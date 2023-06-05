#pragma once
#include "../../GeometryObject/GeometryObjectWithInitialTransformImpl.h"

class ConicCylinder : public CGeometryObjectWithInitialTransformImpl
{
public:
	ConicCylinder(
		double const& height = 1, // ������ �������� (>=0)
		double const& baseRadius = 1, // ������ ��������� (>=0)
		double const& capRadius = 0, // ������ ������ (>=0)
		CMatrix4d const& tranform = CMatrix4d());

	virtual bool Hit(CRay const& ray, CIntersection& intersection) const;

private:
	double m_smallRadius;
};
