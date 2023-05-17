#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <GLFWInitializer.hpp>
#include "MandelbrotWindow/MandelbrotWindow.h"

int main(void)
{
	glance::GLFWInitializer initGLFW;

	MandelbrotWindow window(800, 600, "Mandelbrot");

	window.Run();
}