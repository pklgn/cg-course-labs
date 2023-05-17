#include "Mandelbrot.h"
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>

Mandelbrot::Mandelbrot(Size windowSize, Size size, Vector3d position, Vector3d angle)
	: m_shaderProgram("Shaders/Vertex.shader", "Shaders/Fragment.shader")
	, m_shaderUniformMap("u_model", "u_view", "u_projection")
	, m_mandelbrotUniformMap("systemResolution", "systemTime", "mouse")
	, m_rectangle(size, position, angle)
	, m_windowSize(windowSize)
{
}

void Mandelbrot::SetWindowSize(int width, int height)
{
	m_windowSize = { static_cast<float>(width), static_cast<float>(height), 1 };
	m_rectangle.SetPosition(Vector3d{ static_cast<float>(width) / 2, static_cast<float>(height) / 2, 0 });
}

Size Mandelbrot::GetWindowSize() const
{
	return m_windowSize;
}

void Mandelbrot::Draw() const
{
	m_shaderProgram.Use();
	UpdateMVPMatrices();
	glViewport(0, 0, static_cast<GLsizei>(m_windowSize.width), static_cast<GLsizei>(m_windowSize.height));

	m_shaderProgram.SetUniform2f(m_mandelbrotUniformMap.systemResolution.c_str(), glm::vec2(m_windowSize.width, m_windowSize.height));
	m_shaderProgram.SetUniform1f(m_mandelbrotUniformMap.systemTime.c_str(), glfwGetTime() * 1000);
	m_shaderProgram.SetUniform3f(m_mandelbrotUniformMap.mouse.c_str(), glm::vec3(0.0, 0.0, 0.01));

	m_rectangle.Draw();
}

void Mandelbrot::UpdateMVPMatrices() const
{
	auto view = glm::mat4(1.0f);
	m_shaderProgram.SetUniform4fv(m_shaderUniformMap.viewUniform.c_str(), view);

	auto projection = glm::ortho(0.0f, float(m_windowSize.width), 0.0f, float(m_windowSize.height), -1.0f, 100.0f);
	m_shaderProgram.SetUniform4fv(m_shaderUniformMap.projectionUniform.c_str(), projection);

	m_shaderProgram.SetUniform4fv(m_shaderUniformMap.modelUniform.c_str(), m_rectangle.BuildModelMatrix());
}
