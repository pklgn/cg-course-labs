#include "Grass.h"

Grass::Grass()
{
	std::unique_ptr<IPolytopeDrawable> surface = std::make_unique<TextureCube>(std::move(std::make_unique<Cube>(Size{ 0.1f, 5, 5 }, Vector3d{ 0, -1, -1 }, Vector3d{ 0, 0, 90.f })), "Model\\Assets\\grass.jpg");

	m_roomParts.push_back(std::move(surface));
}
