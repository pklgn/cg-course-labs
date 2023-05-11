#pragma once
#include <GL/glew.h>
#include <Types/DimensionTypes.h>
#include "ShaderProgram.h"
#include "../Model/Cube/Cube.h"
#include "../Model/Pyramid/Pyramid.h"
#include "Bedroom/Bedroom.h"
#include "LivingRoom/LivingRoom.h"
#include "DiningRoom/DiningRoom.h"
#include "Garage/Garage.h"

class Cottage
{
public:
	Cottage(Size size, Vector3d position, float angle = 0.f);

	void Draw(const glance::ShaderProgram& program) const;

private:
	Bedroom m_bedroom;
	LivingRoom m_livingRoom;
	DiningRoom m_diningRoom;
	Garage m_garage;
};
