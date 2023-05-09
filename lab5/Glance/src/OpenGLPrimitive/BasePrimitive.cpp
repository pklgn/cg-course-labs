#include "../../pch.h"
#include "OpenGLLog.h"
#include "OpenGLPrimitive/BasePrimitive.h"

using namespace glance;

BasePrimitive::BasePrimitive(Size size, Vector3d position, float angle)
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

void BasePrimitive::SetAngle(float angle)
{
	m_angle = angle;
}

float BasePrimitive::GetAngle() const
{
	return m_angle;
}

// FIXED: переименовать в SetupVerticesData или что-то такое?
void BasePrimitive::UpdateVerticesData()
{
	m_vbo = std::make_unique<VertexBuffer>(m_verticesData.data(), sizeof(VerticesDataType) * m_verticesData.size(), GL_STATIC_DRAW);

	m_vao->Bind();
	m_vbo->Bind();
	// position
	m_vbo->BindAttribPointer(0, GL_FLOAT, 3, (3 + 3 + 3) * sizeof(GLfloat), (GLvoid*)0);
	// color
	m_vbo->BindAttribPointer(1, GL_FLOAT, 3, (3 + 3 + 3) * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	// normal
	m_vbo->BindAttribPointer(2, GL_FLOAT, 3, (3 + 3 + 3) * sizeof(GLfloat), (GLvoid*)((3 + 3) * sizeof(GLfloat)));
	
	m_vao->Unbind();
}

void BasePrimitive::UpdateIndicesData()
{
	m_vao->Bind();

	m_ibo->SetData(m_indicesData.data(), static_cast<unsigned int>(m_indicesData.size()), GL_STATIC_DRAW);

	m_vao->Unbind();
}

void BasePrimitive::ApplyModelTransform(GLuint program) const
{
	auto result = glm::mat4(1.0f);
	GLint modelLoc = glGetUniformLocation(program, "u_model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(result));
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
