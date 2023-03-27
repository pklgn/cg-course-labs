#pragma once
#include "../../Controller/CollageController/CollageController.h"
#include <windows.h>

class WindowView
{
public:
	WindowView(CollageController& collageController, HINSTANCE hInstance, int nCmdShow = SW_SHOW);

	int Show();

	static BOOL OnEraseBkgnd(HWND hwnd, HDC wParam);
	void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void OnDestroy(HWND /*hWnd*/);
	void OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags);
	void OnLButtonUp(HWND hwnd, int x, int y, UINT keyFlags);
	void OnMouseMove(HWND hwnd, int x, int y, UINT keyFlags);
	void OnOpenFile(HWND hwnd, UINT /*codeNotify*/);
	void OnPaint(HWND hwnd);
	void OnSize(HWND hwnd, UINT state, int cx, int cy);

	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	void InitFileNameStructure(HWND hwndOwner, OPENFILENAME* pOpenFileName, TCHAR* pFileName, DWORD maxFileName) const;

	int m_nCmdShow;
	HINSTANCE m_hInstance;

	CollageController& m_collageController;
};
