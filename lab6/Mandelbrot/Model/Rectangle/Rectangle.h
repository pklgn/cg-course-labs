#pragma once
#include "../TexturePrimitive.h"
#include "OpenGLPrimitive/IPrimitiveDrawable.h"

class Rectangle : public TexturePrimitive, public IPrimitiveDrawable
{
public:
	Rectangle(Size size, Vector3d position, Vector3d angle = { 0.f, 0.f, 0.f });

	void Draw() const;

	glm::mat4 BuildModelMatrix() const;
};
