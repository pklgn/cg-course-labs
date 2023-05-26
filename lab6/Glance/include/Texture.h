#pragma once
#include <string>
#include <GL/glew.h>

namespace glance
{
// FIXED: защитить от копирования
class Texture
{
public:
	Texture(const std::string& path, GLenum target = GL_TEXTURE_2D);

	void Bind(GLenum activeTexture = GL_TEXTURE0) const;
	void Unbind() const;

	// FIXED: избавиться от методов GetWidht() и GetHeight()

	Texture(const Texture&) = delete;
	void operator=(const Texture&) = delete;

private:
	GLuint m_id;
	GLenum m_target;
};

}; // namespace glance