#pragma once
#include <windows.h>
#include "../../Controller/CollageController/CollageController.h"

class WindowView
{
public:
	WindowView(CollageController& collageController, HINSTANCE hInstance, int nCmdShow = SW_SHOW);

	int Show();

	void OnDestroy(HWND /*hWnd*/);
	void OnOpenFile(HWND hwnd, UINT /*codeNotify*/);
	void OnPaint(HWND hwnd);
	void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void OnMouseMove(HWND hwnd, int x, int y, UINT keyFlags);
	void OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags);
	void OnLButtonUp(HWND hwnd, int x, int y, UINT keyFlags);
	BOOL OnEraseBkgnd(HWND hwnd, HDC wParam);

	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	bool RegisterWndClass(HINSTANCE hInstance);
	void InitFileNameStructure(HWND hwndOwner, OPENFILENAME* pOpenFileName, TCHAR* pFileName, DWORD maxFileName);

	HINSTANCE m_hInstance;
	int m_nCmdShow;

	CollageController& m_collageController;
};
