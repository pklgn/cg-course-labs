#pragma once
#include "../../Model/IDrawable.h"
#include "../../Model/Cube/TextureCube.h"
#include "../../Model/Pyramid/TexturePyramid.h"

class Garage : public IDrawable
{
public:
	Garage();

	void Draw(const glance::ShaderProgram& program) const override;

private:
	TextureCube m_room;
	TextureCube m_door;
	TexturePyramid m_roof;
};
