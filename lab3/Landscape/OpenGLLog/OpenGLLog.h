#pragma once


class OpenGLLog
{
public:
	static void PrintShaderLog(unsigned int shader);
	static void PrintProgramLog(int prog);
	static bool CheckOpenGLError();
};
