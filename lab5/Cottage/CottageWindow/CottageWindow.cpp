#include "CottageWindow.h"
#include "../Cottage/Cottage.h"

using namespace glance;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

CottageWindow::CottageWindow(int w, int h, const char* title)
	: BaseWindow(w, h, title)
{
	glfwSetKeyCallback(m_window, key_callback);
	glfwSetCursorPosCallback(m_window, mouse_callback);

	m_cottagePtr = std::make_unique<Cottage>();

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

	m_projection = glm::perspective(glm::radians(45.f), (float)(width + 1) / (float)(height + 1), 0.1f, 100.0f);
	GLint projectionLoc = glGetUniformLocation(*m_shaderProgram, "u_projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(m_projection));
	glViewport(0, 0, width, height);
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

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	//if (firstMouse)
	//{
	//	lastX = xpos;
	//	lastY = ypos;
	//	firstMouse = false;
	//}

	//float xoffset = xpos - lastX;
	//float yoffset = lastY - ypos;
	//lastX = xpos;
	//lastY = ypos;

	//float sensitivity = 0.1f;
	//xoffset *= sensitivity;
	//yoffset *= sensitivity;

	//yaw += xoffset;
	//pitch += yoffset;

	//if (pitch > 89.0f)
	//	pitch = 89.0f;
	//if (pitch < -89.0f)
	//	pitch = -89.0f;

	//glm::vec3 front;
	//front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	//front.y = sin(glm::radians(pitch));
	//front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	//cameraFront = glm::normalize(front);
}
