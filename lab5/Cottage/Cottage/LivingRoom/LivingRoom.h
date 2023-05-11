#pragma once
#include "../../Model/Cube/TextureCube.h"
#include "../../Model/IDrawable.h"
#include "../../Model/Pyramid/TexturePyramid.h"

class LivingRoom : public IDrawable
{
public:
	LivingRoom();

	void Draw(const glance::ShaderProgram& program) const override;

private:
	TextureCube m_room;
	TextureCube m_door;
	TextureCube m_window;
	TexturePyramid m_roof;
};
