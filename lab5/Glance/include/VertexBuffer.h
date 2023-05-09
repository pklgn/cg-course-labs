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

private:
	GLuint m_id;
	size_t m_size;
	GLenum m_usage;
};

} // namespace glance