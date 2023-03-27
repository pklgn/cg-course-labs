// Viewer_MFC.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Model/Collage/Collage.h"
#include "View/CollageView/CollageView.h"
#include "View/WindowView/WindowView.h"
#include "Controller/CollageController/CollageController.h"

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE /*hPrevInstance*/,
	LPSTR /*lpCmdLine*/,
	int nCmdShow)
{
	Collage collage;
	CollageView collageView(collage);
	CollageController collageController(collage, collageView);
	WindowView windowView(collageController, hInstance);
	return windowView.Show();
}