#pragma once
#include "DimensionTypes.h"

struct Curve3d
{
	Vector3d p1;
	Vector3d p2;
	Vector3d p3;
};

struct Curve4d
{
	Vector3d p1;
	Vector3d p2;
	Vector3d p3;
	Vector3d p4;
};

struct Circle
{
	float radius;
	float posX;
	float posY;
	float transX;
	float transY;
	float transZ;
};