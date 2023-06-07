#pragma once
#include "../../GeometryObject/GeometryObjectWithInitialTransformImpl.h"

class EllipticParaboloid : public CGeometryObjectWithInitialTransformImpl
{
public:
	EllipticParaboloid(CMatrix4d const& transform);

	bool Hit(CRay const& ray, CIntersection& intersection) const override;
};
