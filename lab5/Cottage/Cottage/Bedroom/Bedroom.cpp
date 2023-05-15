#include "Bedroom.h"
#include <memory>

Bedroom::Bedroom()
{
	std::unique_ptr<IPolytopeDrawable> room = std::make_unique<TextureCube>(std::move(std::make_unique<Cube>(Size{ 1, 1, 1 }, Vector3d{ 0, 0, 2 })), "Model\\Assets\\brickwall.jpg");
	std::unique_ptr<IPolytopeDrawable> window = std::make_unique<TextureCube>(std::move(std::make_unique<Cube>(Size{ 0.1f, 0.5f, 0.5f }, Vector3d{ 1, 0, 2 }, Vector3d{ 180.f, 0, 0 })), "Model\\Assets\\window.jpg");
	std::unique_ptr<IPolytopeDrawable> roof = std::make_unique<TexturePyramid>(std::move(std::make_unique<Pyramid>(Size{ 1.2f, 1.f, 1.2f }, Vector3d{ 0, 1, 2 })), "Model\\Assets\\roof.jpg");

	m_roomParts.push_back(std::move(room));
	m_roomParts.push_back(std::move(window));
	m_roomParts.push_back(std::move(roof));
}
