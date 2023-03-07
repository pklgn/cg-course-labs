#include "../../pch.h"
#include "ImageFrame.h"

ImageFrame::ImageFrame(HWND hwnd, const WCHAR* filename, RECT frame)
	: m_frame(frame)
	, m_gdiplusInitializer()
{
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
}

void ImageFrame::Display(HWND hwnd)
{
}
