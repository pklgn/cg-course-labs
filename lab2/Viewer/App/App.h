#pragma once
#include "../MediaFrame/IMediaFrame.h"

class App
{
public:
	int Run(HINSTANCE hInstance, int nCmdShow);

private:
	HWND CreateMainWindow(HINSTANCE hInstance);
	bool RegisterWndClass(HINSTANCE hInstance);
	int MainLoop();
	LRESULT CALLBACK WindowProc(
		HWND hwnd,
		UINT uMsg,
		WPARAM wParam,
		LPARAM lParam);

	void InitFileNameStructure(HWND hwndOwner, OPENFILENAME* pOpenFileName, TCHAR* pFileName, DWORD maxFileName);

	void OnDestroy(HWND /*hWnd*/);
	void OnOpenFile(HWND hwnd, UINT /*codeNotify*/);

	HINSTANCE m_hInstance;
	std::vector<std::unique_ptr<IMediaFrame>> m_mediaFrames;
};