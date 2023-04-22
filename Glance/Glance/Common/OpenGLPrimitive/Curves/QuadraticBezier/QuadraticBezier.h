#pragma once
#include "../../../Common/Types/GeometryTypes.h"
#include "../../BasePrimitive.h"

class QuadraticBezier : public BasePrimitive
{
public:
	QuadraticBezier(Size size, Vector3d position, const Curve4d& controlPoints, const std::vector<RGB>& colors = {}, float angle = 0.f, unsigned int verticesNumber = 100);

	void Draw(GLuint program) const override;

	void SetDrawMode(GLenum mode);

private:
	unsigned int m_verticesNumber;
	Curve4d m_controlPoints;
	GLenum m_drawMode;
};
