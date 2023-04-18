#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <format>
#include <stdexcept>
#include "Rectangle.h"

void Rectangle::Draw(unsigned int program) const
{
	// �������� �������������
	glBindVertexArray(m_vao);
	int location = glGetUniformLocation(program, "u_Color");
	// TODO: ���������� ���� �� �������
	glUniform4f(location, 0.f, 0.3f, 0.8f, 1.0f);
	glm::mat4 model = glm::mat4(1.0f);
	auto scale = glm::scale(glm::mat4(1.0f), glm::vec3(float(m_size.width), float(m_size.height), 1.0f));
	auto trans = glm::translate(glm::mat4(1.0f), glm::vec3(float(m_position.x), float(m_position.y), float(m_position.z)));
	auto final = trans * scale;
	GLint modelLoc = glGetUniformLocation(program, "u_model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(final));
	glDrawArrays(GL_QUADS, 0, 4);
	glBindVertexArray(0);
}

void Rectangle::Prepare()
{
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);

	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(m_vertices.at(0)), m_vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(0);
}

void Rectangle::CheckVertices(const std::vector<float>& vertices)
{
	auto expectedSize = VERTICES_NUMBER * DIMENSIONS_NUMBER;
	if (vertices.size() != expectedSize)
	{
		auto fmt = std::format("Unable to assign less or more than {} vertices with {} dimensions each",
			VERTICES_NUMBER,
			DIMENSIONS_NUMBER);
		throw std::invalid_argument(fmt);
	}
}

Rectangle::Rectangle(Size size, Vector3d position)
	: m_size(size)
	, m_position(position)
{
	std::vector<float> vertices = {
		-1, -1, 0,
		 1, -1, 0,
		 1,  1, 0,
		-1,  1, 0
	};

	SetVertices(vertices);
	Prepare();
}

Rectangle::~Rectangle()
{
	// ����������� �������
	glDeleteBuffers(1, &m_vbo);
	glDeleteVertexArrays(1, &m_vao);
}

void Rectangle::SetVertices(const std::vector<float>& vertices)
{
	CheckVertices(vertices);
	m_vertices = vertices;
}

std::vector<float> Rectangle::GetVertices() const
{
	return m_vertices;
}

void Rectangle::SetSize(Size size)
{
	m_size = size;
}

Size Rectangle::GetSize() const
{
	return m_size;
}
