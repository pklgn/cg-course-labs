#include "IndexBuffer.h"

namespace glance
{

IndexBufferObject::IndexBufferObject()
	: m_count(0)
{
	glGenBuffers(1, &m_id);
}

IndexBufferObject::~IndexBufferObject()
{
	glDeleteBuffers(1, &m_id);
}

void IndexBufferObject::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

void IndexBufferObject::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBufferObject::SetData(const unsigned int* data, unsigned int count, GLenum usage)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, usage);
}

unsigned int IndexBufferObject::GetCount() const
{
	return m_count;
}

IndexBufferObject::operator GLuint() const
{
	return m_id;
}

}