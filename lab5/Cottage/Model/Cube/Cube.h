#pragma once
#include "Texture.h"
#include "OpenGLPrimitive/BasePrimitive.h"

class Cube : public BasePrimitive
{
public:
	Cube(Size size, Vector3d position, Vector3d angle = { 0.f, 0.f, 0.f });

	void Draw(const glance::ShaderProgram& program) const override;
};
