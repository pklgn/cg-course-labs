// Viewer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <tchar.h>
#include <windows.h>
#include <winuser.h>
#include <windowsx.h>
#include <gdiplus.h>
#include <memory>
#include <stdexcept>
#include <functional>

TCHAR const CLASS_NAME[] = _T("MainWndClass");
TCHAR const WINDOW_TITLE[] = _T("Drawing raster images");
UINT const IDM_NEW = 1;

HINSTANCE g_hInstance = NULL;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int MainLoop();
bool RegisterWndClass(HINSTANCE hInstance);
HWND CreateMainWindow(HINSTANCE hInstance);

using namespace Gdiplus;

class CGdiplusInitializer
{
public:
	CGdiplusInitializer()
	{
		Gdiplus::GdiplusStartupInput input;
		Gdiplus::GdiplusStartupOutput output;

		if (Gdiplus::GdiplusStartup(&m_token, &input, &output) != Gdiplus::Ok)
		{
			// Не удалось инициализировать GDI+
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

std::unique_ptr<Bitmap> g_pBitmap = NULL;

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE /*hPrevInstance*/,
	LPSTR /*lpCmdLine*/,
	int nCmdShow)
{
	// Выполняем инициализацию GDI+
	try
	{
		CGdiplusInitializer initializer;

		// Создаем объект Image в динамической памяти и сохраняем
		// указатель на него в умном указателе std::auto_ptr
		std::auto_ptr<Gdiplus::Image> pImage(new Gdiplus::Image(L"car.jpg"));

		// Создаем растровое изображение соответствующего размера
		// с форматом пикселей RGBA 32 bit
		std::unique_ptr<Gdiplus::Bitmap> bmp = std::make_unique<Gdiplus::Bitmap>(pImage->GetWidth(), pImage->GetHeight(), PixelFormat32bppARGB);

		// Создаем объект Graphics дли рисования в растре bmp
		Gdiplus::Graphics g(bmp.get());

		// Рисуем исходное изображение внутрь созданного нами растра
		g.DrawImage(pImage.get(), 0, 0);

		// удаляем объект Image
		pImage.release();

		// Сохраняем указатель на раст в глобальной переменной
		// для функции OnPaint
		g_pBitmap = std::move(bmp);

		// Регистрируем класс главного окна
		if (!RegisterWndClass(hInstance))
		{
			return 1;
		}

		// Создаю меню для окна приложения
		HMENU hMenu = CreateMenu();
		HMENU hSubMenu = CreatePopupMenu();
		AppendMenu(hSubMenu, MF_STRING, IDM_NEW, L"New");
		AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hSubMenu, L"File");

		// Создаем главное окно приложения
		HWND hMainWindow = CreateMainWindow(hInstance);
		if (hMainWindow == NULL)
		{
			return 1;
		}

		//Добавляем меню к главному окну приложения
		SetMenu(hMainWindow, hMenu);

		// Показываем главное окно приложения
		ShowWindow(hMainWindow, nCmdShow);
		UpdateWindow(hMainWindow);

		// Запускаем цикл выборки сообщений, пока не получим
		// сигнал о завершении приложения
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
			// произошла ошибка - нужно обработать ее и, вероятно,
			// завершить работу приложения
		}
		else
		{
			// Если это сообщение о нажатии виртуальной клавиши,
			// то добавляем в очередь сообщений сообщения, несущие информацию о
			// коде вводимого пользователем символа
			TranslateMessage(&msg);
			// передаем сообщение в соответствующую оконную процедуру
			DispatchMessage(&msg);
		}
	}

	// сюда мы попадем только в том случае извлечения сообщения WM_QUIT
	// msg.wParam содержит код возврата, помещенный при помощи функции PostQuitMessage()
	return msg.wParam;
}

void OnDestroy(HWND /*hWnd*/)
{
	g_pBitmap.reset();
	PostQuitMessage(0);
}

