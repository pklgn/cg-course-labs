#include "../pch.h"

#include <fstream>
#include <string>

#include "OpenGLLog.h"
#include "ShaderProgram.h"

namespace glance
{

ShaderProgram::ShaderProgram()
	: m_id(glCreateProgram())
{
}

ShaderProgram::ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader)
	: ShaderProgram()
{
	AttachShader(vertexShader);
	AttachShader(fragmentShader);

	Link();

	DetachShader(vertexShader);
	DetachShader(fragmentShader);
}


ShaderProgram::ShaderProgram(const std::string& vertexPath, const std::string& fragmentPath)
	: ShaderProgram()
{
	Shader vertexShader(GL_VERTEX_SHADER);
	vertexShader.LoadFileSource(vertexPath.c_str());
	vertexShader.Compile();

	Shader fragmentShader(GL_FRAGMENT_SHADER);
	vertexShader.LoadFileSource(fragmentPath.c_str());
	vertexShader.Compile();

	AttachShader(vertexShader);
	AttachShader(fragmentShader);

	Link();

	DetachShader(vertexShader);
	DetachShader(fragmentShader);
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(m_id);
}

void glance::ShaderProgram::AttachShader(const Shader& shader)
{
	GLint compiled = GL_FALSE;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		GLint length = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		std::vector<GLchar> log(length);
		glGetShaderInfoLog(shader, length, nullptr, log.data());
		throw std::runtime_error(log.data());
	}

	glAttachShader(m_id, shader);
}

void ShaderProgram::DetachShader(const Shader& shader)
{
	glDetachShader(m_id, shader);
}

void ShaderProgram::Link()
{
	glLinkProgram(m_id);

	GLint linked = GL_FALSE;
	glGetProgramiv(m_id, GL_LINK_STATUS, &linked);
	if (!linked)
	{
		GLint length = 0;
		glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &length);
		std::vector<GLchar> log(length);
		glGetProgramInfoLog(m_id, length, nullptr, log.data());

		throw std::runtime_error(log.data());
	}
}

void ShaderProgram::Use()
{
	glUseProgram(m_id);
}

void ShaderProgram::SetUniform1f(const char* name, float value)
{
	GLint location = glGetUniformLocation(m_id, name);
	glUniform1f(location, value);
}

void ShaderProgram::SetUniform1i(const char* name, int value)
{
	GLint location = glGetUniformLocation(m_id, name);
	glUniform1i(location, value);
}

void ShaderProgram::SetUniform2f(const char* name, glm::vec2 value)
{
	GLint location = glGetUniformLocation(m_id, name);
	glUniform2f(location, value.x, value.y);
}

void ShaderProgram::SetUniform3f(const char* name, glm::vec3 value)
{
	GLint location = glGetUniformLocation(m_id, name);
	glUniform3f(location, value.x, value.y, value.z);
}

void ShaderProgram::SetUniform4f(const char* name, glm::vec4 value)
{
	GLint location = glGetUniformLocation(m_id, name);
	glUniform4f(location, value.x, value.y, value.z, value.w);
}

void ShaderProgram::SetUniform4fv(const char* name, glm::mat4 value)
{
	GLint location = glGetUniformLocation(m_id, name);
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

}; // namespace glance