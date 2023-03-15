#include "../pch.h"
#include "../common/GdiplusInitializer.h"
#include "../common/WndConfig.h"
#include "../common/MnConfig.h"
#include "App.h"
#include "../MediaFrame/ImageFrame/ImageFrame.h"

int MainLoop();
bool RegisterWndClass(HINSTANCE hInstance);
HWND CreateMainWindow(HINSTANCE hInstance);

App::App(HINSTANCE hInstance, int nCmdShow)
	: m_hInstance(hInstance)
	, m_nCmdShow(nCmdShow)
{
}

int App::Run()
{
	if (m_isRunning)
	{
		return 1;
	}
	m_isRunning = true;

	try
	{
		GdiplusInitializer gdiplusInitializer;

		// Регистрируем класс главного окна
		if (!RegisterWndClass(m_hInstance))
		{
			return 1;
		}

		// Создаю меню для окна приложения
		HMENU hMenu = CreateMenu();
		HMENU hSubMenu = CreatePopupMenu();
		AppendMenu(hSubMenu, MF_STRING, MenuID.at(MenuIDKey::NEW), L"New");
		AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hSubMenu, L"File");

		// Создаем главное окно приложения
		HWND hMainWindow = CreateMainWindow(m_hInstance);
		if (hMainWindow == NULL)
		{
			return 1;
		}

		SetWindowLongPtr(hMainWindow, GWLP_USERDATA, (LONG_PTR)(this));

		//Добавляем меню к главному окну приложения
		SetMenu(hMainWindow, hMenu);

		// Показываем главное окно приложения
		ShowWindow(hMainWindow, m_nCmdShow);
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

void App::InitFileNameStructure(HWND hwndOwner, OPENFILENAME* pOpenFileName, TCHAR* pFileName, DWORD maxFileName)
{
	ZeroMemory(pOpenFileName, sizeof(OPENFILENAME));

	pOpenFileName->lStructSize = sizeof(OPENFILENAME);
	pOpenFileName->hwndOwner = hwndOwner;
	pOpenFileName->hInstance = m_hInstance;
	pOpenFileName->nMaxFile = maxFileName;
	pOpenFileName->lpstrFile = pFileName;
	pOpenFileName->lpstrFilter = _T("Images (BMP, PNG, JPG, TIFF)\0*.bmp;*.png;*.jpg;*.tif\0")
								 _T("All files\0*.*\0")
								 _T("\0");
}

void App::OnDestroy(HWND)
{
	for (auto&& mediaFrame : m_mediaFrames)
	{
		mediaFrame.reset();
	}
	PostQuitMessage(0);
}

void App::OnOpenFile(HWND hwnd, UINT)
{
	OPENFILENAME ofn;
	TCHAR fileName[MAX_PATH + 1] = _T("");
	InitFileNameStructure(hwnd, &ofn, fileName, MAX_PATH);

	if (GetOpenFileName(&ofn))
	{
		Gdiplus::Image img(ofn.lpstrFile);

		if (img.GetLastStatus() == Gdiplus::Ok)
		{
			auto bitmap = std::make_unique<Gdiplus::Bitmap>(img.GetWidth(), img.GetHeight(), PixelFormat32bppARGB);
			Gdiplus::Graphics g(bitmap.get());
			g.DrawImage(&img, 0, 0);
			//TODO: исправить мув на муве
			m_mediaFrames.push_front(std::move(std::make_unique<ImageFrame>(std::move(bitmap))));

			// триггерим событие перерисовки
			InvalidateRect(hwnd, NULL, TRUE);
		}
	}
}

void App::OnPaint(HWND hwnd)
{
	PAINTSTRUCT ps;
	HDC dc = BeginPaint(hwnd, &ps);

	Gdiplus::Graphics g(dc);



	for (auto&& mediaFrame : m_mediaFrames)
	{
		auto resizeCoef = mediaFrame->WndFit(hwnd);
		mediaFrame->Center(hwnd, resizeCoef);
		mediaFrame->Display(g);
	}
}

void App::OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if (id == MenuID.at(MenuIDKey::NEW))
	{
		OnOpenFile(hwnd, codeNotify);
	}
}

LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	auto instance = reinterpret_cast<App*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

	switch (uMsg)
	{
		HANDLE_MSG(hwnd, WM_DESTROY, instance->OnDestroy);
		HANDLE_MSG(hwnd, WM_PAINT, instance->OnPaint);
		HANDLE_MSG(hwnd, WM_COMMAND, instance->OnCommand);
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

HWND CreateMainWindow(HINSTANCE hInstance)
{
	HWND hMainWindow = CreateWindowEx(
		0,
		WNDENTITIES.at(WndKeyEntities::CLASS_NAME),
		WNDENTITIES.at(WndKeyEntities::WINDOW_TITLE),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	return hMainWindow;
}

bool RegisterWndClass(HINSTANCE hInstance)
{
	WNDCLASSEX wndClass = {
		sizeof(wndClass), // UINT cbSize;
		CS_HREDRAW | CS_VREDRAW, // UINT style;
		&WindowProc, // WNDPROC lpfnWndProc;
		0, // int cbClsExtra;
		static_cast<LONG_PTR>(sizeof(App*)), // int cbWndExtra;
		hInstance, // HINSTANCE hInstance;
		NULL, // HICON hIcon;
		LoadCursor(NULL, IDC_ARROW), // HCURSOR hCursor;
		(HBRUSH)(COLOR_BTNFACE + 1), // HBRUSH hbrBackground;
		NULL, // LPCTSTR lpszMenuName;
		WNDENTITIES.at(WndKeyEntities::CLASS_NAME), // LPCTSTR lpszClassName;
		NULL, // HICON hIconSm;
	};

	return RegisterClassEx(&wndClass) != FALSE;
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
	return static_cast<int>(msg.wParam);
}