#pragma once
#include <GL/glew.h>

namespace glance
{

class IndexBufferObject
{
public:
	IndexBufferObject();
	~IndexBufferObject();

	void Bind() const;
	void Unbind() const;

	void SetData(const unsigned int* data, unsigned int count, GLenum usage);

	unsigned int GetCount() const;

	operator GLuint() const;

private:
	unsigned int m_id;
	unsigned int m_count;
};

} // namespace glance