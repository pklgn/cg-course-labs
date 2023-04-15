#include <GL/glew.h>
#include <string>
#include <fstream>
#include <iostream>
#include "ShaderProgram.h"
#include "../OpenGLLog/OpenGLLog.h"

unsigned int ShaderProgram::CreateShaderProgram(const char* vp, const char* fp)
{
	OpenGLLog::CheckOpenGLError();
	GLuint vShader = PrepareShader(GL_VERTEX_SHADER, vp);
	GLuint fShader = PrepareShader(GL_FRAGMENT_SHADER, fp);
	GLuint vfprogram = glCreateProgram();
	glAttachShader(vfprogram, vShader);
	glAttachShader(vfprogram, fShader);
	FinalizeShaderProgram(vfprogram);

	return vfprogram;
}

std::string ShaderProgram::ReadShaderFile(const char* filePath)
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

unsigned int ShaderProgram::PrepareShader(unsigned int shaderTYPE, const char* shaderPath)
{
	GLint shaderCompiled;
	std::string shaderStr = ReadShaderFile(shaderPath);
	const char* shaderSrc = shaderStr.c_str();
	GLuint shaderRef = glCreateShader(shaderTYPE);
	glShaderSource(shaderRef, 1, &shaderSrc, NULL);
	glCompileShader(shaderRef);
	OpenGLLog::CheckOpenGLError();
	glGetShaderiv(shaderRef, GL_COMPILE_STATUS, &shaderCompiled);
	if (shaderCompiled != 1)
	{
		if (shaderTYPE == 35633)
			std::cout << "Vertex ";
		if (shaderTYPE == 36488)
			std::cout << "Tess Control ";
		if (shaderTYPE == 36487)
			std::cout << "Tess Eval ";
		if (shaderTYPE == 36313)
			std::cout << "Geometry ";
		if (shaderTYPE == 35632)
			std::cout << "Fragment ";
		std::cout << "shader compilation error." << std::endl;
		OpenGLLog::PrintShaderLog(shaderRef);
	}

	return shaderRef;
}

int ShaderProgram::FinalizeShaderProgram(unsigned int shaderProgram)
{
	GLint linked;
	glLinkProgram(shaderProgram);
	OpenGLLog::CheckOpenGLError();
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linked);
	if (linked != 1)
	{
		std::cout << "linking failed" << std::endl;
		OpenGLLog::PrintProgramLog(shaderProgram);
	}

	return shaderProgram;
}
