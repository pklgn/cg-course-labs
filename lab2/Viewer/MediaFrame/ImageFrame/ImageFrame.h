#pragma once
#include <memory>
#include <gdiplus.h>
#include "../IMediaFrame.h"
#include "../../common/GdiplusInitializer.h"

class ImageFrame : public IMediaFrame
{
public:
	ImageFrame(const WCHAR* filename);
	ImageFrame(std::unique_ptr<Gdiplus::Bitmap> bitmap);

	void Display(HWND hwnd) override;
	void Resize(SIZE size) override;
	void Move(POINT dst) override;
	void Center(HWND hwnd, double resizeCoef = 1);
	void SetBitmap(const WCHAR* filename);
	void SetBitmap(std::unique_ptr<Gdiplus::Bitmap> bitmap);

private:
	double WndFit(HWND hwnd);

	std::unique_ptr<Gdiplus::Bitmap> m_pBitmap;
	//GdiplusInitializer m_gdiplusInitializer;
	POINT m_leftTop;
	SIZE m_size;
};