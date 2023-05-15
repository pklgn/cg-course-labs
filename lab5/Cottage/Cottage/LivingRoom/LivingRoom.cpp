#include <memory>
#include "LivingRoom.h"

LivingRoom::LivingRoom()
{
	std::unique_ptr<IPolytopeDrawable> room = std::make_unique<TextureCube>(std::move(std::make_unique<Cube>(Size{ 1.3f, 1.3f, 1 }, Vector3d{ 0, 0.3f, 0 })), "Model\\Assets\\accentBrickwall.jpg");
	std::unique_ptr<IPolytopeDrawable> window = std::make_unique<TextureCube>(std::move(std::make_unique<Cube>(Size{ 0.1f, 0.5f, 0.5f }, Vector3d{ -1.3f, 0, 0 }, Vector3d{ 180.f, 0, 0 })), "Model\\Assets\\window.jpg");
	std::unique_ptr<IPolytopeDrawable> door = std::make_unique<TextureCube>(std::move(std::make_unique<Cube>(Size{ 0.1f, 0.8f, 0.7f }, Vector3d{ 1.25f, -0.2f, 0 }, Vector3d{ 180.f, 0, 0 })), "Model\\Assets\\door.jpg");
	std::unique_ptr<IPolytopeDrawable> roof = std::make_unique<TexturePyramid>(std::move(std::make_unique<Pyramid>(Size{ 1.4f, 1.4f, 1 }, Vector3d{ 0, 1.6f, 0 })), "Model\\Assets\\roof.jpg");
	std::unique_ptr<IPolytopeDrawable> veranda = std::make_unique<TexturePyramid>(std::move(std::make_unique<Pyramid>(Size{ 0.4f, 0.4f, 0.8f }, Vector3d{ 1.3f, 0.7f, 0 })), "Model\\Assets\\roof.jpg");

	m_roomParts.push_back(std::move(room));
	m_roomParts.push_back(std::move(window));
	m_roomParts.push_back(std::move(door));
	m_roomParts.push_back(std::move(roof));
	m_roomParts.push_back(std::move(veranda));
}
