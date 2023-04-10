#define _USE_MATH_DEFINES
#include "GraphWindow.h"
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>

#pragma comment(lib, "glew32.lib")

constexpr GLfloat X_MIN = -1;
constexpr GLfloat X_MAX = 1;
constexpr GLfloat Y_MIN = -1;
constexpr GLfloat Y_MAX = 1;

constexpr float GRID_STEP = 0.1f;

constexpr GLfloat MIN_X_RANGE_BOUND = -6 * M_PI;
constexpr GLfloat MAX_X_RANGE_BOUND = 6 * M_PI;
constexpr float X_STEP = 0.0001f;

struct ShaderProgramSource
{
	std::string vertexShader;
	std::string framgentShader;
};

static ShaderProgramSource ParseShader(const std::string& filepath)
{
	std::ifstream stream(filepath);

	enum class ShaderType
	{
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1,
	};

	if (!stream)
	{
		std::cout << "Unable to open filestream at " << filepath << std::endl;
		throw std::invalid_argument("Invalid filepath");
	}

	std::string line;
	std::stringstream ss[2];
	ShaderType shaderType = ShaderType::NONE;
	while (std::getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				shaderType = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				shaderType = ShaderType::FRAGMENT;
			}
		}
		else
		{
			ss[(int)shaderType] << line << "\n";
		}
	}

	return {
		ss[0].str(),
		ss[1].str()
	};
}

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
				  << "shader";
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);

	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

void DrawCoordinateSystem()
{
	// Рисуем сетку
	glColor3f(0.3f, 0.3f, 0.3f);
	glBegin(GL_LINES);
	for (float i = -1.0f; i <= 1.0f; i += GRID_STEP)
	{
		glVertex2f(i, -1.0f);
		glVertex2f(i, 1.0f);

		glVertex2f(-1.0f, i);
		glVertex2f(1.0f, i);
	}
	glEnd();
	// TODO: сделать координатные оси пропорциональными
	// TODO: сам график и сетку вынести в отдельные классы

	// Рисуем ось X
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2f(-1.0f, 0.0f);
	glVertex2f(1.0f, 0.0f);
	glEnd();

	// Рисуем ось Y
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2f(0.0f, -1.0f);
	glVertex2f(0.0f, 1.0f);
	glEnd();
}

GLfloat GetHarmonicOscillation(GLfloat x)
{
	return sin(3 * x) + cos(2 * x + M_PI / 12);
}

void GraphWindow::Draw(int width, int height)
{
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT);

	DrawCoordinateSystem();

	const auto scaleX = (std::abs(MIN_X_RANGE_BOUND) + std::abs(MAX_X_RANGE_BOUND)) / 2;
	glColor3f(0.0f, 1.0f, 1.0f);
	glBegin(GL_LINE_STRIP);
	for (float x = MIN_X_RANGE_BOUND; x <= MAX_X_RANGE_BOUND; x += X_STEP)
	{
		glVertex2f((x) / scaleX,
			GetHarmonicOscillation(x) / 2);
	}
	glEnd();

	float positions[] = {
		-0.5f, -0.5f, // 0
		 0.5f, -0.5f, // 1
		 0.5f,  0.5f, // 2
		-0.5f,  0.5f  // 3
	};

	// NEW
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), positions, GL_STATIC_DRAW);

	// index = 0, потому что это первый из наших атрибутов с начальным индексом 0
	// size = 2, так как нашим первым атрибутом будет позиция в двухмерной системе кооординат (x, y), например (-0.5f, -0.5f)
	// type = GL_FLOAT, потому что флоат)
	// normalize = FALSE, вроде как нормализовать не надо, все норм
	// stride = 8, это количество байт, которое мы имеем между каждой вершиной, это величина именно до следующей ВЕРШИНЫ (vertex), НЕ АТРБИБУТА (attribute)
	// pointer = 0 помним, что указатель это тоже число, которое мы передаем для КОНКРЕТНОЙ ВЕРШИНЫ и в рамках этой вершины прибавляем к ее стартовому адресу
	// указатель, чтобы получить доступ к конкретному атрибуту, можно использовать offsetof макрос, если у нас уже определена конкретная структура в качестве текущего атрибута
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(positions[0]) * 2, 0);
	// MEM: нужно заэнейблить этот атрибут
	glEnableVertexAttribArray(0);

	// есть два основных типов шейдеров: vertex-шейдер и fragment-шейдер (также известных как pixel-шейдеры)
	/*
	 * Получаем следующую последовательность действий
	 * 1. Draw call
	 * 2. Vertex shader
	 * 3. Fragment shader
	 * 4. Получаем возможность увидеть на экране, что ожидали
	 *
	 * Получается, что вертекс шейдер вызывается отдельно для каждой вершины, поскольку мы рисуем треугольник, у которого три вершины, то
	 * это означает, что вертекс шейдер будет вызван трижды
	 * Основная цель вертекс шейдера в том, чтобы сказать ОПЕНЖЫЭЛ где мы хотим видеть нашу вершину на нашем скрин спейс
	 * Шейдер не связан со светом и тенью, это программа
	 * Все, что делает вертекс шейдер - определяет какой мы хотим видеть позицию, потому что как мы уже знаем, в ОПЕНЖЫЭЛе все координаты нормированы
	 * и их надо привести к реальным
	 *
	 * После вертекс этапа наступает очередь фрагмент-шейдеров
	 * Будем для простоты пока считать, что фрагменты это пиксели
	 * Каждый фрагмент шейдер будет выполнен единожды для каждого пикселя, который требует растеризации
	 * Фрагмент шейдер решает, каким цветом должен быть каждый пиксель
	 * Прикольное сравнение с раскраской, сначала определили вершины, а затем закрасили в установленных границах нужным цветом
	 * Опять ниточка со стейт машиной, которая нам напоминает, что нужно ЗАЭНЕЙБЛИТЬ шейдер, чтобы его использовать
	 */

	// NEW
	unsigned int ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	ShaderProgramSource shaderProgramSource = ParseShader("Resources/Shaders/Shader.shader");

	auto shader = CreateShader(shaderProgramSource.vertexShader, shaderProgramSource.framgentShader);
	glUseProgram(shader);

	// NEW
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}
