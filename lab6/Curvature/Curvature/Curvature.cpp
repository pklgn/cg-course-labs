#include "Curvature.h"
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>

Curvature::Curvature(Size windowSize, Size size, Vector3d position, Vector3d angle)
	: m_shaderProgram("Shaders/Vertex.shader", "Shaders/Fragment.shader")
	, m_shaderUniformMap("u_model", "u_view", "u_projection")
	, m_line(0, 2 * 3.14f, 2000, size, position, angle)
	, m_windowSize(windowSize)
{
}

void Curvature::SetWindowSize(int width, int height)
{
	m_windowSize = { static_cast<float>(width), static_cast<float>(height), 1 };
	m_line.SetPosition(Vector3d{ static_cast<float>(width) / 2, static_cast<float>(height) / 2, 0 });
}

Size Curvature::GetWindowSize() const
{
	return m_windowSize;
}

void Curvature::Draw() const
{
	m_shaderProgram.Use();
	UpdateMVPMatrices();
	glViewport(0, 0, m_windowSize.width, m_windowSize.height);

	m_line.Draw();
}

void Curvature::UpdateMVPMatrices() const
{
	auto view = glm::mat4(1.0f);
	m_shaderProgram.SetUniform4fv(m_shaderUniformMap.viewUniform.c_str(), view);

	auto projection = glm::ortho(0.0f, float(m_windowSize.width), 0.0f, float(m_windowSize.height), -1.0f, 100.0f);
	m_shaderProgram.SetUniform4fv(m_shaderUniformMap.projectionUniform.c_str(), projection);

	m_shaderProgram.SetUniform4fv(m_shaderUniformMap.modelUniform.c_str(), m_line.BuildModelMatrix());
}
