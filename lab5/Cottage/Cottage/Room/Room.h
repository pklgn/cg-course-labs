#pragma once
#include "../../Model/Cube/Cube.h"
#include "Texture.h"

class Room : public Cube
{
public:
	Room(Size size, Vector3d position, Vector3d angle = { 0.f, 0.f, 0.f });

	void Draw(const glance::ShaderProgram& program) const override;

private:
	std::unique_ptr<glance::Texture> m_texture;
};
