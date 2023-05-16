#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <GLFWInitializer.hpp>
#include "CurvatureWindow/CurvatureWindow.h"

int main(void)
{
	glance::GLFWInitializer initGLFW;

	CurvatureWindow window(800, 600, "Cottage");

	window.Run();
}