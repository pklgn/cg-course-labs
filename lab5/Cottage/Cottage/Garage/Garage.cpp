#include "Garage.h"

Garage::Garage()
	: m_room("Model\\Assets\\brickwall.jpg", Size{ 1, 1, 1 }, Vector3d{ 0, 0, -4 })
	, m_door("Model\\Assets\\garageDoor.jpg", Size{ 0.1f, 0.8f, 0.7f }, Vector3d{ 1.f, -0.2f, -4 }, Vector3d{ 180.f, 0, 0 })
	, m_roof("Model\\Assets\\roof.jpg", Size{ 1.2f, 1.2f, 1 }, Vector3d{ 0, 1, -4 })
{
}

void Garage::Draw(const glance::ShaderProgram& program) const
{
	m_room.Draw(program);
	m_door.Draw(program);
	m_roof.Draw(program);
}

