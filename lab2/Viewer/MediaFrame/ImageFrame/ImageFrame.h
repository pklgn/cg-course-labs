#pragma once
#include <memory>
#include <gdiplus.h>
#include "../IMediaFrame.h"

class ImageFrame : public IMediaFrame
{
public:
	ImageFrame(std::unique_ptr<Bitmap>&& pBitmap, RECT frame);

	void Display(HWND hwnd) override;
	void Resize(POINT size) override;
	void Move(POINT dst) override;
	void ChangeSource() override;

private:
	std::unique_ptr<Bitmap> m_pBitmap;
	RECT m_frame;
};