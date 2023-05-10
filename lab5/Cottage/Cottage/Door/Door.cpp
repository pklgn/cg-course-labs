#include "Door.h"

using namespace glance;

Door::Door(Size size, Vector3d position, Vector3d angle)
	: Cube(size, position, angle)
	, m_texture(std::make_unique<Texture>("Model\\Assets\\door.jpg"))
{
}

void Door::Draw(const glance::ShaderProgram& program) const
{
	m_texture->Bind();
	Cube::Draw(program);
}
