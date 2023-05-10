#include "TexturePyramid.h"
#include "Texture.h"

using namespace glance;

TexturePyramid::TexturePyramid(const std::string& texturePath, Size size, Vector3d position, Vector3d angle)
	: Pyramid(size, position, angle)
	, m_texture(std::make_unique<Texture>(texturePath))
{
}

void TexturePyramid::Draw(const glance::ShaderProgram& program) const
{
	m_texture->Bind();
	Pyramid::Draw(program);
}


