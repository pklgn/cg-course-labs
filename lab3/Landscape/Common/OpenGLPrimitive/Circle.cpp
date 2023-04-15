#define _USE_MATH_DEFINES
#include <cmath>
#include <GL/glew.h>
#include <vector>
#include "Circle.h"

void Circle::Draw(unsigned int program, float radius, unsigned int numSegments)
{
	std::vector<float> vertices;
	vertices.reserve((numSegments + 1) * 3); // 2 координаты на каждую вершину

	auto shiftY = -1.f;

	vertices.push_back(0.0f); // x-координата центра
	vertices.push_back(0.0f + shiftY); // y-координата центра
	vertices.push_back(0.5f);

	std::vector<float> verticesColor;
	std::vector<float> circleColor = {
		0.f, 1.f, 0.f
	};

	for (unsigned int i = 0; i <= numSegments; ++i)
	{
		float angle = static_cast<float>(2.0f * M_PI * static_cast<float>(i) / static_cast<float>(numSegments));
		float x = radius * cosf(angle);
		float y = radius * sinf(angle);
		vertices.push_back(x);
		vertices.push_back(y + shiftY);
		vertices.push_back(0.5f);
	}

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
	glEnableVertexAttribArray(0);

	int location = glGetUniformLocation(program, "u_Color");
	glUniform4f(location, 1.0f, 0.3f, 0.8f, 1.0f);


	glDrawArrays(GL_TRIANGLE_FAN, 0, numSegments + 2); // +2 для центра и последней вершины

	glDisableVertexAttribArray(0);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
}
