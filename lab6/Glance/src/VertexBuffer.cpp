#include "../pch.h"
#include "VertexBuffer.h"

namespace glance
{

VertexBuffer::VertexBuffer(const void* data, GLsizei size, GLenum usage)
	: m_size(size)
{

	glGenBuffers(1, &m_id);
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
	glBufferData(GL_ARRAY_BUFFER, m_size, data, usage);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_id);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void VertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GLsizei VertexBuffer::GetSize() const
{
	return m_size;
}

}; // namespace glance