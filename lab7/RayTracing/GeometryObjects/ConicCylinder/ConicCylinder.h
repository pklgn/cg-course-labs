#pragma once
#include "../../GeometryObject/GeometryObjectWithInitialTransformImpl.h"

class ConicCylinder : public CGeometryObjectWithInitialTransformImpl
{
public:
	ConicCylinder(
		double const& height = 1, // Высота цилиндра (>=0)
		double const& baseRadius = 1, // Радиус основания (>=0)
		double const& capRadius = 0, // Радиус крышки (>=0)
		CMatrix4d const& tranform = CMatrix4d());

	virtual bool Hit(CRay const& ray, CIntersection& intersection) const;

private:
	double m_smallRadius;
};
