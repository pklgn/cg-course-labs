#include "TextureCube.h"
#include "Texture.h"

using namespace glance;

TextureCube::TextureCube(const std::string& texturePath, Size size, Vector3d position, Vector3d angle)
	: Cube(size, position, angle)
	, m_texture(std::make_unique<Texture>(texturePath))
{
}

void TextureCube::Draw(const glance::ShaderProgram& program) const
{
	m_texture->Bind();
	Cube::Draw(program);
}
