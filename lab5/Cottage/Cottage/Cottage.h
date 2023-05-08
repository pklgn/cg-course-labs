#pragma once
#include <GL/glew.h>
#include <Types/DimensionTypes.h>

class Cottage
{
public:
	Cottage(Size size, Vector3d position, float angle = 0.f);

	void Draw(GLuint program) const;
};
