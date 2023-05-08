#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <GLFWInitializer.hpp>
#include "CottageWindow/CottageWindow.h"

int main(void)
{
	glance::GLFWInitializer initGLFW;

	CottageWindow window(800, 600, "Cottage");

	window.Run();
}