#include "Fence.h"

Fence::Fence()
{
	std::unique_ptr<IPolytopeDrawable> rearFence = std::make_unique<TextureCube>(std::move(std::make_unique<Cube>(Size{ 0.05f, 1.f, 5 }, Vector3d{ -4, 0, -1 })), "Model\\Assets\\fence.jpg");
	std::unique_ptr<IPolytopeDrawable> leftFence = std::make_unique<TextureCube>(std::move(std::make_unique<Cube>(Size{ 0.05f, 1.f, 3 }, Vector3d{ -1, 0, 4 }, Vector3d{ 0, 90.f, 0 })), "Model\\Assets\\fence.jpg");
	std::unique_ptr<IPolytopeDrawable> rightFence = std::make_unique<TextureCube>(std::move(std::make_unique<Cube>(Size{ 0.05f, 1.f, 3 }, Vector3d{ -1, 0, -6 }, Vector3d{ 0, 90.f, 0 })), "Model\\Assets\\fence.jpg");

	m_roomParts.push_back(std::move(rearFence));
	m_roomParts.push_back(std::move(leftFence));
	m_roomParts.push_back(std::move(rightFence));
}
