#pragma once
#include <Windows.h>

class BaseApp
{
public:
	virtual ~BaseApp() = default;

protected:
	LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	HWND CreateMainWindow(HINSTANCE hInstance);
	bool RegisterWndClass(HINSTANCE hInstance);
	int MainLoop();
};