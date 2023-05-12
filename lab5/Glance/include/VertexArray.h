﻿#pragma once
#include <GL/glew.h>

namespace glance
{

class VertexArray
{
	// TODO: сделать защиту от копирования
public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void Unbind() const;

	void SetVertexBuffer(GLint location, GLenum type, GLuint count, GLuint stride, intptr_t offset) const;
	void SetIndexBuffer(GLuint buffer) const;

private:
	GLuint m_id;
};

}; // namespace glance