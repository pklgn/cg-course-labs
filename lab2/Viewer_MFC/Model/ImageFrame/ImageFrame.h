#pragma once
#include <memory>
#include <windows.h>
#include <gdiplus.h>
#include "../../Common/Observer/IObservable.h"

class ImageFrame : public IObservable
{
public:
	ImageFrame(const WCHAR* filename);
	ImageFrame(std::unique_ptr<Gdiplus::Bitmap> bitmap);

	double WndFit(const RECT& clientRect);
	void Center(const RECT& clientRect, double resizeCoef = 1);
	void Move(POINT deltaPosition);

	void SetBitmap(const WCHAR* filename);
	void SetBitmap(std::unique_ptr<Gdiplus::Bitmap> bitmap);

	POINT GetLeftTop() const;
	SIZE GetSize() const;
	Gdiplus::Image* GetThumbnailImage(SIZE thumbnailSize) const;

private:
	std::unique_ptr<Gdiplus::Bitmap> m_pBitmap;
	POINT m_leftTop;
	SIZE m_size;
};
