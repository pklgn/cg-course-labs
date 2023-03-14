#include "../../pch.h"
#include "ImageFrame.h"

ImageFrame::ImageFrame(const WCHAR* filename)
{
	SetBitmap(filename);
}

ImageFrame::ImageFrame(std::unique_ptr<Gdiplus::Bitmap> bitmap)
{
	SetBitmap(std::move(bitmap));
}

void ImageFrame::Display(HWND hwnd)
{
	PAINTSTRUCT ps;
	HDC dc = BeginPaint(hwnd, &ps);

	// Создаем объект Graphics
	Gdiplus::Graphics g(dc);

	auto resizeCoef = WndFit(hwnd);
	Center(hwnd, resizeCoef);
	auto thumbnailImage = m_pBitmap->GetThumbnailImage(m_size.cx, m_size.cy, NULL, NULL);
	g.DrawImage(thumbnailImage, static_cast<INT>(m_leftTop.x), static_cast<INT>(m_leftTop.y));

	EndPaint(hwnd, &ps);
}

void ImageFrame::Resize(SIZE size)
{
}

void ImageFrame::Move(POINT dst)
{
}

void ImageFrame::Center(HWND hwnd, double resizeCoef)
{
	RECT clientRect;
	GetClientRect(hwnd, &clientRect);

	m_leftTop = { static_cast<LONG>((clientRect.right - clientRect.left) / 2 - m_pBitmap->GetWidth() * resizeCoef / 2),
		static_cast<LONG>((clientRect.bottom - clientRect.top) / 2 - m_pBitmap->GetHeight() * resizeCoef / 2) };
}

void ImageFrame::SetBitmap(const WCHAR* filename)
{
	std::auto_ptr<Gdiplus::Image> pImage(new Gdiplus::Image(filename));

	// Создаем растровое изображение соответствующего размера
	// с форматом пикселей RGBA 32 bit
	std::unique_ptr<Gdiplus::Bitmap> bmp = std::make_unique<Gdiplus::Bitmap>(pImage->GetWidth(), pImage->GetHeight(), PixelFormat32bppARGB);

	// Создаем объект Graphics дли рисования в растре bmp
	Gdiplus::Graphics g(bmp.get());

	// Рисуем исходное изображение внутрь созданного нами растра
	g.DrawImage(pImage.get(), 0, 0);

	// удаляем объект Image
	pImage.release();

	m_pBitmap = std::move(bmp);
}

void ImageFrame::SetBitmap(std::unique_ptr<Gdiplus::Bitmap> bitmap)
{
	m_pBitmap = std::move(bitmap);
}

double ImageFrame::WndFit(HWND hwnd)
{
	// здесь нужно посчитать размеры изображения и в случае нехватки места уменишить размер с сохранением пропорций
	SIZE bitmapSize = { m_pBitmap->GetWidth(),
		m_pBitmap->GetHeight() };
	auto bitmapAspectRatio = bitmapSize.cx / static_cast<double>(bitmapSize.cy);

	RECT clientRect;
	GetClientRect(hwnd, &clientRect);
	SIZE clientSize = { clientRect.right - clientRect.left,
		clientRect.bottom - clientRect.top };

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
	if (clientSize.cx < bitmapSize.cx)
	{
		resizeCoef *= (bitmapAspectRatio < 1)
			? clientSize.cy / static_cast<double>(bitmapSize.cy)
			: clientSize.cx / static_cast<double>(bitmapSize.cx);
	}
	if (clientSize.cy < bitmapSize.cy * resizeCoef)
	{
		resizeCoef *= clientSize.cy / (static_cast<double>(bitmapSize.cy * resizeCoef));
	}

	//auto thumbnailImage = m_pBitmap->GetThumbnailImage(bitmapSize.cx * resizeCoef, bitmapSize.cy * resizeCoef, NULL, NULL);
	m_size = { static_cast<LONG>(bitmapSize.cx * resizeCoef),
		static_cast<LONG>(bitmapSize.cy * resizeCoef) };

	//m_pBitmap.reset(static_cast<Gdiplus::Bitmap*>(thumbnailImage));
	return resizeCoef;
}
