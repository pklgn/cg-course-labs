#include "WavefrontObject.h"
#include "PolytopeReader/PolytopeReader.h"

WavefrontObject::WavefrontObject(const std::string& filePath, CMatrix4d const& transform)
{
	PolytopeReader polytopeReader(filePath);

	std::vector<Vertex> vertices;
	std::vector<Face> faces;

	polytopeReader.Read(vertices, faces);

	// Данные полигональной сетки
	m_triangleMeshData = std::make_unique<CTriangleMeshData>(vertices, faces);

	m_triangleMesh = std::make_unique<CTriangleMesh>(m_triangleMeshData.get(), transform);
}

bool WavefrontObject::Hit(CRay const& ray, CIntersection& intersection) const
{
	return m_triangleMesh->Hit(ray, intersection);
}
