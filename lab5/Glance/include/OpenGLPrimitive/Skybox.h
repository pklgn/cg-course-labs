#pragma once
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "CubemapTexture.h"
#include "ShaderProgram.h"

namespace glance
{

class Skybox
{
public:
	Skybox(const std::vector<std::string>& faces);

	void Draw(const ShaderProgram& program, const glm::mat4& view, const glm::mat4& projection) const;

private:
	std::unique_ptr<VertexArray> m_vao;
	std::unique_ptr<VertexBuffer> m_vbo;

	CubemapTexture m_cubemapTexture;
};

}; // namespace glance