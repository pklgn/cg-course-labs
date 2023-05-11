#include "Bedroom.h"

Bedroom::Bedroom()
	: m_room("Model\\Assets\\brickwall.jpg", Size{ 1, 1, 1 }, Vector3d{ 0, 0, 2 })
	, m_window("Model\\Assets\\window.jpg", Size{ 0.1f, 0.5f, 0.5f }, Vector3d{ 1, 0, 2 }, Vector3d{ 180.f, 0, 0 })
	, m_roof("Model\\Assets\\roof.jpg", Size{ 1.2f, 1.f, 1.2f }, Vector3d{ 0, 1, 2 })
{
}

void Bedroom::Draw(const glance::ShaderProgram& program) const
{
	m_room.Draw(program);
	m_window.Draw(program);
	m_roof.Draw(program);
}

