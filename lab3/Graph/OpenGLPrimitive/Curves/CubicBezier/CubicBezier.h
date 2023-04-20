#pragma once
#include <GL/glew.h>
#include "../../../Types/GeometryTypes.h"
#include "../../BasePrimitive.h"

class CubicBezier : public BasePrimitive
{
public:
	CubicBezier(
		Size size, Vector3d position, const Curve4d& controlPoints, const std::vector<RGB>& colors = {}, float angle = 0.f, unsigned int verticesNumber = 100);

	void Draw() const override;

private:
	unsigned int m_verticesNumber;
	Curve4d m_controlPoints;
};
