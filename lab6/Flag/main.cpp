#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <GLFWInitializer.hpp>
#include "FlagWindow/FlagWindow.h"

int main(void)
{
	glance::GLFWInitializer initGLFW;

	FlagWindow window(800, 600, "Ring");

	window.Run();
}