void OnPaint(HWND hwnd)
{
	PAINTSTRUCT ps;
	HDC dc = BeginPaint(hwnd, &ps);

	// Создаем объект Graphics
	Gdiplus::Graphics g(dc);

	// здесь нужно посчитать размеры изображения и в случае нехватки места уменишить размер с сохранением пропорций
	auto bitmapWidth = g_pBitmap->GetWidth();
	auto bitmapHeight = g_pBitmap->GetHeight();
	auto aspectRatio = g_pBitmap->GetWidth() / static_cast<double>(g_pBitmap->GetHeight());
	RECT clientRect;
	GetClientRect(hwnd, &clientRect);
	auto clientWidth = clientRect.right - clientRect.left;
	auto clientHeight = clientRect.bottom - clientRect.top;
	UINT clientAspectRatio = clientWidth / static_cast<double>(clientHeight);

	double resizeCoef = 1;

	/* если ШИРИНА выходит за рамки изображения, то мы обращаем внимание
	* на соотношение сторон:
	*	если оно портретное, то вычисляем соотношение ВЫСОТ
	*	иначе в качестве коэффициента берем соотношение ШИРИН
	* после этого коэф масштабирования уменьшит изображение по БОЛЬШЕМУ из двух
	* параметров
	* 
	* однако после этой операции может оказаться так, что МЕНЬШИЙ из параметров
	* все равно будет выходить за границы окна по своей оси
	* связано это с тем, что в общем случае соотношение сторон окна 
	* не совпадает с соотношением сторон изображения
	*/
	if (clientWidth < g_pBitmap->GetWidth())
	{
		resizeCoef *= (aspectRatio < 1)
			? clientHeight / static_cast<double>(g_pBitmap->GetHeight())
			: clientWidth / static_cast<double>(g_pBitmap->GetWidth());
	}
	if (clientHeight < g_pBitmap->GetHeight() * resizeCoef)
	{
		resizeCoef *= clientHeight / (static_cast<double>(g_pBitmap->GetHeight() * resizeCoef));
	}

	Image* scaleImage = new Bitmap(g_pBitmap->GetWidth() * resizeCoef, g_pBitmap->GetHeight() * resizeCoef, PixelFormat32bppARGB);

	Gdiplus::Graphics scaleG(scaleImage);

	scaleG.ScaleTransform(resizeCoef, resizeCoef);
	scaleG.DrawImage(g_pBitmap.get(), 0, 0);

	auto thumbnail = g_pBitmap->GetThumbnailImage(g_pBitmap->GetWidth() * resizeCoef, g_pBitmap->GetHeight() * resizeCoef, NULL, NULL);
	//Рисуем изображение в Graphics
	g.DrawImage(thumbnail, (INT)(clientWidth / 2 - g_pBitmap->GetWidth() * resizeCoef / 2), (INT)(clientHeight / 2 - g_pBitmap->GetHeight() * resizeCoef / 2));

	EndPaint(hwnd, &ps);
}

void InitFileNameStructure(HWND hwndOwner, OPENFILENAME* pOpenFileName, TCHAR* pFileName, DWORD maxFileName)
{
	ZeroMemory(pOpenFileName, sizeof(OPENFILENAME));

	pOpenFileName->lStructSize = sizeof(OPENFILENAME);
	pOpenFileName->hwndOwner = hwndOwner;
	pOpenFileName->hInstance = g_hInstance;
	pOpenFileName->nMaxFile = maxFileName;
	pOpenFileName->lpstrFile = pFileName;
	pOpenFileName->lpstrFilter = _T("Images (BMP, PNG, JPG, TIFF)\0*.bmp;*.png;*.jpg;*.tif\0")
								 _T("All files\0*.*\0")
								 _T("\0");
}

void OnOpenFile(HWND hwnd, UINT /*codeNotify*/)
{
	OPENFILENAME ofn;
	TCHAR fileName[MAX_PATH + 1] = _T("");
	InitFileNameStructure(hwnd, &ofn, fileName, MAX_PATH);

	if (GetOpenFileName(&ofn))
	{
		Image img(ofn.lpstrFile);

		if (img.GetLastStatus() == Ok)
		{
			g_pBitmap.reset(std::move(new Bitmap(img.GetWidth(), img.GetHeight(), PixelFormat32bppARGB)));


			Gdiplus::Graphics g(g_pBitmap.get());
			g.DrawImage(&img, 0, 0);

			InvalidateRect(hwnd, NULL, TRUE);
		}
	}
}

void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if (id == IDM_NEW)
	{
		OnOpenFile(hwnd, codeNotify);
	}
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
		HANDLE_MSG(hwnd, WM_COMMAND, OnCommand);
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
