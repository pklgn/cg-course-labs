#include <GLFW/glfw3.h>
#include "GraphWindow/GraphWindow.h"
#include "Common/GLFWInitializer.h"
#include <iostream>

int main(void)
{
	GLFWInitializer initGLFW;

	GraphWindow window(800, 600, "Graph");
	
	window.Run();
}