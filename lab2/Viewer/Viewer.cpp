// Viewer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <tchar.h>
#include <windows.h>
#include <windowsx.h>
#include <gdiplus.h>
#include <memory>
#include <stdexcept>

TCHAR const CLASS_NAME[] = _T("MainWndClass");
TCHAR const WINDOW_TITLE[] = _T("Drawing raster images");

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int MainLoop();
bool RegisterWndClass(HINSTANCE hInstance);
HWND CreateMainWindow(HINSTANCE hInstance);

class CGdiplusInitializer
{
public:
	CGdiplusInitializer()
	{
		Gdiplus::GdiplusStartupInput input;
		Gdiplus::GdiplusStartupOutput output;

		if (Gdiplus::GdiplusStartup(&m_token, &input, &output) != Gdiplus::Ok)
		{
			// �� ������� ���������������� GDI+
			throw std::runtime_error("Failed to initialize GDI+");
		}
	}

	~CGdiplusInitializer()
	{
		Gdiplus::GdiplusShutdown(m_token);
	}

private:
	ULONG_PTR m_token;
};

Gdiplus::Bitmap* g_pBitmap = NULL;

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE /*hPrevInstance*/,
	LPSTR /*lpCmdLine*/,
	int nCmdShow)
{
	// ��������� ������������� GDI+
	try
	{
		CGdiplusInitializer initializer;

		// ������� ������ Image � ������������ ������ � ���������
		// ��������� �� ���� � ����� ��������� std::auto_ptr
		std::auto_ptr<Gdiplus::Image> pImage(new Gdiplus::Image(L"car.jpg"));

		// ������� ��������� ����������� ���������������� �������
		// � �������� �������� RGBA 32 bit
		Gdiplus::Bitmap bmp(pImage->GetWidth(), pImage->GetHeight(), PixelFormat32bppARGB);

		// ������� ������ Graphics ��� ��������� � ������ bmp
		Gdiplus::Graphics g(&bmp);

		// ������ �������� ����������� ������ ���������� ���� ������
		g.DrawImage(pImage.get(), 0, 0);

		// ������� ������ Image
		pImage.release();

		// ��������� ��������� �� ���� � ���������� ����������
		// ��� ������� OnPaint
		g_pBitmap = &bmp;

		// ������������ ����� �������� ����
		if (!RegisterWndClass(hInstance))
		{
			return 1;
		}

		// ������� ������� ���� ����������
		HWND hMainWindow = CreateMainWindow(hInstance);
		if (hMainWindow == NULL)
		{
			return 1;
		}

		// ���������� ������� ���� ����������
		ShowWindow(hMainWindow, nCmdShow);
		UpdateWindow(hMainWindow);

		// ��������� ���� ������� ���������, ���� �� �������
		// ������ � ���������� ����������
		return MainLoop();
	}
	catch (std::runtime_error&)
	{
		return 2;
	}
}

HWND CreateMainWindow(HINSTANCE hInstance)
{
	HWND hMainWindow = CreateWindowEx(
		0,
		CLASS_NAME,
		WINDOW_TITLE,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	return hMainWindow;
}

int MainLoop()
{
	MSG msg;
	BOOL res;
	while ((res = GetMessage(&msg, NULL, 0, 0)) != 0)
	{
		if (res == -1)
		{
			// ��������� ������ - ����� ���������� �� �, ��������,
			// ��������� ������ ����������
		}
		else
		{
			// ���� ��� ��������� � ������� ����������� �������,
			// �� ��������� � ������� ��������� ���������, ������� ���������� �
			// ���� ��������� ������������� �������
			TranslateMessage(&msg);
			// �������� ��������� � ��������������� ������� ���������
			DispatchMessage(&msg);
		}
	}

	// ���� �� ������� ������ � ��� ������ ���������� ��������� WM_QUIT
	// msg.wParam �������� ��� ��������, ���������� ��� ������ ������� PostQuitMessage()
	return msg.wParam;
}

void OnDestroy(HWND /*hWnd*/)
{
	PostQuitMessage(0);
}

void OnPaint(HWND hwnd)
{
	PAINTSTRUCT ps;
	HDC dc = BeginPaint(hwnd, &ps);

	// ������� ������ Graphics
	Gdiplus::Graphics g(dc);

	// ������ ����������� � Graphics
	g.DrawImage(g_pBitmap, 20, 20);

	EndPaint(hwnd, &ps);
}

LRESULT CALLBACK WindowProc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam)
{
	switch (uMsg)
	{
		HANDLE_MSG(hwnd, WM_DESTROY, OnDestroy);
		HANDLE_MSG(hwnd, WM_PAINT, OnPaint);
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

bool RegisterWndClass(HINSTANCE hInstance)
{
	WNDCLASSEX wndClass = {
		sizeof(wndClass), // UINT cbSize;
		CS_HREDRAW | CS_VREDRAW, // UINT style;
		&WindowProc, // WNDPROC lpfnWndProc;
		0, // int cbClsExtra;
		0, // int cbWndExtra;
		hInstance, // HINSTANCE hInstance;
		NULL, // HICON hIcon;
		LoadCursor(NULL, IDC_ARROW), // HCURSOR hCursor;
		(HBRUSH)(COLOR_BTNFACE + 1), // HBRUSH hbrBackground;
		NULL, // LPCTSTR lpszMenuName;
		CLASS_NAME, // LPCTSTR lpszClassName;
		NULL, // HICON hIconSm;
	};

	return RegisterClassEx(&wndClass) != FALSE;
}
