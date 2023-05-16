#include "../../pch.h"
#include "OpenGLLog.h"
#include "OpenGLPrimitive/Primitive.h"

using namespace glance;

Primitive::Primitive(Size size, Vector3d position, Vector3d angle)
	: m_size(size)
	, m_position(position)
	, m_angle(angle)
	, m_vao(std::make_unique<glance::VertexArray>())
	, m_ibo(std::make_unique<glance::IndexBuffer>())
{
}

Primitive::~Primitive()
{
	// TODO: подумать, нужно ли сюда что-то добавить
}

void Primitive::SetVerticesData(const std::vector<VerticesDataType>& vertices)
{
	m_verticesData = vertices;
}

std::vector<Primitive::VerticesDataType> Primitive::GetVerticesData() const
{
	return m_verticesData;
}

void Primitive::SetIndicesData(const std::vector<IndicesDataType>& indicesData)
{
	m_indicesData = indicesData;
}

std::vector<Primitive::IndicesDataType> Primitive::GetIndicesData() const
{
	return m_indicesData;
}

void Primitive::SetSize(Size size)
{
	m_size = size;
}

Size Primitive::GetSize() const
{
	return m_size;
}

void Primitive::SetPosition(Vector3d position)
{
	m_position = position;
}

Vector3d Primitive::GetPosition() const
{
	return m_position;
}

void Primitive::SetAngle(Vector3d angle)
{
	m_angle = angle;
}

Vector3d Primitive::GetAngle() const
{
	return m_angle;
}

// FIXED: переименовать в SetupVerticesData или что-то такое?
void Primitive::UpdateVerticesData()
{
	m_vbo = std::make_unique<VertexBuffer>(m_verticesData.data(), static_cast<GLsizei>(sizeof(VerticesDataType) * m_verticesData.size()), GL_STATIC_DRAW);

	m_vao->Bind();
	m_vbo->Bind();
	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(VerticesDataType), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	
	m_vao->Unbind();
}

void Primitive::UpdateIndicesData()
{
	m_vao->Bind();

	m_ibo->Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indicesData.size() * sizeof(IndicesDataType), m_indicesData.data(), GL_STATIC_DRAW);

	m_vao->Unbind();
}

std::vector<Vector3d> Primitive::CalculateNormals(const std::vector<Vector3d>& vertices) const
{
	std::vector<Vector3d> normals;
	auto vertexCount = vertices.size();
	for (size_t i = 0; i < vertexCount; i += 3)
	{
		auto firstVector = glm::vec3(vertices[i + 1].x - vertices[i].x, vertices[i + 1].y - vertices[i].y, vertices[i + 1].z - vertices[i].z);
		auto secondVector = glm::vec3(vertices[i + 2].x - vertices[i].x, vertices[i + 2].y - vertices[i].y, vertices[i + 2].z - vertices[i].z);

		auto normal = glm::cross(firstVector, secondVector);
		normal = glm::normalize(normal);

		normals.push_back({ normal.x, normal.y, normal.z });
		normals.push_back({ normal.x, normal.y, normal.z });
		normals.push_back({ normal.x, normal.y, normal.z });
	}

	return normals;
}
