#include "../pch.h"
#include "Texture.h"

using namespace glance;

// TODO: добавить в качестве параметров GL_CLAMP_TO_EDGE GL_LINEAR для текстурных параметров
Texture::Texture(const std::string& path, GLenum target)
	: m_target(target)
{
	int width, height;
	unsigned char* data = SOIL_load_image(path.c_str(), &width, &height, 0, SOIL_LOAD_RGB);

	if (!data)
	{
		throw std::runtime_error("Failed to load texture");
	}

	glGenTextures(1, &m_id);
	glBindTexture(m_target, m_id);
	glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(m_target, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(m_target, GL_TEXTURE_WRAP_T, GL_REPEAT);

	if (m_target == GL_TEXTURE_2D)
	{
		glTexImage2D(m_target, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	else if (m_target = GL_TEXTURE_1D)
	{
		glTexImage1D(m_target, 0, GL_RGB, width, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	else
	{
		std::cout << "Invalid target value\n";
	}

	glGenerateMipmap(m_target);
	SOIL_free_image_data(data);

	glBindTexture(m_target, 0);
}

void Texture::Bind(GLenum activeTexture) const
{
	glActiveTexture(activeTexture);
	glBindTexture(m_target, m_id);
}

void ::Texture::Unbind() const
{
	glBindTexture(m_target, 0);
}
