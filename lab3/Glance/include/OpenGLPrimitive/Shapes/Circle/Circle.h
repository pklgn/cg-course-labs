#pragma once
#include "../../BasePrimitive.h"

class Circle : public BasePrimitive
{
public:
	Circle(Size size, Vector3d position, const std::vector<RGB>& colors = {}, float angle = 0.f, unsigned int verticesNumber = 360);

	void Draw(GLuint program) const override;

private:
	unsigned int m_verticesNumber;
};
