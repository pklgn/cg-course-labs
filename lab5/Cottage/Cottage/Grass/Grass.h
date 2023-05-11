#pragma once
#include "../../Model/IDrawable.h"
#include "../../Model/Cube/TextureCube.h"
#include "../../Model/Pyramid/TexturePyramid.h"

class Grass : public IDrawable
{
public:
	Grass();

	void Draw(const glance::ShaderProgram& program) const override;

private:
	TextureCube m_surface;
};
