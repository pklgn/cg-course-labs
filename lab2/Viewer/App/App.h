#pragma once
#include <vector>
#include "../ImageFrame/ImageFrame.h"

class App
{
public:
	App(HINSTANCE hInstance, int nCmdShow = SW_SHOW);

	int Run();

	void OnDestroy(HWND /*hWnd*/);
	void OnOpenFile(HWND hwnd, UINT /*codeNotify*/);
	void OnPaint(HWND hwnd);
	void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	BOOL OnEraseBkgnd(HWND hwnd, HDC wParam);

	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	void InitFileNameStructure(HWND hwndOwner, OPENFILENAME* pOpenFileName, TCHAR* pFileName, DWORD maxFileName);

	bool m_isRunning = false;
	HINSTANCE m_hInstance;
	int m_nCmdShow;
	std::vector<std::unique_ptr<ImageFrame>> m_mediaFrames;
};