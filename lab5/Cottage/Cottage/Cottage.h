#pragma once
#include <GL/glew.h>
#include <Types/DimensionTypes.h>
#include "ShaderProgram.h"
#include "Bedroom/Bedroom.h"
#include "LivingRoom/LivingRoom.h"
#include "DiningRoom/DiningRoom.h"
#include "Garage/Garage.h"
#include "Grass/Grass.h"
#include "Fence/Fence.h"

class Cottage
{
public:
	// FIXED: убрать все параметры для коттеджа

	void Draw(const glance::ShaderProgram& program) const;

private:
	Bedroom m_bedroom;
	LivingRoom m_livingRoom;
	DiningRoom m_diningRoom;
	Garage m_garage;
	Grass m_grass;
	Fence m_fence;
};
