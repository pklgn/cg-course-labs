#include "BasePrimitive.h"

BasePrimitive::BasePrimitive(Size size, Vector3d position)
	: m_size(size)
	, m_position(position)
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

void BasePrimitive::SetVertices(const std::vector<GLfloat>& vertices)
{
	m_vertices = vertices;
}

std::vector<GLfloat> BasePrimitive::GetVertices() const
{
	return m_vertices;
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

void BasePrimitive::UpdateData()
{
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);

	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(m_vertices.at(0)), m_vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(0);
}

