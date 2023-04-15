#include <gl/glew.h>
#include "Common/GLFWInitializer.h"
#include "LandscapeWindow/LandscapeWindow.h"
#include <GLFW/glfw3.h>
#include <iostream>

int main(void)
{
	GLFWInitializer initGLFW;

	LandscapeWindow window(800, 600, "Landscape");

	window.Run();
}