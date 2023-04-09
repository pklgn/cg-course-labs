#define _USE_MATH_DEFINES
#include <cmath>
#include "GraphWindow.h"

#pragma comment(lib, "glew32.lib")


constexpr GLfloat X_MIN = -1;
constexpr GLfloat X_MAX = 1;
constexpr GLfloat Y_MIN = -1;
constexpr GLfloat Y_MAX = 1;

constexpr float GRID_STEP = 0.1f;

constexpr GLfloat MIN_X_RANGE_BOUND = -6 * M_PI;
constexpr GLfloat MAX_X_RANGE_BOUND = 6 * M_PI;
constexpr float X_STEP = 0.0001f;

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

	float positions[6] = {
		-0.5f, -0.5f,
		 0.5f, -0.5f,
		 0.0f,  0.5f
	};
	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

	// NEW
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


	glDrawArrays(GL_TRIANGLES, 0, 3);
}
