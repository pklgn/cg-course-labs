#include "../pch.h"
#include "Texture.h"

using namespace glance;

Texture::Texture(const std::string& path)
{
	unsigned char* data = SOIL_load_image(path.c_str(), &m_width, &m_height, 0, SOIL_LOAD_RGB);

	if (!data)
	{
		throw std::runtime_error("Failed to load texture");
	}

	glGenTextures(1, &m_id);
	glBindTexture(GL_TEXTURE_2D, m_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(data);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void glance::Texture::Bind(GLenum activeTexture) const
{
	glActiveTexture(activeTexture);
	glBindTexture(GL_TEXTURE_2D, m_id);
}

void glance::Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

int glance::Texture::GetWidth() const
{
	return m_width;
}

int glance::Texture::GetHeight() const
{
	return m_height;
}
