#pragma once

#include <GL/glew.h>

namespace glance
{

class VertexBuffer
{
public:
	VertexBuffer(const void* data, GLsizei size, GLenum usage = GL_STATIC_DRAW);
	~VertexBuffer();

	void Bind() const;
	static void Unbind();

	GLsizei GetSize() const;

	VertexBuffer(const VertexBuffer&) = delete;
	void operator=(const VertexBuffer&) = delete;

private:
	GLuint m_id;
	GLsizei m_size;
};

} // namespace glance