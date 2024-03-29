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

double ImageFrame::WndFit(const RECT& clientRect)
{
	// ����� ����� ��������� ������� ����������� � � ������ �������� ����� ��������� ������ � ����������� ���������
	SIZE bitmapSize = { static_cast<LONG>(m_pBitmap->GetWidth()),
		static_cast<LONG>(m_pBitmap->GetHeight()) };
	auto bitmapAspectRatio = bitmapSize.cx / static_cast<double>(bitmapSize.cy);

	SIZE clientSize = { clientRect.right - clientRect.left,
		clientRect.bottom - clientRect.top };

	double resizeCoef = 1;

	/* ���� ������ ������� �� ����� �����������, �� �� �������� ��������
	 * �� ����������� ������:
	 *	���� ��� ����������, �� ��������� ����������� �����
	 *	����� � �������� ������������ ����� ����������� �����
	 * ����� ����� ���� ��������������� �������� ����������� �� �������� �� ����
	 * ����������
	 *
	 * ������ ����� ���� �������� ����� ��������� ���, ��� ������� �� ����������
	 * ��� ����� ����� �������� �� ������� ���� �� ����� ���
	 * ������� ��� � ���, ��� � ����� ������ ����������� ������ ����
	 * �� ��������� � ������������ ������ �����������
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
	SIZE prevSize = m_size;
	m_size = { static_cast<LONG>(bitmapSize.cx * resizeCoef),
		static_cast<LONG>(bitmapSize.cy * resizeCoef) };


	if (prevSize.cx != m_size.cx ||
		prevSize.cy != m_size.cy)
	{
		m_changedData = {
			std::nullopt,
			std::nullopt,
			m_size
		};

		NotifyObservers();
	}
	m_resizeBitmapCoef = resizeCoef;

	return resizeCoef;
}

void ImageFrame::Center(const RECT& clientRect, double resizeCoef)
{
	m_leftTop = { static_cast<LONG>((clientRect.right - clientRect.left) / 2 - m_pBitmap->GetWidth() * resizeCoef / 2),
		static_cast<LONG>((clientRect.bottom - clientRect.top) / 2 - m_pBitmap->GetHeight() * resizeCoef / 2) };

	m_changedData = {
		std::nullopt,
		m_leftTop,
		std::nullopt
	};
	NotifyObservers();
}

void ImageFrame::Move(POINT deltaPosition)
{
	m_leftTop.x += deltaPosition.x;
	m_leftTop.y += deltaPosition.y;
}

void ImageFrame::SetBitmap(const WCHAR* filename)
{
	std::auto_ptr<Gdiplus::Image> pImage(new Gdiplus::Image(filename));

	// ������� ��������� ����������� ���������������� �������
	// � �������� �������� RGBA 32 bit

	SIZE imageSize = {
		static_cast<LONG>(pImage->GetWidth()),
		static_cast<LONG>(pImage->GetHeight())
	};
	std::unique_ptr<Gdiplus::Bitmap> bmp = std::make_unique<Gdiplus::Bitmap>(imageSize.cx, imageSize.cy, PixelFormat32bppARGB);

	// ������� ������ Graphics ��� ��������� � ������ bmp
	Gdiplus::Graphics g(bmp.get());

	// ������ �������� ����������� ������ ���������� ���� ������
	g.DrawImage(pImage.get(), 0, 0);

	// ������� ������ Image
	pImage.release();

	m_size = imageSize;
	m_pBitmap = std::move(bmp);

	m_changedData = {
		m_pBitmap.get(),
		std::nullopt,
		m_size
	};
	NotifyObservers();
}

void ImageFrame::SetBitmap(std::unique_ptr<Gdiplus::Bitmap> bitmap)
{
	m_size = {
		static_cast<LONG>(bitmap->GetWidth()),
		static_cast<LONG>(bitmap->GetHeight()),
	};
	m_pBitmap = std::move(bitmap);

	m_changedData = {
		m_pBitmap.get(),
		std::nullopt,
		m_size
	};
	NotifyObservers();
}

POINT ImageFrame::GetLeftTop() const
{
	return m_leftTop;
}

SIZE ImageFrame::GetSize() const
{
	return m_size;
}
	
Gdiplus::Image* ImageFrame::GetThumbnailImage(SIZE thumbnailSize) const
{
	return m_pBitmap->GetThumbnailImage(thumbnailSize.cx, thumbnailSize.cy, NULL, NULL);
}

void ImageFrame::DrawLine(POINT from, POINT to)
{
	Gdiplus::Graphics graphics(m_pBitmap.get());
	Gdiplus::Pen pen(Gdiplus::Color(255, 255, 0, 0), static_cast<Gdiplus::REAL>(3 / m_resizeBitmapCoef));
	graphics.DrawLine(&pen, static_cast<INT>(from.x / m_resizeBitmapCoef), static_cast<INT>(from.y / m_resizeBitmapCoef), static_cast<INT>(to.x / m_resizeBitmapCoef), static_cast<INT>(to.y / m_resizeBitmapCoef));
	
	m_changedData = {
		m_pBitmap.get(),
		std::nullopt,
		m_size
	};
}

ImageFrameData ImageFrame::GetChangedData() const
{
	return m_changedData;
}
