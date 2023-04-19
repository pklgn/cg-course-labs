#define _USE_MATH_DEFINES
#include <cmath>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "Circle.h"

Circle::Circle(Size size, Vector3d position, const std::vector<RGB>& colors, unsigned int verticesNumber)
	: BasePrimitive(size, position)
	, m_verticesNumber(verticesNumber)
{
	std::vector<GLfloat> vertices;
	vertices.resize(m_verticesNumber * (3 + 3));

	std::vector<RGB> finishColors = GetVerticesColor(colors, m_verticesNumber);

	for (int angle = 0, index = 0; angle < 360; angle += (360 / m_verticesNumber), index += 6)
	{
		float rad = angle * M_PI / 180.0f;
		//positions
		vertices[index] = cosf(rad);
		vertices[index + 1] = sinf(rad);
		vertices[index + 2] = 1.f;
		//colors
		vertices[index + 3] = finishColors[index / 6].r;
		vertices[index + 4] = finishColors[index / 6].g;
		vertices[index + 5] = finishColors[index / 6].b;
	}
	
	SetVerticesData(vertices);
	UpdateData();
}

void Circle::Draw(GLuint program) const
{
	glBindVertexArray(m_vao);
	
	ApplyModelTransform(program);

	glDrawArrays(GL_TRIANGLE_FAN, 0, m_verticesNumber);
	glBindVertexArray(0);
}
