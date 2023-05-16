#include "../pch.h"
#include "Shader.h"

namespace glance
{

Shader::Shader(GLenum type)
	: m_id(glCreateShader(type))
{
}

Shader::~Shader()
{
	glDeleteShader(m_id);
}

void Shader::LoadMemorySource(const char* source)
{
	glShaderSource(m_id, 1, &source, nullptr);
}

void Shader::LoadFileSource(const char* filePath)
{
	auto source = ReadShaderFile(filePath);
	LoadMemorySource(source.c_str());
}

void Shader::Compile()
{
	glCompileShader(m_id);

	GLint success;
	GLchar infoLog[1024];
	glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(m_id, 1024, nullptr, infoLog);
		throw std::runtime_error("Shader compilation error: " + std::string(infoLog));
	}
}

Shader::operator GLuint() const
{
	return m_id;
}

std::string Shader::ReadShaderFile(const char* filePath)
{
	std::string content;
	std::ifstream fileStream(filePath, std::ios::in);
	std::string line = "";
	while (!fileStream.eof())
	{
		getline(fileStream, line);
		content.append(line + "\n");
	}
	fileStream.close();

	return content;
}

}; // namespace glance