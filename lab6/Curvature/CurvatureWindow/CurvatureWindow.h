#pragma once
#include <memory>
#include <BaseWindow.hpp>
#include "../Curvature/Curvature.h"
#include "OpenGLPrimitive/Skybox.h"
#include "ShaderMVPUniformMap.h"

class CurvatureWindow : public glance::BaseWindow
{
public:
	CurvatureWindow(int w, int h, const char* title);

private:
	Curvature m_curvature;

private:
	void Draw(int width, int height) override;

	void MousePositionCallback(GLFWwindow* window, double positionX, double positionY);
	void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void WindowSizeCallback(GLFWwindow* window, int width, int height);

private:
	class GLFWCallbackWrapper
	{
	public:
		GLFWCallbackWrapper() = delete;
		GLFWCallbackWrapper(const GLFWCallbackWrapper&) = delete;
		GLFWCallbackWrapper(GLFWCallbackWrapper&&) = delete;
		~GLFWCallbackWrapper() = delete;

		static void MousePositionCallback(GLFWwindow* window, double positionX, double positionY);
		static void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void WindowSizeCallback(GLFWwindow* window, int width, int height);
		static void SetWindow(CurvatureWindow* window);

	private:
		static CurvatureWindow* s_window;
	};
};
