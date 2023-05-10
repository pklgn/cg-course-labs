#include "Pyramid.h"
#include "../PolytopeReader/PolytopeReader.h"
#include <glm/gtx/transform.hpp>

Pyramid::Pyramid(Size size, Vector3d position, Vector3d angle)
	: BasePrimitive(size, position, angle)
{
	PolytopeReader polytopeReader("Model\\Assets\\pyramid.txt");
	std::vector<Vector3d> vertices;
	std::vector<unsigned int> indices;
	std::vector<RGB> colors;
	std::vector<Vector2d> textureCoords;
	polytopeReader.Read(vertices, indices, colors, textureCoords);

	std::vector<Vector3d> normals = CalculateNormals(vertices);

	std::vector<GLfloat> verticesData;
	auto verticesCount = vertices.size();
	for (int i = 0; i < (int)verticesCount; ++i)
	{
		auto vertex = vertices.at(i);
		auto color = colors.at(i);
		auto normal = normals.at(i);
		auto textureCoord = textureCoords.at(i);
		verticesData.insert(verticesData.end(), { vertex.x, vertex.y, vertex.z, color.r, color.g, color.b, normal.x, normal.y, normal.z, textureCoord.x, textureCoord.y });
	}

	SetVerticesData(verticesData);
	UpdateVerticesData();

	SetIndicesData(indices);
	UpdateIndicesData();
}

void Pyramid::Draw(const glance::ShaderProgram& program) const
{
	m_vao->Bind();

	program.SetUniform4fv("u_model", BuildModelMatrix());

	// TODO: подумать, нужно ли обернуть это рисование в отдельный вызов метода или же создать вообще отдельный класс типа Mesh
	glDrawElements(GL_TRIANGLES, (GLsizei)m_indicesData.size(), GL_UNSIGNED_INT, nullptr);

	m_vao->Unbind();
}
