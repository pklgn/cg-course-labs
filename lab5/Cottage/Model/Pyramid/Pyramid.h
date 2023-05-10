#pragma once
#include "OpenGLPrimitive/BasePrimitive.h"

class Pyramid : public BasePrimitive
{
public:
	Pyramid(Size size, Vector3d position, Vector3d angle = { 0.f, 0.f, 0.f });

	void Draw(const glance::ShaderProgram& program) const override;
};
