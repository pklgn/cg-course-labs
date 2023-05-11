#include "DiningRoom.h"

DiningRoom::DiningRoom()
	: m_room("Model\\Assets\\brickwall.jpg", Size{ 1.5, 1, 1 }, Vector3d{ 0, 0, -2 })
	, m_windowFront("Model\\Assets\\window.jpg", Size{ 0.1f, 0.7f, 0.7f }, Vector3d{ 1.5f, 0, -2 }, Vector3d{ 180.f, 0, 0 })
	, m_windowRear("Model\\Assets\\window.jpg", Size{ 0.1f, 0.7f, 0.7f }, Vector3d{ -1.5f, 0, -2 }, Vector3d{ 180.f, 0, 0 })
	, m_roof("Model\\Assets\\roof.jpg", Size{ 1.7f, 1.2f, 1 }, Vector3d{ 0, 1, -2 })
{
}

void DiningRoom::Draw(const glance::ShaderProgram& program) const
{
	m_room.Draw(program);
	m_windowFront.Draw(program);
	m_windowRear.Draw(program);
	m_roof.Draw(program);
};
