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
	double radius;
	double posX;
	double posY;
	double transX;
	double transY;
	double transZ;
};