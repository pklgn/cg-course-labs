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

	// ������� ������ Graphics
	Gdiplus::Graphics g(dc);

	WndFit(hwnd);

	g.DrawImage(m_pBitmap.get(), static_cast<INT>(m_leftTop.x), static_cast<INT>(m_leftTop.y));

	EndPaint(hwnd, &ps);
}

void ImageFrame::Resize(POINT size)
{
}

void ImageFrame::Move(POINT dst)
{
}

void ImageFrame::SetBitmap(const WCHAR* filename)
{
	std::auto_ptr<Gdiplus::Image> pImage(new Gdiplus::Image(filename));

	// ������� ��������� ����������� ���������������� �������
	// � �������� �������� RGBA 32 bit
	std::unique_ptr<Gdiplus::Bitmap> bmp = std::make_unique<Gdiplus::Bitmap>(pImage->GetWidth(), pImage->GetHeight(), PixelFormat32bppARGB);

	// ������� ������ Graphics ��� ��������� � ������ bmp
	Gdiplus::Graphics g(bmp.get());

	// ������ �������� ����������� ������ ���������� ���� ������
	g.DrawImage(pImage.get(), 0, 0);

	// ������� ������ Image
	pImage.release();

	m_pBitmap = std::move(bmp);
}

void ImageFrame::SetBitmap(std::unique_ptr<Gdiplus::Bitmap> bitmap)
{
	m_pBitmap = std::move(bitmap);
}

void ImageFrame::WndFit(HWND hwnd)
{
	// ����� ����� ��������� ������� ����������� � � ������ �������� ����� ��������� ������ � ����������� ���������
	SIZE bitmapSize = { m_pBitmap->GetWidth(),
		m_pBitmap->GetHeight() };
	auto bitmapAspectRatio = bitmapSize.cx / static_cast<double>(bitmapSize.cy);

	RECT clientRect;
	GetClientRect(hwnd, &clientRect);
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

	auto thumbnailImage = m_pBitmap->GetThumbnailImage(bitmapSize.cx * resizeCoef, bitmapSize.cy * resizeCoef, NULL, NULL);

	m_pBitmap.reset(static_cast<Gdiplus::Bitmap*>(thumbnailImage));
}
