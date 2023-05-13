#include "../pch.h"
#include "VertexBuffer.h"

namespace glance
{

VertexBuffer::VertexBuffer(const void* data, size_t size, GLenum usage)
	: m_size(size)
	, m_usage(usage)
{

	glGenBuffers(1, &m_id);
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
	glBufferData(GL_ARRAY_BUFFER, m_size, data, m_usage);
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

void VertexBuffer::SetData(const void* data, size_t size)
{
	if (m_size != size)
	{
		glDeleteBuffers(1, &m_id);

		m_size = size;
		glGenBuffers(1, &m_id);
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
		glBufferData(GL_ARRAY_BUFFER, m_size, data, m_usage);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	else
	{
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}
}

void VertexBuffer::BindAttribPointer(GLint location, GLenum type, GLuint count, GLuint stride, GLvoid* offset) const
{
	Bind();
	glVertexAttribPointer(location, count, type, GL_FALSE, stride, (const GLvoid*)offset);
	glEnableVertexAttribArray(location);
	Unbind();
}

}; // namespace glance