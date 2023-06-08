#include "Dodecahedron.h"
#include "../PolytopeReader/PolytopeReader.h"

// TODO: сделать так, чтобы все додекаэдры шарили одну и ту же меш дату
Dodecahedron::Dodecahedron(CMatrix4d const& transform)
	: CGeometryObjectImpl(transform)
{
	PolytopeReader polytopeReader("GeometryObjects/Dodecahedron/dodecahedron.obj");

	std::vector<Vertex> vertices;
	std::vector<Face> faces;

	polytopeReader.Read(vertices, faces);

	// Данные полигональной сетки
	m_triangleMeshData = std::make_unique<CTriangleMeshData>(vertices, faces);

	m_triangleMesh = std::make_unique<CTriangleMesh>(m_triangleMeshData.get(), transform);
}

bool Dodecahedron::Hit(CRay const& ray, CIntersection& intersection) const
{
	return m_triangleMesh->Hit(ray, intersection);
}
