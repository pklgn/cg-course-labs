#include "Cottage.h"
#include "../Model/Cube/Cube.h"

Cottage::Cottage(Size size, Vector3d position, float angle)
	: m_cube(std::make_unique<Cube>(size, position, angle))
{
}

void Cottage::Draw(const glance::ShaderProgram& program) const
{
	m_cube->Draw(program);
}
