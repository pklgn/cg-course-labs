#pragma once
#include "../../../Common/Types/GeometryTypes.h"
#include "../../BasePrimitive.h"
#include <GL/glew.h>

class QuadraticBezier : public BasePrimitive
{
public:
	QuadraticBezier(Size size, Vector3d position, const Curve4d& controlPoints, unsigned int verticesNumber = 100);

	void Draw(GLuint program) const override;

private:
	unsigned int m_verticesNumber;
	Curve4d m_controlPoints;
};
