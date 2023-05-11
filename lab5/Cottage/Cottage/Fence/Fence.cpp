#include "Fence.h"

Fence::Fence()
	: m_body("Model\\Assets\\fence.jpg", Size{ 0.05f, 1.f, 5 }, Vector3d{ -4, 0, -1 })
	, m_leftPart("Model\\Assets\\fence.jpg", Size{ 0.05f, 1.f, 3 }, Vector3d{ -1, 0, 4 }, Vector3d{ 0, 90.f, 0 })
	, m_rightPart("Model\\Assets\\fence.jpg", Size{ 0.05f, 1.f, 3 }, Vector3d{ -1, 0, -6 }, Vector3d{ 0, 90.f, 0 })
{
}

void Fence::Draw(const glance::ShaderProgram& program) const
{
	m_body.Draw(program);
	m_leftPart.Draw(program);
	m_rightPart.Draw(program);
}
