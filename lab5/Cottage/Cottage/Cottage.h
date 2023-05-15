#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <Types/DimensionTypes.h>
#include "ShaderProgram.h"
#include "ShaderMVPUniformMap.h"
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
	Cottage();

	void Draw(int width, int height) const;

	void UpdateVPMatrices(int width, int height) const;

private:
	Bedroom m_bedroom;
	LivingRoom m_livingRoom;
	DiningRoom m_diningRoom;
	Garage m_garage;
	Grass m_grass;
	Fence m_fence;

	glance::ShaderProgram m_shaderProgram;
	glance::ShaderMVPUniformMap m_shaderUniformMap;
};
