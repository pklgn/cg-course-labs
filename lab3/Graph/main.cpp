#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include "GraphWindow/GraphWindow.h"
#include "Common/GLFWInitializer.h"
#include <iostream>

int main(void)
{
	GLFWInitializer initGLFW;
	
	GraphWindow window(800, 600, "Graph");
	
	window.Run();

	// just for fun
	std::cout << glGetString(GL_VERSION) << std::endl;
}