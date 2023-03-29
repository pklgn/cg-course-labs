#include "../../pch.h"
#include "CollageController.h"
#include "../../View/CollageView/CollageView.h"

const UINT MAX_REDRAW_BUFFER = 4;

CollageController::CollageController(Collage& collage, CollageView& collageView)
	: m_collage(collage)
	, m_collageView(collageView)
	, m_prevMousePosition({0, 0})
{
}

void CollageController::OnDestroy()
{
	// TODO: определиться с правильным порядком удаления и отписки, чтобы избежать access violation ошибок
	auto collageViewSize = static_cast<int>(m_collageView.GetSize());
	for (int i = collageViewSize - 1; 0 <= i; --i)
	{
		m_collageView.RemoveImageFrameViewAtIndex(i);
	}

	auto collageSize = static_cast<int>(m_collage.GetImageFrameCount());
	for (int i = collageSize - 1; 0 <= i; --i)
	{
		m_collage.RemoveImageFrameAtIndex(i);
	}
}

void CollageController::OnPaint(Gdiplus::Graphics& g, const RECT& clientRect)
{
	// FIXED: возможно, не следует при каждом событии рисования вызывать функцию, подсчитывающую размеры изображения на основании размера окна
	// FIXED: перенес цикл пересчета размеров миниатюры в обработчик события OnSize (WM_SIZE у winapi)
	m_collageView.Display(g);
}

/*
* Возвращает прямоугольник, который требует перерисовки
*/
RECT CollageController::OnMouseMove(POINT mousePosition)
{
	if (m_pActiveImageFrame)
	{
		POINT deltaPosition = {
			static_cast<LONG>(mousePosition.x - m_prevMousePosition.x),
			static_cast<LONG>(mousePosition.y - m_prevMousePosition.y)
		};

		m_pActiveImageFrame->Move(deltaPosition);
		m_prevMousePosition = {
			static_cast<LONG>(mousePosition.x),
			static_cast<LONG>(mousePosition.y)
		};

		auto leftTop = m_pActiveImageFrame->GetLeftTop();
		auto size = m_pActiveImageFrame->GetSize();

		RECT invalidRect = {
			leftTop.x - deltaPosition.x,
			leftTop.y - deltaPosition.y,
			leftTop.x + size.cx + std::abs(deltaPosition.x),
			leftTop.y + size.cy + std::abs(deltaPosition.y)
		};

		return invalidRect;
	}
	if (m_isDrawing && m_collage.GetImageFrameCount() != 0)
	{
		auto imageFrame = m_collage.GetImageFrameAtIndex(m_collage.GetImageFrameCount() - 1);
		imageFrame->DrawLine(m_prevMousePosition, mousePosition);
		++m_redrawBuffer;
		if (m_redrawBuffer == MAX_REDRAW_BUFFER)
		{
			m_redrawBuffer = 0;
			imageFrame->NotifyObservers();
		}
		

		LONG left = (m_prevMousePosition.x < mousePosition.x)
			? m_prevMousePosition.x
			: mousePosition.x;
		LONG top = (m_prevMousePosition.y < mousePosition.y)
			? m_prevMousePosition.y
			: mousePosition.y;
		LONG right = (m_prevMousePosition.x < mousePosition.x)
			? mousePosition.x
			: m_prevMousePosition.x;
		LONG bottom = (m_prevMousePosition.y < mousePosition.y)
			? mousePosition.y
			: m_prevMousePosition.y;
		m_prevMousePosition = mousePosition;

		RECT invalidRect = {
			left,
			top,
			right,
			bottom
		};

		return invalidRect;
	}

	return RECT();
}

void CollageController::OnLButtonDown(POINT mousePosition, BOOL fDoubleClick)
{
	// TODO: реализовать логику рисования
	if (m_collage.GetImageFrameCount() == 0)
	{
		auto size = m_collage.GetSize();
		RECT canvasRect = {
			0,
			0,
			size.cx,
			size.cy
		};
		AppendCanvas(canvasRect);
	}
	m_prevMousePosition = mousePosition;
	m_isDrawing = true;
}

void CollageController::OnLButtonDblClk(POINT mousePosition, BOOL fDoubleClick)
{
	if (!m_pActiveImageFrame)
	{
		m_pActiveImageFrame = FindActiveImageFrame(mousePosition);
	}
}

void CollageController::OnLButtonUp()
{
	if (m_isDrawing)
	{
		auto imageFrame = m_collage.GetImageFrameAtIndex(m_collage.GetImageFrameCount() - 1);
	/*	imageFrame->WndFit()*/
	}
	m_pActiveImageFrame = nullptr;
	m_isDrawing = false;
}

void CollageController::OnSize(int cx, int cy)
{
	auto collageSize = static_cast<int>(m_collage.GetImageFrameCount());
	for (auto i = collageSize - 1; 0 <= i; --i)
	{
		m_collage.GetImageFrameAtIndex(i)->WndFit({0, 0, static_cast<LONG>(cx), static_cast<LONG>(cy)});
	}
}

void CollageController::AppendImage(Gdiplus::Image& img, const RECT& clientRect)
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

	m_collage.AddImageFrameAtIndex(std::make_unique<ImageFrame>(std::move(bitmap)));
	m_collage.GetImageFrameAtIndex(m_collage.GetImageFrameCount() - 1)->WndFit(clientRect);
}

// TODO: переделать получение параметра с const RECT& на SIZE, чтобы туда-сюда не перегонять
void CollageController::AppendCanvas(const RECT& clientRect)
{
	SIZE canvasSize = {
		clientRect.right - clientRect.left,
		clientRect.bottom - clientRect.top,
	};
	Gdiplus::Bitmap bitmap(static_cast<INT>(canvasSize.cx), static_cast<INT>(canvasSize.cy), PixelFormat32bppARGB);
	Gdiplus::Graphics graphics(&bitmap);
	graphics.Clear(Gdiplus::Color(0, 0, 0, 0));
	std::unique_ptr<Gdiplus::Bitmap> pBitmap;
	pBitmap.reset(&bitmap);
	m_collage.AddImageFrameAtIndex(std::make_unique<ImageFrame>(std::move(pBitmap)));
}

ImageFrame* CollageController::FindActiveImageFrame(POINT mousePosition)
{
	auto collageSize = static_cast<int>(m_collage.GetImageFrameCount());
	for (int i = collageSize - 1; 0 <= i; --i)
	{
		auto imageFrame = m_collage.GetImageFrameAtIndex(i);
		auto leftTop = imageFrame->GetLeftTop();
		auto size = imageFrame->GetSize();
		RECT frame = {
			leftTop.x,
			leftTop.y,
			leftTop.x + size.cx,
			leftTop.y + size.cy,
		};
		bool containMousePosition = PtInRect(&frame, mousePosition);
		if (containMousePosition)
		{
			m_prevMousePosition = mousePosition;

			return imageFrame;
		}
	}

	return nullptr;
}
