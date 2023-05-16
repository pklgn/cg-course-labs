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

	void Draw() const;

private:
	VertexArray m_vao;
	std::unique_ptr<VertexBuffer> m_vbo;

	CubemapTexture m_cubemapTexture;
};

}; // namespace glance