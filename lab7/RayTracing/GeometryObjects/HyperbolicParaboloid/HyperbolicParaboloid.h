#pragma once
#include "../../GeometryObject/GeometryObjectImpl.h"

class HyperbolicParaboloid : public CGeometryObjectImpl
{
public:
	HyperbolicParaboloid(CMatrix4d const& transform = CMatrix4d());

	bool Hit(CRay const& ray, CIntersection& intersection) const override;
};
