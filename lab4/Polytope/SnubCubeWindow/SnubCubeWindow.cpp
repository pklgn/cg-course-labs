#include <OpenGLPrimitive/Shapes/Circle/Circle.h>
#include <OpenGLPrimitive/Shapes/Rectangle/Rectangle.h>
#include "SnubCubeWindow.h"
#include "../SnubCube/SnubCube.h"

SnubCubeWindow::SnubCubeWindow(int w, int h, const char* title)
	: BaseWindow(w, h, title)
{
	// TODO: вынести в класс приложения
	// Включаем режим отбраковки граней
	glEnable(GL_CULL_FACE);
	// Отбраковываться будут нелицевые стороны граней
	glCullFace(GL_BACK);
	// Сторона примитива считается лицевой, если при ее рисовании
	// обход верших осуществляется против часовой стрелки
	//glFrontFace(GL_CCW);

	// Включаем тест глубины для удаления невидимых линий и поверхностей
	glEnable(GL_DEPTH_TEST);
}

void SnubCubeWindow::UpdateUVMatrices(int width, int height)
{
	glm::mat4 view = glm::lookAt(glm::vec3(2, 2, 2), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	GLint viewLoc = glGetUniformLocation(m_shaderProgram, "u_view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	glm::mat4 projection = glm::perspective(45.f, (GLfloat)width / (GLfloat)height, 1.0f, 150.0f);
	GLint projectionLoc = glGetUniformLocation(m_shaderProgram, "u_projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glViewport(0, 0, width, height);
}

void SnubCubeWindow::Draw(int width, int height)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	UpdateUVMatrices(width, height);

	SnubCube snubCube({ 2, 2 }, { 0, 0 });
	snubCube.Draw(m_shaderProgram);
}
