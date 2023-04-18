#pragma once
#include "../../BasePrimitive.h"

class MyCircle : public BasePrimitive
{
public:
	MyCircle(Size size, Vector3d position, unsigned int verticesNumber = 360);

	void Draw(GLuint program) const override;

private:
	unsigned int m_verticesNumber;
};
