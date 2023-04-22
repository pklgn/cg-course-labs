#pragma once
#include <string>

class ShaderProgram
{
public:
	static unsigned int CreateShaderProgram(const char* vp, const char* fp);

private:
	static std::string ReadShaderFile(const char* filePath);
	static unsigned int PrepareShader(unsigned int shaderTYPE, const char* shaderPath);
	static int FinalizeShaderProgram(unsigned int shaderProgram);
};
