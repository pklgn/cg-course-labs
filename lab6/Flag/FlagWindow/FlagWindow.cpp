#include "FlagWindow.h"

using namespace glance;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

FlagWindow::FlagWindow(int w, int h, const char* title)
	: BaseWindow(w, h, title)
	, m_flag(Size{ static_cast<float>(w), static_cast<float>(h) }, Size{ 400, 250 }, Vector3d{ 0, 0, 0 })
{
	glfwSetKeyCallback(m_window, key_callback);
	glfwSetCursorPosCallback(m_window, mouse_callback);
}

void FlagWindow::Draw(int width, int height)
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	m_flag.SetWindowSize(width, height);

	m_flag.Draw();
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// TODO: реализовать
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	// TODO: реализовать
}
