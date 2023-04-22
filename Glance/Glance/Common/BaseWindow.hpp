#pragma once
#include "../pch.h"
#include "../Common/ShaderProgram/ShaderProgram.h"
#include <stdexcept>

class BaseWindow
{
public:
	BaseWindow(int w, int h, const char* title)
		: m_window{ CreateWindow(w, h, title) }
	{
		if (!m_window)
		{
			throw std::runtime_error("Failed to create window");
		}
		m_time = glfwGetTime();
	}
	BaseWindow(const BaseWindow&) = delete;
	BaseWindow& operator=(const BaseWindow&) = delete;

	virtual ~BaseWindow()
	{
		glfwDestroyWindow(m_window);
	}

	void Run()
	{
		glfwMakeContextCurrent(m_window);

		if (glewInit() != GLEW_OK)
		{
			std::cout << "Error!\n";
		}

		m_shaderProgram = ShaderProgram::CreateShaderProgram("Shaders/Vertex.shader", "Shaders/Fragment.shader");
		glUseProgram(m_shaderProgram);

		while (!glfwWindowShouldClose(m_window))
		{
			int w, h;
			glfwGetFramebufferSize(m_window, &w, &h);
			Draw(w, h);
			glfwSwapBuffers(m_window);
			glfwPollEvents();
		}
	}

protected:
	GLFWwindow* m_window;
	unsigned int m_shaderProgram;
	double m_time;

private:
	virtual void Draw(int width, int height) = 0;

	static GLFWwindow* CreateWindow(int w, int h, const char* title)
	{
		glfwWindowHint(GLFW_DEPTH_BITS, 24);
		return glfwCreateWindow(w, h, title, nullptr, nullptr);
	}
};