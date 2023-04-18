#define _USE_MATH_DEFINES
#include <cmath>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "Circle.h"

MyCircle::MyCircle(Size size, Vector3d position, unsigned int verticesNumber)
	: BasePrimitive(size, position)
	, m_verticesNumber(verticesNumber)
{
	std::vector<GLfloat> vertices;
	vertices.resize(m_verticesNumber * 3);

	for (int angle = 0, index = 0; angle < 360; angle += (360 / m_verticesNumber), index += 3)
	{
		float rad = angle * M_PI / 180.0f;
		vertices[index] = cosf(rad);
		vertices[index + 1] = sinf(rad);
		vertices[index + 2] = 1.f;
	}
	
	SetVertices(vertices);
	UpdateData();
}

void MyCircle::Draw(GLuint program) const
{
	glBindVertexArray(m_vao);
	int location = glGetUniformLocation(program, "u_color");
	// TODO: передавать цвет из вершины
	glUniform4f(location, 1.f, 0.3f, 0.8f, 1.0f);
	glm::mat4 model = glm::mat4(1.0f);
	auto scale = glm::scale(glm::mat4(1.0f), glm::vec3(float(m_size.width), float(m_size.height), 1.0f));
	auto trans = glm::translate(glm::mat4(1.0f), glm::vec3(float(m_position.x), float(m_position.y), float(m_position.z)));
	auto final = trans * scale;
	GLint modelLoc = glGetUniformLocation(program, "u_model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(final));
	glDrawArrays(GL_TRIANGLE_FAN, 0, m_verticesNumber);
	glBindVertexArray(0);
}
