#include <OpenGLPrimitive/Shapes/Circle/Circle.h>
#include <OpenGLPrimitive/Shapes/Rectangle/Rectangle.h>
#include "SnubCubeWindow.h"
#include "../SnubCube/SnubCube.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

SnubCubeWindow::SnubCubeWindow(int w, int h, const char* title)
	: BaseWindow(w, h, title)
{
	glfwSetKeyCallback(m_window, key_callback);  
	//// TODO: вынести в класс приложения
	// Включаем режим отбраковки граней
	glEnable(GL_CULL_FACE);
	// Отбраковываться будут нелицевые стороны граней
	glCullFace(GL_BACK);
	// Сторона примитива считается лицевой, если при ее рисовании
	// обход верших осуществляется против часовой стрелки
	glFrontFace(GL_CCW);

	// Включаем тест глубины для удаления невидимых линий и поверхностей
	glEnable(GL_DEPTH_TEST);
}

void SnubCubeWindow::UpdateUVMatrices(int width, int height)
{
	GLfloat radius = 3.0f;
	GLfloat camX = sin(glfwGetTime()) * radius;
	GLfloat camZ = cos(glfwGetTime()) * radius;
	glm::mat4 view;
	view = glm::lookAt(glm::vec3(camX, 2, camZ), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	GLint viewLoc = glGetUniformLocation(m_shaderProgram, "u_view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	glm::mat4 projection = glm::perspective(glm::radians(45.f), (float)(width + 1) / (float)(height + 1), 0.1f, 100.0f);
	GLint projectionLoc = glGetUniformLocation(m_shaderProgram, "u_projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glViewport(0, 0, width, height);
}

void SnubCubeWindow::Draw(int width, int height)
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	UpdateUVMatrices(width, height);

	SnubCube snubCube({ 1, 1 }, { 0, 0 });
	snubCube.Draw(m_shaderProgram);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// Когда пользователь нажимает ESC, мы устанавливаем свойство WindowShouldClose в true,
	// и приложение после этого закроется
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}
