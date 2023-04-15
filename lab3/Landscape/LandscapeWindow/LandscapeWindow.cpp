#include "LandscapeWindow.h"
#include "../Common/OpenGLPrimitive/Circle.h"
#include "../Common/OpenGLPrimitive/Rectangle.h"

void LandscapeWindow::Draw(int width, int height)
{
	glUseProgram(m_shaderProgram);
	glClear(GL_DEPTH_BUFFER_BIT);
	
	Rectangle::Draw(m_shaderProgram, { // Координаты вершин
										 -0.f, -1.f, -0.5f,
										  1.f, -1.f, -0.5f,
										  1.f,  1.f, -0.5f,
										 -1.f,  1.f, -0.5f});
	Circle::Draw(m_shaderProgram, 1, 36);
}
