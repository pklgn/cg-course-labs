#pragma once
#include <GL/glew.h>
#include <Types/DimensionTypes.h>
#include "ShaderProgram.h"
#include "../Model/Cube/Cube.h"
#include "../Model/Pyramid/Pyramid.h"

class Cottage
{
public:
	Cottage(Size size, Vector3d position, float angle = 0.f);

	void Draw(const glance::ShaderProgram& program) const;

private:
	std::unique_ptr<Cube> m_bedroom;
	std::unique_ptr<Cube> m_bedroomWindow;

	std::unique_ptr<Cube> m_livingRoom;
	std::unique_ptr<Cube> m_livingRoomWindow;
	std::unique_ptr<Cube> m_livingRoomDoor;

	std::unique_ptr<Cube> m_dining;
	std::unique_ptr<Cube> m_diningWindowFront;
	std::unique_ptr<Cube> m_diningWindowRear;

	std::unique_ptr<Cube> m_garage;
	std::unique_ptr<Cube> m_garageDoor;

	std::unique_ptr<Pyramid> m_bedroomRoof;
};
