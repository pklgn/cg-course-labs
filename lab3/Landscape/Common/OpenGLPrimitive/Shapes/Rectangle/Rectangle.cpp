#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <format>
#include <stdexcept>
#include "Rectangle.h"

void Rectangle::Draw(GLuint program) const
{
	// Нарисуем прямоугольник
	glBindVertexArray(m_vao);
	int location = glGetUniformLocation(program, "u_color");
	// TODO: передавать цвет из вершины
	glUniform4f(location, 0.f, 0.3f, 0.8f, 1.0f);
	glm::mat4 model = glm::mat4(1.0f);
	auto scale = glm::scale(glm::mat4(1.0f), glm::vec3(float(m_size.width), float(m_size.height), 1.0f));
	auto trans = glm::translate(glm::mat4(1.0f), glm::vec3(float(m_position.x), float(m_position.y), float(m_position.z)));
	auto final = trans * scale;
	GLint modelLoc = glGetUniformLocation(program, "u_model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(final));
	glDrawArrays(GL_QUADS, 0, VERTICES_NUMBER);
	glBindVertexArray(0);
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
	: BasePrimitive(size, position)
{
	std::vector<GLfloat> vertices = {
		-1, -1, 0,
		 1, -1, 0,
		 1,  1, 0,
		-1,  1, 0
	};

	SetVertices(vertices);
	UpdateData();
}
