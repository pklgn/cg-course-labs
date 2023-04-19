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
	
	SetVerticesData(vertices);
	UpdateData();
}

void MyCircle::Draw(GLuint program) const
{
	glBindVertexArray(m_vao);
	int location = glGetUniformLocation(program, "u_color");
	// TODO: передавать цвет из вершины
	glUniform4f(location, 1.f, 0.3f, 0.8f, 1.0f);
	
	ApplyModelTransform(program);

	glDrawArrays(GL_TRIANGLE_FAN, 0, m_verticesNumber);
	glBindVertexArray(0);
}
