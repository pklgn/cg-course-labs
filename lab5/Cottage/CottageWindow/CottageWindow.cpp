#include "CottageWindow.h"
#include "../Cottage/Cottage.h"

using namespace glance;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

CottageWindow::CottageWindow(int w, int h, const char* title)
	: BaseWindow(w, h, title)
{
	glfwSetKeyCallback(m_window, key_callback);

	m_cottagePtr = std::make_unique<Cottage>(Size{ 1, 1 }, Vector3d{ 0, 0 });

	m_projection = glm::perspective(glm::radians(45.f), (float)(w + 1) / (float)(h + 1), 0.1f, 100.0f);
	GLint projectionLoc = glGetUniformLocation(*m_shaderProgram, "u_projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(m_projection));
	glViewport(0, 0, w, h);

	std::vector<std::string> faces{
		"Model\\Assets\\Skybox\\right.jpg",
		"Model\\Assets\\Skybox\\left.jpg",
		"Model\\Assets\\Skybox\\top.jpg",
		"Model\\Assets\\Skybox\\bottom.jpg",
		"Model\\Assets\\Skybox\\front.jpg",
		"Model\\Assets\\Skybox\\back.jpg",
	};

	m_skyboxPtr = std::make_unique<Skybox>(faces);
}

void CottageWindow::UpdateVPMatrices(int width, int height)
{
	GLfloat radius = 12.0f;
	GLfloat camX = (GLfloat)(sin(glfwGetTime()) * radius);
	GLfloat camZ = (GLfloat)(cos(glfwGetTime()) * radius);
	m_view = glm::lookAt(glm::vec3(camX, 3, camZ), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));

	m_shaderProgram->SetUniform4fv("u_view", m_view);
}

void CottageWindow::Draw(int width, int height)
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	UpdateVPMatrices(width, height);

	glDepthFunc(GL_LEQUAL);
	m_skyboxShaderProgram->Use();
	m_skyboxPtr->Draw(*m_skyboxShaderProgram, m_view, m_projection);
	glDepthFunc(GL_LESS); // set depth function back to default

	m_shaderProgram->Use();
	m_cottagePtr->Draw(*m_shaderProgram);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// Когда пользователь нажимает ESC, мы устанавливаем свойство WindowShouldClose в true,
	// и приложение после этого закроется
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}
