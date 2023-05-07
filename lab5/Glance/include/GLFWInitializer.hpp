#pragma once
#include "../pch.h"
#include <stdexcept>

namespace glance
{

class GLFWInitializer final
{
public:
	GLFWInitializer()
	{
		if (!glfwInit())
			throw std::runtime_error("Failed to initialize GLFW");
	}

	GLFWInitializer(const GLFWInitializer&) = delete;
	GLFWInitializer& operator=(const GLFWInitializer&) = delete;

	~GLFWInitializer()
	{
		glfwTerminate();
	}
};

}; // namespace glance