#pragma once
#include <string>
#include <GL/glew.h>

namespace glance
{
// FIXED: защитить от копирования
class Texture
{
public:
	Texture(const std::string& path);

	void Bind(GLenum activeTexture = GL_TEXTURE0) const;
	static void Unbind();

	// FIXED: избавиться от методов GetWidht() и GetHeight()

	Texture(const Texture&) = delete;
	void operator=(const Texture&) = delete;

private:
	GLuint m_id;
};

}; // namespace glance