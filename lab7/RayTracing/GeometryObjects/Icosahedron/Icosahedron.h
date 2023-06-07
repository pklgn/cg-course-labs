#pragma once
#include "../../GeometryObject/GeometryObjectImpl.h"
#include "../../TriangleMesh/TriangleMesh.h"
#include "../WavefrontObject.h"

class Icosahedron : public WavefrontObject
{
public:
	Icosahedron(CMatrix4d const& transform = CMatrix4d());
};
