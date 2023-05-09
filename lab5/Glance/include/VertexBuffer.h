#pragma once

#include <GL/glew.h>

namespace glance
{

class VertexBuffer
{
public:
	VertexBuffer(const void* data, size_t size, GLenum usage = GL_STATIC_DRAW);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

	void SetData(const void* data, size_t size);

	void BindAttribPointer(GLint location, GLenum type, GLuint count, GLuint stride, GLvoid* offset) const;

private:
	GLuint m_id;
	size_t m_size;
	GLenum m_usage;
};

} // namespace glance