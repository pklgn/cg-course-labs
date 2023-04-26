#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "SnubCube.h"
#include <ShaderProgram.h>

SnubCube::SnubCube(Size size, Vector3d position, const std::vector<RGB>& /*colors*/, float angle)
	: BasePrimitive(size, position, angle)
{
	// TODO: сделать чтение из файла
	//std::vector<GLfloat> verticesData = {
	//	0.f, 0.f, 1.077364f,	 0.f, 0.5f, 0.5f,
	//	0.7442063f,0.f ,0.7790187f,	 0.f, 0.5f, 0.5f,
	//	0.3123013f,0.6755079f,0.7790187f,	 0.f, 0.5f, 0.5f,
	//	-0.482096,0.5669449,0.7790187,	 0.f, 0.5f, 0.5f,
	//	-0.7169181,-0.1996786,0.7790187,	 0.f, 0.5f, 0.5f,
	//	-0.1196038,-0.7345325,0.7790187,	 0.f, 0.5f, 0.5f,
	//	0.6246025,-0.7345325,0.4806734,	 0.f, 0.5f, 0.5f,
	//	 1.056508,-0.1996786,0.06806912,	 0.f, 0.5f, 0.5f,
	//	0.8867128,0.5669449,0.2302762,	 0.f, 0.5f, 0.5f,
	//	0.2621103,1.042774,0.06806912,	 0.f, 0.5f, 0.5f,
	//	-0.532287,0.9342111,0.06806912,	 0.f, 0.5f, 0.5f,
	//	-1.006317,0.3082417,0.2302762,	 0.f, 0.5f, 0.5f,
	//	-0.7020817,-0.784071,0.2302762,	 0.f, 0.5f, 0.5f,
	//	 0.02728827,-1.074865,0.06806912,	 0.f, 0.5f, 0.5f,
	//	0.6667271,-0.784071,-0.3184664,	 0.f, 0.5f, 0.5f,
	//	0.8216855,-0.09111555,-0.6908285,	 0.f, 0.5f, 0.5f,
	//	0.6518908,0.6755079,-0.5286215,	 0.f, 0.5f, 0.5f,
	//	-0.1196038,0.8751866,-0.6168117,	 0.f, 0.5f, 0.5f,
	//	-0.8092336,0.4758293,-0.5286215,	 0.f, 0.5f, 0.5f,
	//	-0.9914803,-0.2761507,-0.3184664,	 0.f, 0.5f, 0.5f,
	//	-0.4467414,-0.825648,-0.5286215,	 0.f, 0.5f, 0.5f,
	//	0.1926974,-0.5348539,-0.915157,	 0.f, 0.5f, 0.5f,
	//	0.1846311,0.2587032,-1.029416,	 0.f, 0.5f, 0.5f,
	//	-0.5049987,-0.1406541,-0.9412258,	 0.f, 0.5f, 0.5f,
	//};
	m_verticesNumber = 24;

	std::vector<Vector3d> vertices = {
		{ 0.f, 0.f, 1.077364f },
		{ 0.7442063f, 0.f, 0.7790187f },
		{ 0.3123013f, 0.6755079f, 0.7790187f },
		{ -0.482096f, 0.5669449f, 0.7790187f },
		{ -0.7169181f, -0.1996786f, 0.7790187f },
		{ -0.1196038f, -0.7345325f, 0.7790187f },
		{ 0.6246025f, -0.7345325f, 0.4806734f },
		{ 1.056508f, -0.1996786f, 0.06806912f },
		{ 0.8867128f, 0.5669449f, 0.2302762f },
		{ 0.2621103f, 1.042774f, 0.06806912f },
		{ -0.532287f, 0.9342111f, 0.06806912f },
		{ -1.006317f, 0.3082417f, 0.2302762f },
		{ -0.7020817f, -0.784071f, 0.2302762f },
		{ 0.02728827f, -1.074865f, 0.06806912f },
		{ 0.6667271f, -0.784071f, -0.3184664f },
		{ 0.8216855f, -0.09111555f, -0.6908285f },
		{ 0.6518908f, 0.6755079f, -0.5286215f },
		{ -0.1196038f, 0.8751866f, -0.6168117f },
		{ -0.8092336f, 0.4758293f, -0.5286215f },
		{ -0.9914803f, -0.2761507f, -0.3184664f },
		{ -0.4467414f, -0.825648f, -0.5286215f },
		{ 0.1926974f, -0.5348539f, -0.915157f },
		{ 0.1846311f, 0.2587032f, -1.029416f },
		{ -0.5049987f, -0.1406541f, -0.9412258f }
	};

	std::vector<RGB> colors = {
		{ 0.f, 0.5f, 0.5f },
		{ 0.f, 0.5f, 0.5f },
		{ 0.f, 0.5f, 0.5f },
		{ 0.f, 0.5f, 0.5f },
		{ 0.f, 0.5f, 0.5f },
		{ 0.f, 0.5f, 0.5f },
		{ 0.f, 0.5f, 0.5f },
		{ 0.f, 0.5f, 0.5f },
		{ 0.f, 0.5f, 0.5f },
		{ 0.f, 0.5f, 0.5f },
		{ 0.f, 0.5f, 0.5f },
		{ 0.f, 0.5f, 0.5f },
		{ 0.f, 0.5f, 0.5f },
		{ 0.f, 0.5f, 0.5f },
		{ 0.f, 0.5f, 0.5f },
		{ 0.f, 0.5f, 0.5f },
		{ 0.f, 0.5f, 0.5f },
		{ 0.f, 0.5f, 0.5f },
		{ 0.f, 0.5f, 0.5f },
		{ 0.f, 0.5f, 0.5f },
		{ 0.f, 0.5f, 0.5f },
		{ 0.f, 0.5f, 0.5f },
		{ 0.f, 0.5f, 0.5f },
		{ 0.f, 0.5f, 0.5f },
	};

	std::vector<unsigned int> indecies = {
		0, 1, 2,
		0, 2, 3,
		0, 3, 4,
		0, 4, 5,
		1, 6, 7,
		1, 7, 8,
		1, 8, 2,
		2, 8, 9,
		3, 10, 11,
		3, 11, 4,
		4, 12, 5,
		5, 12, 13,
		5, 13, 6,
		6, 13, 14,
		6, 14, 7,
		7, 14, 15,
		8, 16, 9,
		9, 16, 17,
		9, 17, 10,
		10, 17, 18,
		10, 18, 11,
		11, 18, 19,
		12, 19, 20,
		12, 20, 13,
		14, 21, 15,
		15, 21, 22,
		15, 22, 16,
		16, 22, 17,
		18, 23, 19,
		19, 23, 20,
		20, 23, 21,
		21, 23, 22,
		0, 5, 6, 1,
		2, 9, 10, 3,
		4, 11, 19, 12,
		7, 15, 16, 8,
		13, 20, 21, 14,
		17, 22, 23, 18
	};

	auto normals = CalculateNormals(vertices, indecies, { {}, {} });

	std::vector<GLfloat> verticesData;
	for (int i = 0; i < (int)m_verticesNumber; ++i)
	{
		auto vertex = vertices.at(i);
		auto color = colors.at(i);
		auto normal = normals.at(i);
		verticesData.insert(verticesData.end(), { vertex.x, vertex.y, vertex.z, color.r, color.g, color.b, normal.x, normal.y, normal.z });
	}

	SetVerticesData(verticesData);
	UpdateVerticesData();
	UpdateIndexData(indecies);
}

