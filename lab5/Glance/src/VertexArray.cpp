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

void VertexArray::SetVertexBuffer(GLint location, GLenum type, GLuint count, GLuint stride, intptr_t offset) const
{
	// FIXED: добавил bind для удобства использования и правильной работы
	Bind();
	glVertexAttribPointer(location, count, type, GL_FALSE, stride, (const GLvoid*)offset);
	glEnableVertexAttribArray(location);
	Unbind();
}

void VertexArray::SetIndexBuffer(GLuint buffer) const
{
	// TODO: аналогично предыдущему
	Bind();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
	Unbind();
}

}; // namespace glance