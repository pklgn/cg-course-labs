#include "Cottage.h"
#include "Room/Room.h"
#include "AccentRoom/AccentRoom.h"
#include "Window/Window.h"
#include "Door/Door.h"
#include "../Model/Cube/TextureCube.h"
#include "../Model/Pyramid/TexturePyramid.h"

Cottage::Cottage(Size size, Vector3d position, float angle)
	: m_bedroom(std::make_unique<Room>(Size{ 1, 1, 1 }, Vector3d{ 0, 0, 2 }))
	, m_bedroomWindow(std::make_unique<Window>(Size{ 0.1f, 0.5f, 0.5f }, Vector3d{ 1, 0, 2 }, Vector3d{ 180.f, 0, 0 }))
	, m_livingRoom(std::make_unique<AccentRoom>(Size{ 1.3f, 1.3f, 1 }, Vector3d{ 0, 0.3f, 0 }))
	, m_livingRoomWindow(std::make_unique<Window>(Size{ 0.1f, 0.5f, 0.5f }, Vector3d{ -1.3f, 0, 0 }, Vector3d{ 180.f, 0, 0 }))
	, m_livingRoomDoor(std::make_unique<Door>(Size{ 0.1f, 0.8f, 0.7f }, Vector3d{ 1.25f, -0.2f, 0 }, Vector3d{ 180.f, 0, 0 }))
	, m_dining(std::make_unique<Room>(Size{ 1.5, 1, 1 }, Vector3d{ 0, 0, -2 }))
	, m_diningWindowFront(std::make_unique<Window>(Size{ 0.1f, 0.7f, 0.7f }, Vector3d{ 1.5f, 0, -2 }, Vector3d{ 180.f, 0, 0 }))
	, m_diningWindowRear(std::make_unique<Window>(Size{ 0.1f, 0.7f, 0.7f }, Vector3d{ -1.5f, 0, -2 }, Vector3d{ 180.f, 0, 0 }))
	, m_garage(std::make_unique<Room>(Size{ 1, 1, 1 }, Vector3d{ 0, 0, -4 }))
	, m_garageDoor(std::make_unique<TextureCube>("Model\\Assets\\garageDoor.jpg", Size{ 0.1f, 0.8f, 0.7f }, Vector3d{ 1.f, 0, -4 }, Vector3d{ 180.f, 0, 0 }))
	, m_bedroomRoof(std::make_unique<TexturePyramid>("Model\\Assets\\roof.jpg", Size{ 1.2f, 1.f, 1.2f }, Vector3d{ 0, 1, 2 }))
{
}	

void Cottage::Draw(const glance::ShaderProgram& program) const
{
	program.SetUniform3f("u_objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
	program.SetUniform3f("u_lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
	program.SetUniform3f("u_lightPos", glm::vec3(10.2f, 10.0f, 10.0f));

	m_bedroom->Draw(program);
	m_bedroomWindow->Draw(program);

	m_livingRoom->Draw(program);
	m_livingRoomWindow->Draw(program);
	m_livingRoomDoor->Draw(program);

	m_dining->Draw(program);
	m_diningWindowFront->Draw(program);
	m_diningWindowRear->Draw(program);

	m_garage->Draw(program);
	m_garageDoor->Draw(program);

	m_bedroomRoof->Draw(program);
}
