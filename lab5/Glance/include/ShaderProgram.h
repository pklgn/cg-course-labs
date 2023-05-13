#pragma once
#include <string>
#include <glm/glm.hpp>
#include <Shader.h>

namespace glance
{

class ShaderProgram
{
public:
	ShaderProgram();
	ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader);
	ShaderProgram(const std::string& vertexPath, const std::string& fragmentPath);
	~ShaderProgram();

	// FIXED: подумать, нужно ли делать эти методы константными
	void AttachShader(const Shader& shader) const;
	void DetachShader(const Shader& shader) const;
	void Link() const;
	void Use() const;
	void Unuse() const;

	void SetUniform1f(const char* name, float value) const;
	void SetUniform1i(const char* name, int value) const;
	void SetUniform2f(const char* name, glm::vec2 value) const;
	void SetUniform3f(const char* name, glm::vec3 value) const;
	void SetUniform4f(const char* name, glm::vec4 value) const;
	void SetUniform4fv(const char* name, glm::mat4 value) const;

	operator GLuint() const;

	ShaderProgram(const ShaderProgram&) = delete;
	void operator=(const ShaderProgram&) = delete;

private:
	GLuint m_id;
};

}; // namespace glance