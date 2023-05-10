#pragma once
#include "Cube.h"

class TextureCube : public Cube
{
public:
	TextureCube(const std::string& texturePath, Size size, Vector3d position, Vector3d angle = { 0.f, 0.f, 0.f });

	void Draw(const glance::ShaderProgram& program) const override;

private:
	std::unique_ptr<glance::Texture> m_texture;
};
