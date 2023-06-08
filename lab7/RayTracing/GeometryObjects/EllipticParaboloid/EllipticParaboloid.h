#pragma once
#include "../../GeometryObject/GeometryObjectImpl.h"

class EllipticParaboloid : public CGeometryObjectImpl
{
public:
	EllipticParaboloid(CMatrix4d const& transform);

	bool Hit(CRay const& ray, CIntersection& intersection) const override;
};
