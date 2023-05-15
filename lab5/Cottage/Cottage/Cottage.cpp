#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "Cottage.h"

Cottage::Cottage()
	: m_shaderProgram("Shaders/Vertex.shader", "Shaders/Fragment.shader")
	, m_shaderUniformMap("u_model", "u_view", "u_projection")
{
}

void Cottage::Draw(int width, int height) const
{
	// TODO: собирать шейлеры в рамках коттеджа и вызывать как элемент класса конкретный шейдер
	m_shaderProgram.Use();
	m_shaderProgram.SetUniform3f("u_lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
	m_shaderProgram.SetUniform3f("u_lightPos", glm::vec3(10.2f, 10.0f, 10.0f));
	UpdateVPMatrices(width, height);

	m_bedroom.Draw(m_shaderProgram, m_shaderUniformMap);
	m_livingRoom.Draw(m_shaderProgram, m_shaderUniformMap);
	m_diningRoom.Draw(m_shaderProgram, m_shaderUniformMap);
	m_garage.Draw(m_shaderProgram, m_shaderUniformMap);
	m_grass.Draw(m_shaderProgram, m_shaderUniformMap);
	m_fence.Draw(m_shaderProgram, m_shaderUniformMap);
}

void Cottage::UpdateVPMatrices(int width, int height) const
{
	GLfloat radius = 12.0f;
	GLfloat camX = (GLfloat)(sin(glfwGetTime()) * radius);
	GLfloat camZ = (GLfloat)(cos(glfwGetTime()) * radius);
	auto view = glm::lookAt(glm::vec3(camX, 3, camZ), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));

	m_shaderProgram.SetUniform4fv(m_shaderUniformMap.viewUniform.c_str(), view);

	auto projection = glm::perspective(glm::radians(45.f), (float)(width + 1) / (float)(height + 1), 0.1f, 100.0f);
	m_shaderProgram.SetUniform4fv(m_shaderUniformMap.projectionUniform.c_str(), projection);
	glViewport(0, 0, width, height);
}
