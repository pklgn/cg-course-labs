#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "SnubCube.h"
#include <ShaderProgram.h>
#include "../PolytopeReader/PolytopeReader.h"

SnubCube::SnubCube(Size size, Vector3d position, float angle)
	: BasePrimitive(size, position, angle)
{
	// FIXED: сделать чтение из файла
	
	PolytopeReader polytopeReader("SnubCube.txt");
	std::vector<Vector3d> vertices;
	std::vector<unsigned int> indexes;
	std::vector<RGB> colors;
	polytopeReader.Read(vertices, indexes, colors);

	std::vector<Vector3d> normals;
	CalculateNormals(normals, vertices);

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
	UpdateIndexData(indexes);
}

void SnubCube::Draw(GLuint program) const
{
	glBindVertexArray(m_vao);
	ApplyModelTransform(program);
	ShaderProgram::SetVec3(program, "u_objectColor", 1.0f, 0.5f, 0.31f);
	ShaderProgram::SetVec3(program, "u_lightColor", 1.0f, 1.0f, 1.0f);
	ShaderProgram::SetVec3(program, "u_lightPos", 10.2f, 10.0f, 10.0f);

	if (m_ibo != 0)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT); // отбраковываем лицевые (ближние) грани
		glDrawElements(GL_TRIANGLES, (GLsizei)m_indicesData.size() , GL_UNSIGNED_INT, nullptr);
		glCullFace(GL_BACK);
		glDrawElements(GL_TRIANGLES, (GLsizei)m_indicesData.size(), GL_UNSIGNED_INT, nullptr);
	}
	else
	{
		glDrawArrays(GL_LINE_STRIP, 0, m_verticesNumber);
	}

	glBindVertexArray(0);
}

void SnubCube::CalculateNormals(std::vector<Vector3d>& normals, const std::vector<Vector3d>& vertices) const
{
	normals.clear();
	auto vertexCount = vertices.size();
	for (size_t i = 0; i < vertexCount; i+=3)
	{
		auto firstVector = glm::vec3(vertices[i + 1].x - vertices[i].x, vertices[i + 1].y - vertices[i].y, vertices[i + 1].z - vertices[i].z);
		auto secondVector = glm::vec3(vertices[i + 2].x - vertices[i].x, vertices[i + 2].y - vertices[i].y, vertices[i + 2].z - vertices[i].z);

		auto normal = glm::cross(firstVector, secondVector);
		normal = glm::normalize(normal);

		normals.push_back({ normal.x, normal.y, normal.z });
		normals.push_back({ normal.x, normal.y, normal.z });
		normals.push_back({ normal.x, normal.y, normal.z });
	}
}
