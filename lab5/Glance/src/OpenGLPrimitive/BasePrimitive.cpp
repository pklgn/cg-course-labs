#include "../../pch.h"
#include "OpenGLLog.h"
#include "OpenGLPrimitive/BasePrimitive.h"

using namespace glance;

BasePrimitive::BasePrimitive(Size size, Vector3d position, Vector3d angle)
	: m_size(size)
	, m_position(position)
	, m_angle(angle)
	, m_vao(std::make_unique<glance::VertexArray>())
	, m_ibo(std::make_unique<glance::IndexBuffer>())
{
	m_vao->Bind();
	glEnable(GL_DEPTH_TEST);
	m_vao->Unbind();
}

BasePrimitive::~BasePrimitive()
{
	// TODO: подумать, нужно ли сюда что-то добавить
}

void BasePrimitive::SetVerticesData(const std::vector<VerticesDataType>& vertices)
{
	m_verticesData = vertices;
}

std::vector<BasePrimitive::VerticesDataType> BasePrimitive::GetVerticesData() const
{
	return m_verticesData;
}

void BasePrimitive::SetIndicesData(const std::vector<IndicesDataType>& indicesData)
{
	m_indicesData = indicesData;
}

std::vector<BasePrimitive::IndicesDataType> BasePrimitive::GetIndicesData() const
{
	return m_indicesData;
}

void BasePrimitive::SetSize(Size size)
{
	m_size = size;
}

Size BasePrimitive::GetSize() const
{
	return m_size;
}

void BasePrimitive::SetPosition(Vector3d position)
{
	m_position = position;
}

Vector3d BasePrimitive::GetPosition() const
{
	return m_position;
}

void BasePrimitive::SetAngle(Vector3d angle)
{
	m_angle = angle;
}

Vector3d BasePrimitive::GetAngle() const
{
	return m_angle;
}

// FIXED: переименовать в SetupVerticesData или что-то такое?
void BasePrimitive::UpdateVerticesData()
{
	m_vbo = std::make_unique<VertexBuffer>(m_verticesData.data(), static_cast<GLsizei>(sizeof(VerticesDataType) * m_verticesData.size()), GL_STATIC_DRAW);

	m_vao->Bind();
	m_vbo->Bind();
	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (3 + 3 + 3 + 2) * sizeof(VerticesDataType), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (3 + 3 + 3 + 2) * sizeof(VerticesDataType), (GLvoid*)(3 * sizeof(VerticesDataType)));
	glEnableVertexAttribArray(1);
	// normal
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, (3 + 3 + 3 + 2) * sizeof(VerticesDataType), (GLvoid*)((3 + 3) * sizeof(VerticesDataType)));
	glEnableVertexAttribArray(2);
	// texture
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, (3 + 3 + 3 + 2) * sizeof(VerticesDataType), (GLvoid*)((3 + 3 + 3) * sizeof(VerticesDataType)));
	glEnableVertexAttribArray(3);
	
	m_vao->Unbind();
}

void BasePrimitive::UpdateIndicesData()
{
	m_vao->Bind();

	m_ibo->Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indicesData.size() * sizeof(IndicesDataType), m_indicesData.data(), GL_STATIC_DRAW);

	m_vao->Unbind();
}

glm::mat4 BasePrimitive::BuildModelMatrix() const
{
	// TODO: возможно стоит последовательно передавать матрицы от предыдущего метода преобразования к следующему
	auto translate = glm::translate(glm::mat4(1.0f), glm::vec3(m_position.x, m_position.y, m_position.z));
	auto scale = glm::scale(glm::mat4(1.0f), glm::vec3(m_size.width, m_size.height, m_size.depth));
	auto rotate = glm::rotate(glm::mat4(1.f), glm::radians(m_angle.x), glm::vec3(1.f, 0.f, 0.f));
	rotate = glm::rotate(rotate, glm::radians(m_angle.y), glm::vec3(0.f, 1.f, 0.f));
	rotate = glm::rotate(rotate, glm::radians(m_angle.z), glm::vec3(0.f, 0.f, 1.f));
	
	return translate * rotate * scale;
}

std::vector<Vector3d> BasePrimitive::CalculateNormals(const std::vector<Vector3d>& vertices) const
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
