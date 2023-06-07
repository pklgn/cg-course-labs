#pragma once
#include "../../GeometryObject/GeometryObjectWithInitialTransformImpl.h"

class HyperbolicParaboloid : public CGeometryObjectWithInitialTransformImpl
{
public:
	HyperbolicParaboloid(CVector3d const& center, CMatrix4d const& transform);

	bool Hit(CRay const& ray, CIntersection& intersection) const override;
};
