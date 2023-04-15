#include <GL/glew.h>
#include "Rectangle.h"

void Rectangle::Draw(unsigned int program, const std::vector<float> corners)
{
	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, corners.size() * sizeof(corners.at(0)), corners.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Нарисуем прямоугольник
	glBindVertexArray(VAO);
	int location = glGetUniformLocation(program, "u_Color");
	glUniform4f(location, 0.f, 0.3f, 0.8f, 1.0f);
	glDrawArrays(GL_QUADS, 0, 4);
	glBindVertexArray(0);

	// Освобождаем ресурсы
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}
