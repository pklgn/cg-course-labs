#include "../../pch.h"
#include "../../Common/WndConfig.h"
#include "../../Common/MnConfig.h"
#include "WindowView.h"
#include "../../Common/GdiplusInitializer.h"

const LONG MAX_WINDOW_WIDTH = 800;
const LONG MAX_WINDOW_HEIGHT = 600;

void WindowView::InitFileNameStructure(HWND hwndOwner, OPENFILENAME* pOpenFileName, TCHAR* pFileName, DWORD maxFileName) const
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

HWND CreateMainWindow(HINSTANCE hInstance)
{
	HWND hMainWindow = CreateWindowEx(
		0,
		WNDENTITIES.at(WndKeyEntities::CLASS_NAME),
		WNDENTITIES.at(WndKeyEntities::WINDOW_TITLE),
		WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,
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
	return static_cast<int>(msg.wParam);
}

WindowView::WindowView(CollageController& collageController, HINSTANCE hInstance, int nCmdShow)
	: m_hInstance(hInstance)
	, m_nCmdShow(nCmdShow)
	, m_collageController(collageController)
{
}

bool RegisterWndClass(HINSTANCE hInstance);
int WindowView::Show()
{
	try
	{
		GdiplusInitializer gdiplusInitializer;

		// ������������ ����� �������� ����
		if (!RegisterWndClass(m_hInstance))
		{
			return 1;
		}

		// ������ ���� ��� ���� ����������
		HMENU hMenu = CreateMenu();
		HMENU hSubMenu = CreatePopupMenu();
		AppendMenu(hSubMenu, MF_STRING, MenuID.at(MenuIDKey::NEW), L"New");
		AppendMenu(hSubMenu, MF_STRING, MenuID.at(MenuIDKey::SAVE), L"Save");
		AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hSubMenu, L"File");

		// ������� ������� ���� ����������
		HWND hMainWindow = CreateMainWindow(m_hInstance);
		if (hMainWindow == NULL)
		{
			return 1;
		}

		SetWindowLongPtr(hMainWindow, GWLP_USERDATA, (LONG_PTR)(this));

		//��������� ���� � �������� ���� ����������
		SetMenu(hMainWindow, hMenu);

		// ���������� ������� ���� ����������
		ShowWindow(hMainWindow, m_nCmdShow);
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

void WindowView::OnDestroy(HWND)
{
	m_collageController.OnDestroy();
	PostQuitMessage(0);
}

std::once_flag flag;
void AdjustWindow(HWND hwnd, LONG imageWidth, LONG imageHeight);
void WindowView::OnOpenFile(HWND hwnd, UINT)
{
	OPENFILENAME ofn;
	TCHAR fileName[MAX_PATH + 1] = _T("");
	InitFileNameStructure(hwnd, &ofn, fileName, MAX_PATH);

	if (GetOpenFileName(&ofn))
	{
		Gdiplus::Image img(ofn.lpstrFile);

		if (img.GetLastStatus() == Gdiplus::Ok)
		{
			RECT clientRect;
			GetClientRect(hwnd, &clientRect);
			m_collageController.AppendImage(img, clientRect);
			std::call_once(flag, AdjustWindow, hwnd, img.GetWidth(), img.GetHeight());

			// ��������� ������� �����������
			InvalidateRect(hwnd, NULL, TRUE);
		}
	}
}

std::wstring GetFileExtension(std::wstring const& fileName)
{
	size_t dotPos = fileName.find_last_of(L'.');
	if (dotPos != std::wstring::npos)
	{
		return fileName.substr(dotPos + 1);
	}
	else
	{
		return std::wstring();
	}
}

std::wstring WStringToLower(std::wstring const& str)
{
	std::wstring result(str);

	std::transform(result.begin(), result.end(), result.begin(), std::tolower);

	return result;
}


CLSID GetEncoderCLSID(std::wstring const& fileExtension)
{
	// �������� ���������� � ���� "*.����������"
	std::wstring extensionMask = L"*." + WStringToLower(fileExtension) + L";";

	// ����������� � GDI+ ���������� ������������ �����������
	// � ������ ����� ������ ��� �������� �� ��������
	UINT numEncoders;
	UINT encodersSize;
	Gdiplus::GetImageEncodersSize(&numEncoders, &encodersSize);

	// �������� ����� ��� �������� ���������� � ������������
	std::vector<BYTE> encodersBuffer(encodersSize);

	// ����������� � GDI+ ���������� ��� ���� ������������
	Gdiplus::ImageCodecInfo* pInstalledCodecs = reinterpret_cast<Gdiplus::ImageCodecInfo*>(&encodersBuffer[0]);
	Gdiplus::GetImageEncoders(numEncoders, encodersSize, pInstalledCodecs);

	Gdiplus::ImageCodecInfo* pMatchedCodec = NULL;

	// ���� ���������� ���������� �����������
	for (unsigned i = 0; i < numEncoders; ++i)
	{
		Gdiplus::ImageCodecInfo& codec = pInstalledCodecs[i];

		// �������� ���������� ������, �������������� ������ ������������
		// � �������: *.jpg;*.jpe;*.jpeg;
		std::wstring extensions = WStringToLower(codec.FilenameExtension) + L";";

		// ���� � ������ ���������� ���������� ����� ���������� �����
		// �� ����� ��������� ���������
		if (extensions.find(extensionMask) != std::wstring::npos)
		{
			return codec.Clsid;
		}
	}

	// �� ����� ���������� ����������, ���������� ������� �������������
	return CLSID_NULL;
}

bool SaveBMPFile(const std::wstring& filename, HBITMAP hBitmap, HDC hDC, int width, int height)
{
	Gdiplus::Graphics* graphics = Gdiplus::Graphics::FromHDC(hDC);
	Gdiplus::Bitmap* bitmap = Gdiplus::Bitmap::FromHBITMAP(hBitmap, NULL);
	graphics->DrawImage(bitmap, 0, 0, width, height);

	// �������� ���������� ��������� �����
	std::wstring fileExtension = GetFileExtension(filename);

	// �������� ������������� �� ���������� �����
	CLSID codecId = GetEncoderCLSID(fileExtension);

	// ���� ������� CLSID_NULL (����� �� ������), �� �������
	if (IsEqualCLSID(codecId, CLSID_NULL))
	{
		return false;
	}

	// ��������� ��������� �����������
	Gdiplus::EncoderParameters params;
	params.Count = 1; // � ��� ������ ���� �������� (������� ��������� 0-100)

	// ��������� �������������� ��������� �������� ������
	Gdiplus::EncoderParameter& param0 = params.Parameter[0];

	LONG qualityParam = 75;

	param0.Guid = Gdiplus::EncoderCompression; // ������������� ��������� "����������"
	param0.NumberOfValues = 1; // � ������� ���������� ���������� ���� ��������
	param0.Type = Gdiplus::EncoderParameterValueTypeLong; // ��� �������� LONG
	param0.Value = &qualityParam; // ����� ������� ����������

	// ��������� ����������� � �������������� ������������ �����������
	// � ��������� Quality (�� �������� ������������ ������ � JPEG-�)
	auto status = bitmap->Save(filename.c_str(), &codecId, &params);
	status;

	delete bitmap;
	delete graphics;

	return true;
}

void WindowView::OnSaveFile(HWND hwnd, UINT)
{
	HDC hDC = GetDC(hwnd);
	HDC hTargetDC = CreateCompatibleDC(hDC);
	RECT rect = { 0 };

	GetClientRect(hwnd, &rect);

	HBITMAP hBitmap = CreateCompatibleBitmap(hDC, rect.right - rect.left,
		rect.bottom - rect.top);
	SelectObject(hTargetDC, hBitmap);
	PrintWindow(hwnd, hTargetDC, PW_CLIENTONLY);

	OPENFILENAME ofn;
	TCHAR fileName[MAX_PATH + 1] = _T("");
	InitFileNameStructure(hwnd, &ofn, fileName, MAX_PATH);

	if (GetSaveFileName(&ofn))
	{
		SaveBMPFile(fileName, hBitmap, hTargetDC, rect.right - rect.left,
			rect.bottom - rect.top);
	}
		

	DeleteObject(hBitmap);
	ReleaseDC(hwnd, hDC);
	DeleteDC(hTargetDC);
}

void WindowView::OnPaint(HWND hwnd)
{
	PAINTSTRUCT ps;
	HDC dc = BeginPaint(hwnd, &ps);
	HDC hdcBuffer = CreateCompatibleDC(dc);

	RECT clientRect;
	GetClientRect(hwnd, &clientRect);
	SIZE clientSize = { clientRect.right - clientRect.left,
		clientRect.bottom - clientRect.top };
	HBITMAP hBitmap = CreateCompatibleBitmap(dc, clientSize.cx, clientSize.cy);
	SelectObject(hdcBuffer, hBitmap);

	Gdiplus::SolidBrush brush(Gdiplus::Color(255, 255, 255));

	Gdiplus::Graphics g(hdcBuffer);
	g.FillRectangle(&brush, static_cast<INT>(clientRect.left), static_cast<INT>(clientRect.top), static_cast<INT>(clientSize.cx), static_cast<INT>(clientSize.cy));

	m_collageController.OnPaint(g, clientRect);

	BitBlt(dc, 0, 0, clientSize.cx, clientSize.cy, hdcBuffer, 0, 0, SRCCOPY);

	EndPaint(hwnd, &ps);
}

void WindowView::OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if (id == MenuID.at(MenuIDKey::NEW))
	{
		OnOpenFile(hwnd, codeNotify);
	}
	if (id == MenuID.at(MenuIDKey::SAVE))
	{
		OnSaveFile(hwnd, codeNotify);
	}
}

void WindowView::OnMouseMove(HWND hwnd, int x, int y, UINT keyFlags)
{
	auto invalidRect = m_collageController.OnMouseMove({ x, y });

	InvalidateRect(hwnd, NULL, FALSE);
}

void WindowView::OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)
{
	//m_collageController.OnLButtonDown({ x, y }, fDoubleClick);
	RECT clientRect;
	GetClientRect(hwnd, &clientRect);

	//m_collageController.AppendCanvas(clientRect);
	m_collageController.OnLButtonDown({ x, y }, fDoubleClick);
}

