#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <GLFWInitializer.hpp>
#include "SnubCubeWindow/SnubCubeWindow.h"

int main(void)
{
	GLFWInitializer initGLFW;

	SnubCubeWindow window(800, 600, "Snub Cube");

	window.Run();
}