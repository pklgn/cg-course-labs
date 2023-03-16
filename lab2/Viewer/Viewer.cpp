// Viewer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "App/App.h"


int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE /*hPrevInstance*/,
	LPSTR /*lpCmdLine*/,
	int nCmdShow)
{
	App app(hInstance, nCmdShow);
	return app.Run();
}