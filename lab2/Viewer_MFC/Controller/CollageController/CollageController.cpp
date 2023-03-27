#include "../../pch.h"
#include "CollageController.h"
#include "../../View/CollageView/CollageView.h"

CollageController::CollageController(Collage& collage, CollageView& collageView)
	: m_collage(collage)
	, m_collageView(collageView)
{
}

void CollageController::OnDestroy()
{
	// TODO: определиться с правильным порядком удаления и отписки, чтобы избежать access violation ошибок
	auto count = m_collageView.GetCount();
	for (int i = count - 1; 0 <= i; --i)
	{
		m_collageView.RemoveImageFrameViewAtIndex(i);
	}

	auto size = m_collage.GetSize();
	for (int i = size - 1; 0 <= i; --i)
	{
		m_collage.RemoveImageFrameAtIndex(i);
	}
}

void CollageController::OnPaint(Gdiplus::Graphics& g, const RECT& clientRect)
{
	// TODO: возможно, не следует при каждом событии рисования вызывать функцию, подсчитывающую размеры изображения на основании размера окна
	for (int i = m_collage.GetSize() - 1; 0 <= i; --i)
	{
		m_collage.GetImageFrameAtIndex(i)->WndFit(clientRect);
	}

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

void CollageController::AppendImage(Gdiplus::Image& img)
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
}

ImageFrame* CollageController::FindActiveImageFrame(POINT mousePosition)
{
	for (int i = m_collage.GetSize() - 1; 0 <= i; --i)
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
			return imageFrame;
		}
	}

	return nullptr;
}
