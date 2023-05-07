#include "../pch.h"
#include "VertexArray.h"

namespace glance
{

VertexArrayObject::VertexArrayObject()
{
	glGenVertexArrays(1, &m_id);
}

VertexArrayObject::~VertexArrayObject()
{
	glDeleteVertexArrays(1, &m_id);
}

void VertexArrayObject::Bind() const
{
	glBindVertexArray(m_id);
}

void VertexArrayObject::Unbind() const
{
	glBindVertexArray(0);
}

void VertexArrayObject::SetVertexBuffer(GLint location, GLenum type, GLuint count, GLuint stride, intptr_t offset) const
{
	glVertexAttribPointer(location, count, type, GL_FALSE, stride, (const GLvoid*)offset);
	glEnableVertexAttribArray(location);
}

void VertexArrayObject::SetIndexBuffer(GLuint buffer) const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
}

}; // namespace glance