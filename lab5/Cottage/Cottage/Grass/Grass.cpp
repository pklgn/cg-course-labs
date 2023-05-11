#include "Grass.h"

Grass::Grass()
	: m_surface("Model\\Assets\\grass.jpg", Size{ 0.1f, 5, 5 }, Vector3d{ 0, -1, -1 }, Vector3d{ 0, 0, 90.f })
{
}

void Grass::Draw(const glance::ShaderProgram& program) const
{
	m_surface.Draw(program);
}
