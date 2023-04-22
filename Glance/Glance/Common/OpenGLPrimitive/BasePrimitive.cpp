#include "../../pch.h"
#include "BasePrimitive.h"

const RGB BasePrimitive::DEFAULT_COLOR = { 1.f, 1.f, 1.f };

BasePrimitive::BasePrimitive(Size size, Vector3d position, float angle)
	: m_size(size)
	, m_position(position)
	, m_angle(angle)
	, m_vao(0)
	, m_vbo(0)
{
}

BasePrimitive::~BasePrimitive()
{
	// Освобождаем ресурсы
	glDeleteBuffers(1, &m_vbo);
	glDeleteVertexArrays(1, &m_vao);
}

void BasePrimitive::SetVerticesData(const std::vector<GLfloat>& vertices)
{
	m_verticesData = vertices;
}

std::vector<GLfloat> BasePrimitive::GetVerticesData() const
{
	return m_verticesData;
}

void BasePrimitive::SetSize(Size size)
{
	m_size = size;
}

Size BasePrimitive::GetSize() const
{
	return m_size;
}

void BasePrimitive::SetPosition(Vector3d position)
{
	m_position = position;
}

Vector3d BasePrimitive::GetPosition() const
{
	return m_position;
}

void BasePrimitive::SetAngle(float angle)
{
	m_angle = angle;
}

float BasePrimitive::GetAngle() const
{
	return m_angle;
}

void BasePrimitive::UpdateData()
{
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);

	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_verticesData.size() * sizeof(m_verticesData.at(0)), m_verticesData.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (3 + 3) * sizeof(GLfloat), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (3 + 3) * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

void BasePrimitive::ApplyModelTransform(GLuint program) const
{
	auto rotate = glm::rotate(glm::mat4(1.0f), float(m_angle * 3.14 / 180), glm::vec3(0.0f, 0.0f, 1.0f));
	auto scale = glm::scale(glm::mat4(1.0f), glm::vec3(float(m_size.width / 2), float(m_size.height / 2), 1.0f));
	auto trans = glm::translate(glm::mat4(1.0f), glm::vec3(float(m_position.x), float(m_position.y), float(m_position.z)));
	auto result = trans * rotate * scale;
	GLint modelLoc = glGetUniformLocation(program, "u_model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(result));
}

std::vector<RGB> BasePrimitive::GetVerticesColor(const std::vector<RGB>& colors, unsigned int verticesNumber) const
{
	std::vector<RGB> finishColors = colors;
	if (finishColors.size() == 1)
	{
		finishColors.resize(verticesNumber, finishColors.front());
	}
	else
	{
		finishColors.resize(verticesNumber, DEFAULT_COLOR);
	}

	return finishColors;
}

