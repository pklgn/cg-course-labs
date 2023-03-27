#include "../../pch.h"
#include "CollageController.h"
#include "../../View/CollageView/CollageView.h"

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

	auto collageSize = static_cast<int>(m_collage.GetSize());
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

RECT CollageController::OnMouseMove(POINT mousePosition)
{
	if (m_activeImageFrame)
	{
		POINT deltaPosition = {
			static_cast<LONG>(mousePosition.x - m_prevMousePosition.x),
			static_cast<LONG>(mousePosition.y - m_prevMousePosition.y)
		};

		m_activeImageFrame->Move(deltaPosition);
		m_prevMousePosition = {
			static_cast<LONG>(mousePosition.x),
			static_cast<LONG>(mousePosition.y)
		};

		auto leftTop = m_activeImageFrame->GetLeftTop();
		auto size = m_activeImageFrame->GetSize();

		RECT invalidRect = {
			leftTop.x - deltaPosition.x,
			leftTop.y - deltaPosition.y,
			leftTop.x + size.cx + std::abs(deltaPosition.x),
			leftTop.y + size.cy + std::abs(deltaPosition.y)
		};

		return invalidRect;
	}

	return RECT();
}

void CollageController::OnLButtonDown(POINT mousePosition)
{
	m_activeImageFrame = FindActiveImageFrame(mousePosition);
}

void CollageController::OnLButtonUp()
{
	m_activeImageFrame = nullptr;
}

void CollageController::OnSize(int cx, int cy)
{
	auto collageSize = static_cast<int>(m_collage.GetSize());
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
	m_collage.GetImageFrameAtIndex(m_collage.GetSize() - 1)->WndFit(clientRect);
}

ImageFrame* CollageController::FindActiveImageFrame(POINT mousePosition)
{
	auto collageSize = static_cast<int>(m_collage.GetSize());
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
