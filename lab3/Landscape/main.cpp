#include "LandscapeWindow/LandscapeWindow.h"
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <GLFWInitializer.hpp>
#include <iostream>

int main(void)
{
	GLFWInitializer initGLFW;

	LandscapeWindow window(800, 600, "Landscape");

	window.Run();
}