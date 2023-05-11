#pragma once
#include "../../Model/IDrawable.h"
#include "../../Model/Cube/TextureCube.h"
#include "../../Model/Pyramid/TexturePyramid.h"

class Bedroom : public IDrawable
{
public:
	Bedroom();

	void Draw(const glance::ShaderProgram& program) const override;

private:
	TextureCube m_room;
	TextureCube m_window;
	TexturePyramid m_roof;
};
