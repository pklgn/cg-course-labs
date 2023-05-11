#include "../pch.h"
#include "OpenGLPrimitive/Skybox.h"

using namespace glance;

Skybox::Skybox(const std::vector<std::string>& faces)
	: m_cubemapTexture(faces)
	, m_vao(std::make_unique<glance::VertexArray>())
{
	float skyboxVertices[] = {
		// positions
		-1.0f, 1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,

		-1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,

		-1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f
	};

	m_vbo = std::make_unique<VertexBuffer>(skyboxVertices, sizeof(skyboxVertices), GL_STATIC_DRAW);

	m_vao->Bind();
	m_vbo->Bind();
	m_vbo->BindAttribPointer(0, GL_FLOAT, 3, 3 * sizeof(GLfloat), (GLvoid*)0);
	m_vao->Unbind();
}

void Skybox::Draw(const ShaderProgram& skyboxProgram, const glm::mat4& view, const glm::mat4& projection) const
{
	skyboxProgram.SetUniform4fv("view", glm::mat4(glm::mat3(view)));
	skyboxProgram.SetUniform4fv("projection", projection);
	// skybox cube
	m_vao->Bind();
	m_cubemapTexture.Bind();
	glDrawArrays(GL_TRIANGLES, 0, 36);
	m_vao->Unbind();
}

