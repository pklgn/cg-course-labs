#include "../pch.h"
#include "VertexArray.h"

namespace glance
{

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_id);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_id);
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_id);
}

void VertexArray::Unbind()
{
	glBindVertexArray(0);
}

}; // namespace glance