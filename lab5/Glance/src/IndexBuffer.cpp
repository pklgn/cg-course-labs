#include "../pch.h"
#include "IndexBuffer.h"

namespace glance
{

IndexBuffer::IndexBuffer()
	: m_count(0)
{
	glGenBuffers(1, &m_id);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_id);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::SetData(const unsigned int* data, unsigned int count, GLenum usage)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, usage);
}

unsigned int IndexBuffer::GetCount() const
{
	return m_count;
}

IndexBuffer::operator GLuint() const
{
	return m_id;
}

}