#pragma once
#include <string>
#include <GL/glew.h>

namespace glance
{

class CubemapTexture
{
public:
	CubemapTexture(const std::vector<std::string>& faces);

	void Bind(GLenum activeTexture = GL_TEXTURE0) const;
	static void Unbind();

private:
	GLuint m_id;
};

}; // namespace glance