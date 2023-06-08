#pragma once
#include "../../GeometryObject/GeometryObjectImpl.h"
#include "../../TriangleMesh/TriangleMesh.h"

class Dodecahedron : public CGeometryObjectImpl
{
public:
	Dodecahedron(CMatrix4d const& transform = CMatrix4d());

	// TODO: добавить OnUpdate для трайангл меша при трансформе 
	bool Hit(CRay const& ray, CIntersection& intersection) const override;

private:
	std::unique_ptr<CTriangleMesh> m_triangleMesh;
	std::unique_ptr<CTriangleMeshData> m_triangleMeshData;
};
