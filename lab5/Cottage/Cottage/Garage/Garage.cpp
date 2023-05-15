#include "Garage.h"

Garage::Garage()
{
	std::unique_ptr<IPolytopeDrawable> room = std::make_unique<TextureCube>(std::move(std::make_unique<Cube>(Size{ 1, 1, 1 }, Vector3d{ 0, 0, -4 })), "Model\\Assets\\brickwall.jpg");
	std::unique_ptr<IPolytopeDrawable> door = std::make_unique<TextureCube>(std::move(std::make_unique<Cube>(Size{ 0.1f, 0.8f, 0.7f }, Vector3d{ 1.f, -0.2f, -4 }, Vector3d{ 180.f, 0, 0 })), "Model\\Assets\\garageDoor.jpg");
	std::unique_ptr<IPolytopeDrawable> roof = std::make_unique<TexturePyramid>(std::move(std::make_unique<Pyramid>(Size{ 1.2f, 1.2f, 1 }, Vector3d{ 0, 1, -4 })), "Model\\Assets\\roof.jpg");

	m_roomParts.push_back(std::move(room));
	m_roomParts.push_back(std::move(door));
	m_roomParts.push_back(std::move(roof));
}

