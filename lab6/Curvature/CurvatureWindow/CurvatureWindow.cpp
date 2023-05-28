#include "CurvatureWindow.h"
#include "../Curvature/Curvature.h"

using namespace glance;

CurvatureWindow* CurvatureWindow::GLFWCallbackWrapper::s_window = nullptr;

CurvatureWindow::CurvatureWindow(int w, int h, const char* title)
	: BaseWindow(w, h, title)
	, m_curvature(Size{ static_cast<float>(w), static_cast<float>(h) }, Size{ 450, 450 }, Vector3d{ 0, -225, 0 })
{
	GLFWCallbackWrapper::SetWindow(this);
	glfwSetCursorPosCallback(m_window, GLFWCallbackWrapper::MousePositionCallback);
	glfwSetKeyCallback(m_window, GLFWCallbackWrapper::KeyboardCallback);
	glfwSetWindowSizeCallback(m_window, GLFWCallbackWrapper::WindowSizeCallback);

	WindowSizeCallback(m_window, w, h);
}

void CurvatureWindow::Draw(int width, int height)
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	m_curvature.Draw();
}

void CurvatureWindow::MousePositionCallback(GLFWwindow* window, double positionX, double positionY)
{
	// TODO: реализовать
}

void CurvatureWindow::KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// TODO: реализовать
}

void CurvatureWindow::WindowSizeCallback(GLFWwindow* window, int width, int height)
{
	// TODO: нужно ли здесь что-то делать с viewport'ом?
	glViewport(0, 0, width, height);
	m_curvature.SetWindowSize(width, height);
}

void CurvatureWindow::GLFWCallbackWrapper::MousePositionCallback(GLFWwindow* window, double positionX, double positionY)
{
	s_window->MousePositionCallback(window, positionX, positionY);
}

void CurvatureWindow::GLFWCallbackWrapper::KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	s_window->KeyboardCallback(window, key, scancode, action, mods);
}

void CurvatureWindow::GLFWCallbackWrapper::WindowSizeCallback(GLFWwindow* window, int width, int height)
{
	s_window->WindowSizeCallback(window, width, height);
}

void CurvatureWindow::GLFWCallbackWrapper::SetWindow(CurvatureWindow* window)
{
	GLFWCallbackWrapper::s_window = window;
}
