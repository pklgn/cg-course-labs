#include "ImageFrame.h"

ImageFrame::ImageFrame(std::unique_ptr<Bitmap>&& pBitmap, RECT frame)
	: m_pBitmap(std::move(pBitmap))
	, m_frame(frame)
{
}

void ImageFrame::Display(HWND hwnd)
{
}
