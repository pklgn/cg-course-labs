#pragma once
#include <GL/glew.h>
#include <Types/DimensionTypes.h>
#include "ShaderProgram.h"
#include "../Model/Cube/Cube.h"

class Cottage
{
public:
	Cottage(Size size, Vector3d position, float angle = 0.f);

	void Draw(const glance::ShaderProgram& program) const;

private:
	std::unique_ptr<Cube> m_room;
	std::unique_ptr<Cube> m_window;
};
