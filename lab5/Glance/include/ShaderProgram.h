#pragma once
#include <string>
#include <memory>

#include <Shader.h>

namespace glance
{

class ShaderProgram : public std::enable_shared_from_this<ShaderProgram>
{
public:
	ShaderProgram();
	ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader);
	ShaderProgram(const std::string& vertexPath, const std::string& fragmentPath);
	~ShaderProgram();

	void AttachShader(const Shader& shader);
	void DetachShader(const Shader& shader);
	void Link();
	void Use();

	void SetUniform1f(const char* name, float value);
	void SetUniform1i(const char* name, int value);
	void SetUniform2f(const char* name, glm::vec2 value);
	void SetUniform3f(const char* name, glm::vec3 value);
	void SetUniform4f(const char* name, glm::vec4 value);
	void SetUniform4fv(const char* name, glm::mat4 value);

	operator GLuint() const;

private:
	GLuint m_id;
};

}; // namespace glance