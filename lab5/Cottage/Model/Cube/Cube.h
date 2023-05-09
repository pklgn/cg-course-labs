#pragma once
#include "OpenGLPrimitive/BasePrimitive.h"

class Cube : public BasePrimitive
{
public:
	Cube(Size size, Vector3d position, float angle = 0.f);

	void Draw(const glance::ShaderProgram& program) const override;
};
