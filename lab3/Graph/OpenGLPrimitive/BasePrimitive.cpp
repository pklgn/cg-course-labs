#include "BasePrimitive.h"
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/type_ptr.hpp>

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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}
