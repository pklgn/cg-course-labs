#include "MandelbrotWindow.h"

using namespace glance;

bool IS_FIRST_CLICK = true;
double LAST_X = 0;
double LAST_Y = 0;
int ZOOM = 0;
bool IS_MOUSE_BUTTON_LEFT_DOWN = false;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouseButtonCallback(GLFWwindow* _window, int button, int action, int mods);

MandelbrotWindow::MandelbrotWindow(int w, int h, const char* title)
	: BaseWindow(w, h, title)
	, m_mandelbrot(Size{ static_cast<float>(w), static_cast<float>(h) }, Size{ static_cast<float>(w), static_cast<float>(h) }, Vector3d{ 0, 0, 0 })
	, m_mouse(0.0, 0.0, 0.01)
{
	glfwSetKeyCallback(m_window, key_callback);
	glfwSetCursorPosCallback(m_window, mouse_callback);
	glfwSetMouseButtonCallback(m_window, mouseButtonCallback);
}

void MandelbrotWindow::Draw(int width, int height)
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	m_mandelbrot.SetWindowSize(width, height);
	if (IS_MOUSE_BUTTON_LEFT_DOWN)
	{
		double xpos;
		double ypos;
		glfwGetCursorPos(m_window, &xpos, &ypos);

		if (IS_FIRST_CLICK)
		{
			IS_FIRST_CLICK = false;
			LAST_X = xpos;
			LAST_Y = ypos;
		}

		double deltaX = xpos - LAST_X;
		double deltaY = ypos - LAST_Y;

		LAST_X = xpos;
		LAST_Y = ypos;

		m_mouse.MoveMouse(static_cast<float>(deltaX), static_cast<float>(deltaY));
	}
	if (0 < ZOOM)
	{
		m_mouse.ZoomMouse();
		ZOOM = 0;
	}
	else if (ZOOM < 0)
	{
		m_mouse.UnzoomMouse();
		ZOOM = 0;
	}

	m_mandelbrot.SetMousePosition(Vector3d{ m_mouse.GetX(), m_mouse.GetY(), m_mouse.GetZoomNormalized() });
	m_mandelbrot.Draw();
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// TODO: реализовать
	// ESC to quit
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
		return;
	}

	if (key == GLFW_KEY_PAGE_UP && action == GLFW_PRESS)
	{
		ZOOM = 1;
	}

	if (key == GLFW_KEY_PAGE_DOWN && action == GLFW_PRESS)
	{
		ZOOM = -1;
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	// TODO: реализовать
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
		if (action == GLFW_PRESS)
		{
			IS_MOUSE_BUTTON_LEFT_DOWN = true;
		}
		else if (action == GLFW_RELEASE)
		{
			IS_MOUSE_BUTTON_LEFT_DOWN = false;
			IS_FIRST_CLICK = true;
		}
	}
}