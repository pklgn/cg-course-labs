#include "LivingRoom.h"

LivingRoom::LivingRoom()
	: m_room("Model\\Assets\\accentBrickwall.jpg", Size{ 1.3f, 1.3f, 1 }, Vector3d{ 0, 0.3f, 0 })
	, m_window("Model\\Assets\\window.jpg", Size{ 0.1f, 0.5f, 0.5f }, Vector3d{ -1.3f, 0, 0 }, Vector3d{ 180.f, 0, 0 })
	, m_door("Model\\Assets\\door.jpg", Size{ 0.1f, 0.8f, 0.7f }, Vector3d{ 1.25f, -0.2f, 0 }, Vector3d{ 180.f, 0, 0 })
	, m_roof("Model\\Assets\\roof.jpg", Size{ 1.4f, 1.4f, 1 }, Vector3d{ 0, 1.6f, 0 })
{
}

void LivingRoom::Draw(const glance::ShaderProgram& program) const
{
	m_room.Draw(program);
	m_window.Draw(program);
	m_door.Draw(program);
	m_roof.Draw(program);
}
