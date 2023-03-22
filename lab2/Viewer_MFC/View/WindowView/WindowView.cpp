#include "../../pch.h"
#include "../../Common/WndConfig.h"
#include "WindowView.h"

void InitFileNameStructure(HWND hwndOwner, OPENFILENAME* pOpenFileName, TCHAR* pFileName, DWORD maxFileName)
{
	ZeroMemory(pOpenFileName, sizeof(OPENFILENAME));

	pOpenFileName->lStructSize = sizeof(OPENFILENAME);
	pOpenFileName->hwndOwner = hwndOwner;
	//pOpenFileName->hInstance = m_hInstance;
	pOpenFileName->nMaxFile = maxFileName;
	pOpenFileName->lpstrFile = pFileName;
	pOpenFileName->lpstrFilter = _T("Images (BMP, PNG, JPG, TIFF)\0*.bmp;*.png;*.jpg;*.tif\0")
								 _T("All files\0*.*\0")
								 _T("\0");
}

void WindowView::OnDestroy(HWND)
{
	PostQuitMessage(0);
}

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
			SIZE imgSize = {
				static_cast<LONG>(img.GetWidth()),
				static_cast<LONG>(img.GetHeight())
			};
			auto bitmap = std::make_unique<Gdiplus::Bitmap>(imgSize.cx, imgSize.cy, PixelFormat32bppARGB);
			Gdiplus::Graphics g(bitmap.get());
			// https://stackoverflow.com/questions/18643504/gdi-image-scaling-issue решение проблемы, что пнг изображение загружалось не полностью
			Gdiplus::ImageAttributes attrs;
			attrs.SetWrapMode(Gdiplus::WrapModeTileFlipXY);
			Gdiplus::Rect dest(0, 0, imgSize.cx, imgSize.cy);
			g.DrawImage(&img, dest, 0, 0, static_cast<INT>(imgSize.cx), static_cast<INT>(imgSize.cy), Gdiplus::UnitPixel, &attrs);

			m_mediaFrames.push_back(std::move(std::make_unique<ImageFrame>(std::move(bitmap))));

			RECT clientRect;
			GetClientRect(hwnd, &clientRect);
			auto resizeCoef = m_mediaFrames.back()->WndFit(clientRect);
			m_mediaFrames.back()->Center(clientRect, resizeCoef);

			// триггерим событие перерисовки
			InvalidateRect(hwnd, NULL, TRUE);
		}
	}
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

	for (auto&& mediaFrame : m_mediaFrames)
	{
		auto resizeCoef = mediaFrame->WndFit(clientRect);
		mediaFrame->Display(g);
	}

	BitBlt(dc, 0, 0, clientSize.cx, clientSize.cy, hdcBuffer, 0, 0, SRCCOPY);

	EndPaint(hwnd, &ps);
}

void WindowView::OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if (id == MenuID.at(MenuIDKey::NEW))
	{
		OnOpenFile(hwnd, codeNotify);
	}
}

void WindowView::OnMouseMove(HWND hwnd, int x, int y, UINT keyFlags)
{
	if (!m_isDragging)
	{
		return;
	}

	POINT deltaPosition = {
		static_cast<LONG>(x - m_prevMousePosition.x),
		static_cast<LONG>(y - m_prevMousePosition.y)
	};

	m_mediaFrames.at(m_activeFrameIndex)->Move(deltaPosition);
	m_prevMousePosition = {
		static_cast<LONG>(x),
		static_cast<LONG>(y)
	};

	auto leftTop = m_mediaFrames.at(m_activeFrameIndex)->GetLeftTop();
	auto size = m_mediaFrames.at(m_activeFrameIndex)->GetSize();

	RECT invalidRect = {
		leftTop.x - deltaPosition.x,
		leftTop.y - deltaPosition.y,
		leftTop.x + size.cx + std::abs(deltaPosition.x),
		leftTop.y + size.cy + std::abs(deltaPosition.y)
	};

	InvalidateRect(hwnd, &invalidRect, FALSE);
}

void WindowView::OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)
{
	m_prevMousePosition = {
		static_cast<LONG>(x),
		static_cast<LONG>(y)
	};
	m_isDragging = SelectActiveImageFrame({ x, y });
}

void WindowView::OnLButtonUp(HWND hwnd, int x, int y, UINT keyFlags)
{
	m_isDragging = false;
}

BOOL WindowView::OnEraseBkgnd(HWND hwnd, HDC wParam)
{
	return TRUE;
}

LRESULT WindowView::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return LRESULT();
}

bool WindowView::RegisterWndClass(HINSTANCE hInstance)
{
	WNDCLASSEX wndClass = {
		sizeof(wndClass), // UINT cbSize;
		CS_HREDRAW | CS_VREDRAW, // UINT style;
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


