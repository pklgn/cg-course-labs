#include "CottageWindow.h"
#include "../Cottage/Cottage.h"

using namespace glance;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

CottageWindow::CottageWindow(int w, int h, const char* title)
	: BaseWindow(w, h, title)
	, m_cottage()
	, m_skyboxShaderProgram("Shaders/SkyboxVertex.shader", "Shaders/SkyboxFragment.shader")
	, m_skyboxShaderUniformMap("", "view", "projection")
{
	glfwSetKeyCallback(m_window, key_callback);
	glfwSetCursorPosCallback(m_window, mouse_callback);

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

	m_projection = glm::perspective(glm::radians(45.f), (float)(width + 1) / (float)(height + 1), 0.1f, 100.0f);
	glViewport(0, 0, width, height);
}

void CottageWindow::Draw(int width, int height)
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	UpdateVPMatrices(width, height);
	glDepthFunc(GL_LEQUAL);
	m_skyboxShaderProgram.Use();

	m_skyboxShaderProgram.SetUniform4fv(m_skyboxShaderUniformMap.viewUniform.c_str(), glm::mat4(glm::mat3(m_view)));
	m_skyboxShaderProgram.SetUniform4fv(m_skyboxShaderUniformMap.projectionUniform.c_str(), m_projection);
	m_skyboxPtr->Draw();
	glDepthFunc(GL_LESS); // set depth function back to default

	m_cottage.Draw(width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// TODO: реализовать
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	// TODO: реализовать
}
