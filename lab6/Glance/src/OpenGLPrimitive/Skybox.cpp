#include "../pch.h"
#include "OpenGLPrimitive/Skybox.h"

using namespace glance;

Skybox::Skybox(const std::vector<std::string>& faces)
	: m_cubemapTexture(faces)
	, m_vao()
{
	float skyboxVertices[] = {
		// positions
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f, 1.0f,
		-1.0f,  1.0f, 1.0f,
		 1.0f,  1.0f, 1.0f,
		 1.0f,  1.0f, 1.0f,
		 1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,

		-1.0f, 1.0f, -1.0f,
		 1.0f, 1.0f, -1.0f,
		 1.0f, 1.0f,  1.0f,
		 1.0f, 1.0f,  1.0f,
		-1.0f, 1.0f,  1.0f,
		-1.0f, 1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};

	m_vbo = std::make_unique<VertexBuffer>(skyboxVertices, static_cast<GLsizei>(sizeof(skyboxVertices)), GL_STATIC_DRAW);

	m_vao.Bind();
	m_cubemapTexture.Bind();
	m_vbo->Bind();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	
	// TODO: fix strange C6031 warning
	m_vao.Unbind();
}

// TODO: избавиться от skybox в параметрах
void Skybox::Draw() const
{
	m_vao.Bind();
	glDrawArrays(GL_TRIANGLES, 0, m_vbo->GetSize());
	m_vao.Unbind();
}

