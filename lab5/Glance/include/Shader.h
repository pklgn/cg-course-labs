#pragma once
#include <string>
#include <GL/glew.h>

namespace glance
{

class Shader
{
public:
	Shader(GLenum type);
	~Shader();

	void LoadMemorySource(const char* source);
	void LoadFileSource(const char* filePath);
	void Compile();

	operator GLuint() const;

private:
	static std::string ReadShaderFile(const char* filePath);

private:
	GLuint m_id;
};

}; // namespace glance