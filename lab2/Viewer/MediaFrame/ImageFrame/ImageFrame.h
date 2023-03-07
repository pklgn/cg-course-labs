#pragma once
#include <memory>
#include <gdiplus.h>
#include "../IMediaFrame.h"
#include "../../common/GdiplusInitializer.h"

class ImageFrame : public IMediaFrame
{
public:
	ImageFrame(HWND hwnd, const WCHAR* filename, RECT frame);

	void Display(HWND hwnd) override;
	void Resize(POINT size) override;
	void Move(POINT dst) override;
	void ChangeSource() override;

private:
	std::unique_ptr<Gdiplus::Bitmap> m_pBitmap;
	RECT m_frame;
	GdiplusInitializer m_gdiplusInitializer;
};