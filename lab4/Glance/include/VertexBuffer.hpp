#include <GL/glew.h>

class VertexBuffer
{
public:
	VertexBuffer() {}

	~VertexBuffer()
	{
		glDeleteBuffers(1, &id);
	}

	void Create(GLsizeiptr size, const void* data, GLenum usage)
	{
		glGenBuffers(1, &id);
		glBindBuffer(GL_ARRAY_BUFFER, id);
		glBufferData(GL_ARRAY_BUFFER, size, data, usage);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, id);
	}

	void Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

private:
	GLuint id;
};