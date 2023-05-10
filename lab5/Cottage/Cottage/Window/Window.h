#pragma once
#include "../../Model/Cube/Cube.h"

class Window : public Cube
{
public:
	Window(Size size, Vector3d position, float angle = 0.f);

	void Draw(const glance::ShaderProgram& program) const override;

private:
	std::unique_ptr<glance::Texture> m_texture;
};
