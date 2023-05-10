#include "Cottage.h"
#include "Room/Room.h"
#include "Window/Window.h"

Cottage::Cottage(Size size, Vector3d position, float angle)
	: m_room(std::make_unique<Room>(Size{ 1, 1, 1 }, Vector3d{ -2, 0, 0 }))
	, m_window(std::make_unique<Window>(Size{ 0.1f, 0.5f, 0.5f }, Vector3d{ 0, 0, 0 }))

{
}	

void Cottage::Draw(const glance::ShaderProgram& program) const
{
	m_room->Draw(program);
	m_window->Draw(program);
}
