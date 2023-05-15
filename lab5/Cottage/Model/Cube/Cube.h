#pragma once
#include "../BasePolytope.h"

class Cube : public BasePolytope
{
public:
	Cube(Size size, Vector3d position, Vector3d angle = { 0.f, 0.f, 0.f });
};
