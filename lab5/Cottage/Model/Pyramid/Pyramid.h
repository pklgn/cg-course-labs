#pragma once
#include "../BasePolytope.h"

class Pyramid : public BasePolytope
{
public:
	Pyramid(Size size, Vector3d position, Vector3d angle = { 0.f, 0.f, 0.f });
};
