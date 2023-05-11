#pragma once
#include "../../Model/IDrawable.h"
#include "../../Model/Cube/TextureCube.h"
#include "../../Model/Pyramid/TexturePyramid.h"

class DiningRoom : public IDrawable
{
public:
	DiningRoom();

	void Draw(const glance::ShaderProgram& program) const override;

private:
	TextureCube m_room;
	TextureCube m_windowFront;
	TextureCube m_windowRear;
	TexturePyramid m_roof;
};
