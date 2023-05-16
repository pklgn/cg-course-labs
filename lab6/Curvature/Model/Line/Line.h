#pragma once
#include "OpenGLPrimitive/Primitive.h"
#include "OpenGLPrimitive/IPrimitiveDrawable.h"

class Line : public Primitive, public IPrimitiveDrawable
{
public:
	Line(float startX, float finishX, unsigned int precision, Size size, Vector3d position, Vector3d angle = { 0.f, 0.f, 0.f });

	void Draw() const;

	glm::mat4 BuildModelMatrix() const;
};
