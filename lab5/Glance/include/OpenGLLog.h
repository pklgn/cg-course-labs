#pragma once

namespace glance
{

class OpenGLLog
{
public:
	static void PrintShaderLog(unsigned int shader);
	static void PrintProgramLog(int prog);
	static bool CheckOpenGLError();

private:
	OpenGLLog() = default;
};

}; // namespace glance