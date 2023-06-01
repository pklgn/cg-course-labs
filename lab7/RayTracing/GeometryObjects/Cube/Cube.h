#pragma once
#include "../../GeometryObject/GeometryObjectImpl.h"

class Cube : public CGeometryObjectImpl
{
public:
	Cube(double size = 1,
		CVector3d const& center = CVector3d(),
		CMatrix4d const& transform = CMatrix4d());

	/*
		Ќахождение точки пересечени€ луча с кубом
	*/
	virtual bool Hit(CRay const& ray, CIntersection& intersection) const;

private:
	double m_size;
	CVector3d const& m_center;
	CMatrix4d const& m_transform;
};
