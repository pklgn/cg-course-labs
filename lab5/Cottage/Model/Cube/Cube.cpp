#include "Cube.h"
#include "../PolytopeReader/PolytopeReader.h"

using namespace glance;

Cube::Cube(Size size, Vector3d position, float angle)
	: BasePrimitive(size, position, angle)
{
	PolytopeReader polytopeReader("SnubCube.txt");
	std::vector<Vector3d> vertices;
	std::vector<unsigned int> indices;
	std::vector<RGB> colors;
	polytopeReader.Read(vertices, indices, colors);

	std::vector<Vector3d> normals = CalculateNormals(vertices);

	std::vector<GLfloat> verticesData;
	auto verticesCount = vertices.size();
	for (int i = 0; i < (int)verticesCount; ++i)
	{
		auto vertex = vertices.at(i);
		auto color = colors.at(i);
		auto normal = normals.at(i);
		verticesData.insert(verticesData.end(), { vertex.x, vertex.y, vertex.z, color.r, color.g, color.b, normal.x, normal.y, normal.z });
	}

	SetVerticesData(verticesData);
	UpdateVerticesData();

	SetIndicesData(indices);
	UpdateIndicesData();
}

void Cube::Draw(const ShaderProgram& program) const
{
	m_vao->Bind();

	ApplyModelTransform(program);
	program.SetUniform3f("u_objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
	program.SetUniform3f("u_lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
	program.SetUniform3f("u_lightPos", glm::vec3(10.2f, 10.0f, 10.0f));

	// TODO: подумать, нужно ли обернуть это рисование в отдельный вызов метода или же создать вообще отдельный класс типа Mesh
	glDrawElements(GL_TRIANGLES, (GLsizei)m_indicesData.size(), GL_UNSIGNED_INT, nullptr);

	m_vao->Unbind();
}
