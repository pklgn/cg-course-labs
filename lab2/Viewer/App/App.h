#pragma once
#include <deque>
#include <memory>
#include "../MediaFrame/IMediaFrame.h"

class App
{
public:
	App(HINSTANCE hInstance, int nCmdShow = SW_SHOW);

	int Run();

	void OnDestroy(HWND /*hWnd*/);
	void OnOpenFile(HWND hwnd, UINT /*codeNotify*/);
	void OnPaint(HWND hwnd);
	void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);


private:
	void InitFileNameStructure(HWND hwndOwner, OPENFILENAME* pOpenFileName, TCHAR* pFileName, DWORD maxFileName);

	//LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	bool m_isRunning = false;
	HINSTANCE m_hInstance;
	int m_nCmdShow;
	std::deque<std::unique_ptr<IMediaFrame>> m_mediaFrames;
	UINT m_mediaFrameIndex;
};