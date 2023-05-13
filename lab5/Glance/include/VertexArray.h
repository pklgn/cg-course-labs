#pragma once
#include <GL/glew.h>

namespace glance
{
// TODO: подумать, возможно стоит все классы буферы унаследовать от единого базового класса
class VertexArray
{
	// FIXED: сделать защиту от копирования
public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	static void Unbind();

	void SetVertexBuffer(GLint location, GLenum type, GLuint count, GLuint stride, intptr_t offset) const;
	void SetIndexBuffer(GLuint buffer) const;

private:
	GLuint m_id;
};

}; // namespace glance