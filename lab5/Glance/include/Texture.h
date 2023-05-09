#pragma once
#include <string>
#include <GL/glew.h>

namespace glance
{

class Texture
{
public:
	Texture(const std::string& path);

	void Bind(GLenum activeTexture = GL_TEXTURE0) const;
	void Unbind() const;

	int GetWidth() const;
	int GetHeight() const;

private:
	GLuint m_id;
	int m_width;
	int m_height;
};

}; // namespace glance