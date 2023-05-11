#pragma once
#include "../../Model/IDrawable.h"
#include "../../Model/Cube/TextureCube.h"
#include "../../Model/Pyramid/TexturePyramid.h"

class Fence : public IDrawable
{
public:
	Fence();

	void Draw(const glance::ShaderProgram& program) const override;

private:
	TextureCube m_body;
	TextureCube m_leftPart;
	TextureCube m_rightPart;
};
