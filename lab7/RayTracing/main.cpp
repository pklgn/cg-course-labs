#include <iostream>
#include "Application/Application.h"

#ifdef __cplusplus
extern "C"
#endif
int main(int /*argc*/, char** /*argv*/)
{
	Application app;
	app.MainLoop();
	return 0;
}