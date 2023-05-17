#include "OpenGLLog.h"
#include "TexturePrimitive.h"

using namespace glance;

TexturePrimitive::TexturePrimitive(Size size, Vector3d position, Vector3d angle)
	: m_size(size)
	, m_position(position)
	, m_angle(angle)
	, m_vao(std::make_unique<glance::VertexArray>())
	, m_ibo(std::make_unique<glance::IndexBuffer>())
{
}

TexturePrimitive::~TexturePrimitive()
{
	// TODO: подумать, нужно ли сюда что-то добавить
}

void TexturePrimitive::SetVerticesData(const std::vector<VerticesDataType>& vertices)
{
	m_verticesData = vertices;
}

std::vector<TexturePrimitive::VerticesDataType> TexturePrimitive::GetVerticesData() const
{
	return m_verticesData;
}

void TexturePrimitive::SetIndicesData(const std::vector<IndicesDataType>& indicesData)
{
	m_indicesData = indicesData;
}

std::vector<TexturePrimitive::IndicesDataType> TexturePrimitive::GetIndicesData() const
{
	return m_indicesData;
}

void TexturePrimitive::SetSize(Size size)
{
	m_size = size;
}

Size TexturePrimitive::GetSize() const
{
	return m_size;
}

void TexturePrimitive::SetPosition(Vector3d position)
{
	m_position = position;
}

Vector3d TexturePrimitive::GetPosition() const
{
	return m_position;
}

void TexturePrimitive::SetAngle(Vector3d angle)
{
	m_angle = angle;
}

Vector3d TexturePrimitive::GetAngle() const
{
	return m_angle;
}

// FIXED: переименовать в SetupVerticesData или что-то такое?
void TexturePrimitive::UpdateVerticesData()
{
	m_vbo = std::make_unique<VertexBuffer>(m_verticesData.data(), static_cast<GLsizei>(sizeof(VerticesDataType) * m_verticesData.size()), GL_STATIC_DRAW);

	m_vao->Bind();
	m_vbo->Bind();
	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (3 + 2) * sizeof(VerticesDataType), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, (3 + 2) * sizeof(VerticesDataType), (GLvoid*)(3));
	glEnableVertexAttribArray(0);

	m_vao->Unbind();
}

void TexturePrimitive::UpdateIndicesData()
{
	m_vao->Bind();

	m_ibo->Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indicesData.size() * sizeof(IndicesDataType), m_indicesData.data(), GL_STATIC_DRAW);

	m_vao->Unbind();
}