void SnubCube::Draw(GLuint program) const
{
	glBindVertexArray(m_vao);

	ApplyModelTransform(program);
	ShaderProgram::SetVec3(program, "u_lightColor", 1.0f, 1.0f, 1.0f);
	ShaderProgram::SetVec3(program, "u_lightPos", 1.2f, 1.0f, 2.0f);

	if (m_ibo != 0)
	{
		glDrawElements(GL_LINE_STRIP, (GLsizei)m_indicesData.size(), GL_UNSIGNED_INT, nullptr);
	}
	else
	{
		glDrawArrays(GL_LINE_STRIP, 0, m_verticesNumber);
	}
	glDrawArrays(GL_LINE_STRIP, 0, 24);
	glBindVertexArray(0);
}

std::vector<Vector3d> SnubCube::CalculateNormals(const std::vector<Vector3d>& vertices, const std::vector<unsigned int>& indices, const std::unordered_map<int, int>& faceVertexCountTofaceCount) const
{
	std::vector<Vector3d> normals(vertices.size(), { 0, 0, 0 });
	int offset = 0;
	for (const auto [faceVertexCount, faceCount] : faceVertexCountTofaceCount)
	{
		// бегаем по вектору индексов
		for (int i = offset; i < faceCount; i+=faceVertexCount)
		{
			auto firstPointIndex = indices.at(i);
			auto secondPointIndex = indices.at(i + 1);
			auto thirdPointIndex = indices.at(i + 2);

			auto firstPoint = vertices.at(firstPointIndex);
			auto secondPoint = vertices.at(secondPointIndex);
			auto thirdPoint = vertices.at(thirdPointIndex);

			auto firstVector = glm::vec3(secondPoint.x - firstPoint.x, secondPoint.y - firstPoint.y, secondPoint.z - firstPoint.z);
			auto secondVector = glm::vec3(thirdPoint.x - firstPoint.x, thirdPoint.y - firstPoint.y, thirdPoint.z - firstPoint.z);

			auto result = glm::cross(firstVector, secondVector);
			result = glm::normalize(result);
			normals[firstPointIndex] + Vector3d{ result.x, result.y, result.z };
			normals[firstPointIndex] + Vector3d{ result.x, result.y, result.z };
			normals[firstPointIndex] + Vector3d{ result.x, result.y, result.z };
		}
		offset += faceCount;
	}
	for (auto&& normal : normals)
	{
		normal.Normalize();
	}

	return normals;
}
