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
	static void Unbind();

	void SetData(const void* data, size_t size);

	void BindAttribPointer(GLint location, GLenum type, GLuint count, GLuint stride, GLvoid* offset) const;

	VertexBuffer(const VertexBuffer&) = delete;
	void operator=(const VertexBuffer&) = delete;

private:
	GLuint m_id;
	size_t m_size;
	GLenum m_usage;
};

} // namespace glance