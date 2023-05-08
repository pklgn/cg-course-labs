#include <OpenGLPrimitive/Shapes/Circle/Circle.h>
#include <OpenGLPrimitive/Shapes/Rectangle/Rectangle.h>
#include "CottageWindow.h"
#include "../Cottage/Cottage.h"

using namespace glance;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

CottageWindow::CottageWindow(int w, int h, const char* title)
	: BaseWindow(w, h, title)
{
	glfwSetKeyCallback(m_window, key_callback);
	//// TODO: вынести в класс приложения
	// Включаем режим отбраковки граней

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_DEPTH_TEST);

	m_cottagePtr = std::make_unique<Cottage>(Size{ 1, 1 }, Vector3d{ 0, 0 });

	glm::mat4 projection = glm::perspective(glm::radians(45.f), (float)(w + 1) / (float)(h + 1), 0.1f, 100.0f);
	GLint projectionLoc = glGetUniformLocation(*m_shaderProgram, "u_projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glViewport(0, 0, w, h);
}

void CottageWindow::UpdateVPMatrices(int width, int height)
{
	GLfloat radius = 3.0f;
	GLfloat camX = (GLfloat)(sin(glfwGetTime()) * radius);
	GLfloat camZ = (GLfloat)(cos(glfwGetTime()) * radius);
	glm::mat4 view;
	view = glm::lookAt(glm::vec3(camX, 2, camZ), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	GLint viewLoc = glGetUniformLocation(*m_shaderProgram, "u_view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
}

void CottageWindow::Draw(int width, int height)
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//UpdateVPMatrices(width, height);
	//glEnable(GL_CULL_FACE);
	// Отбраковываться будут нелицевые стороны граней
	//glCullFace(GL_FRONT);
	//m_cottagePtr->Draw(*m_shaderProgram);
	// Сторона примитива считается лицевой, если при ее рисовании
	// обход верших осуществляется против часовой стрелки
	//glCullFace(GL_BACK);
	// Включаем тест глубины для удаления невидимых линий и поверхностей
	m_cottagePtr->Draw(*m_shaderProgram);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// Когда пользователь нажимает ESC, мы устанавливаем свойство WindowShouldClose в true,
	// и приложение после этого закроется
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}
