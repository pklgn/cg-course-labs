#pragma once
#include <string>
#include "../GeometryObject/GeometryObjectImpl.h"
#include "../TriangleMesh/TriangleMesh.h"

class WavefrontObject : public CGeometryObjectImpl
{
public:
	WavefrontObject(const std::string& filePath, CMatrix4d const& transform = CMatrix4d());

	bool Hit(CRay const& ray, CIntersection& intersection) const override;

private:
	std::unique_ptr<CTriangleMesh> m_triangleMesh;
	std::unique_ptr<CTriangleMeshData> m_triangleMeshData;
};
