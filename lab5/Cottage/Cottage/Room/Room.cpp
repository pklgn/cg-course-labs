#include "Room.h"
#include "../Window/Window.h"

using namespace glance;

Room::Room(Size size, Vector3d position, Vector3d angle)
	: Cube(size, position, angle)
	, m_texture(std::make_unique<Texture>("Model\\Assets\\brickwall.jpg"))
{
}

void Room::Draw(const glance::ShaderProgram& program) const
{
	m_texture->Bind();
	Cube::Draw(program);
}
