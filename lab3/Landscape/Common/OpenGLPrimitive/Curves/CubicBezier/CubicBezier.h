#pragma once
#include <GL/glew.h>
#include "../../../Common/Types/GeometryTypes.h"
#include "../../BasePrimitive.h"

class CubicBezier : public BasePrimitive
{
public:
	CubicBezier(Size size, Vector3d position, const Curve4d& controlPoints, unsigned int verticesNumber = 100);

	void Draw(GLuint program) const override;

private:
	unsigned int m_verticesNumber;
	Curve4d m_controlPoints;
};
