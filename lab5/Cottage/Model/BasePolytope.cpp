#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "BasePolytope.h"
#include "PolytopeReader/PolytopeReader.h"


BasePolytope::BasePolytope(const std::string& verticesFilePath, Size size, Vector3d position, Vector3d angle)
	: BasePrimitive(size, position, angle)
{
	PolytopeReader polytopeReader(verticesFilePath);
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

void BasePolytope::Draw() const
{
	m_vao->Bind();

	// FIXED: подумать, нужно ли обернуть это рисование в отдельный вызов метода или же создать вообще отдельный класс типа Mesh
	glDrawElements(GL_TRIANGLES, (GLsizei)m_indicesData.size(), GL_UNSIGNED_INT, nullptr);

	m_vao->Unbind();
}

glm::mat4 BasePolytope::BuildModelMatrix() const
{
	// TODO: возможно стоит последовательно передавать матрицы от предыдущего метода преобразования к следующему
	auto translate = glm::translate(glm::mat4(1.0f), glm::vec3(m_position.x, m_position.y, m_position.z));
	auto scale = glm::scale(glm::mat4(1.0f), glm::vec3(m_size.width, m_size.height, m_size.depth));
	auto rotate = glm::rotate(glm::mat4(1.f), glm::radians(m_angle.x), glm::vec3(1.f, 0.f, 0.f));
	rotate = glm::rotate(rotate, glm::radians(m_angle.y), glm::vec3(0.f, 1.f, 0.f));
	rotate = glm::rotate(rotate, glm::radians(m_angle.z), glm::vec3(0.f, 0.f, 1.f));

	return translate * rotate * scale;
}
