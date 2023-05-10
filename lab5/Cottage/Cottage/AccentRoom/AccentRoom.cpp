#include "AccentRoom.h"

using namespace glance;

AccentRoom::AccentRoom(Size size, Vector3d position, Vector3d angle)
	: Cube(size, position, angle)
	, m_texture(std::make_unique<Texture>("Model\\Assets\\accentBrickwall.jpg"))
{
}

void AccentRoom::Draw(const glance::ShaderProgram& program) const
{
	m_texture->Bind();
	Cube::Draw(program);
}