void WindowView::OnLButtonDblClk(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)
{
	m_collageController.OnLButtonDblClk({ x, y }, fDoubleClick);
}

void WindowView::OnLButtonUp(HWND hwnd, int x, int y, UINT keyFlags)
{
	m_collageController.OnLButtonUp();
}

BOOL WindowView::OnEraseBkgnd(HWND hwnd, HDC wParam)
{
	return TRUE;
}

// TODO: ���������� �� ����������� ������� OnSize, ��� ��� � ���� ������ ���������� ��� ����������� ��������� ����
void WindowView::OnSize(HWND hwnd, UINT state, int cx, int cy)
{
	m_collageController.OnSize(cx, cy);
}

LRESULT WindowView::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	auto instance = reinterpret_cast<WindowView*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	// TODO: �������-����������� � ATL: ���� ���� ����, ������� ����� ��� this
	switch (uMsg)
	{
		HANDLE_MSG(hwnd, WM_DESTROY, instance->OnDestroy);
		HANDLE_MSG(hwnd, WM_PAINT, instance->OnPaint);
		HANDLE_MSG(hwnd, WM_COMMAND, instance->OnCommand);
		HANDLE_MSG(hwnd, WM_ERASEBKGND, instance->OnEraseBkgnd);
		HANDLE_MSG(hwnd, WM_LBUTTONDOWN, instance->OnLButtonDown);
		HANDLE_MSG(hwnd, WM_MOUSEMOVE, instance->OnMouseMove);
		HANDLE_MSG(hwnd, WM_LBUTTONUP, instance->OnLButtonUp);
		HANDLE_MSG(hwnd, WM_SIZE, instance->OnSize);
		HANDLE_MSG(hwnd, WM_LBUTTONDBLCLK, instance->OnLButtonDblClk);
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

bool RegisterWndClass(HINSTANCE hInstance)
{
	WNDCLASSEX wndClass = {
		sizeof(wndClass), // UINT cbSize;
		CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS, // UINT style;
		&WindowView::WindowProc, // WNDPROC lpfnWndProc;
		0, // int cbClsExtra;
		static_cast<LONG_PTR>(sizeof(WindowView*)), // int cbWndExtra;
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

void AdjustWindow(HWND hwnd, LONG imageWidth, LONG imageHeight)
{
	auto bitmapAspectRatio = imageWidth / static_cast<double>(imageHeight);

	SIZE clientSize = { MAX_WINDOW_WIDTH,
		MAX_WINDOW_HEIGHT };

	double resizeCoef = 1;

	if (clientSize.cx < imageWidth)
	{
		resizeCoef *= (bitmapAspectRatio < 1)
			? clientSize.cy / static_cast<double>(imageHeight)
			: clientSize.cx / static_cast<double>(imageWidth);
	}
	if (clientSize.cy < imageHeight * resizeCoef)
	{
		resizeCoef *= clientSize.cy / (static_cast<double>(imageHeight * resizeCoef));
	}
	SIZE imageSize = { static_cast<LONG>(imageWidth * resizeCoef),
		static_cast<LONG>(imageHeight * resizeCoef) };

	RECT windowRect;
	GetWindowRect(hwnd, &windowRect);
	POINT screenLeftTop{ windowRect.left, windowRect.top };
	ScreenToClient(hwnd, &screenLeftTop);
	// TODO: ������ �������� � ��������� ���������� �������� ���� (������ ������� ������� �� 2 �� OX ����� �������������� ������)
	SetWindowPos(hwnd, NULL, windowRect.left, windowRect.top, imageSize.cx - screenLeftTop.x / 2, imageSize.cy - screenLeftTop.y, NULL);
	UpdateWindow(hwnd);
}
// TODO: ������ �������� ��� ������� � "no PDB file for ntdll.dll"
