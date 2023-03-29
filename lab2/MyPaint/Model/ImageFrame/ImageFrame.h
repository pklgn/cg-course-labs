#pragma once
#include <memory>
#include "../../Common/Observer/Observable.h"
#include "ImageFrameData/ImageFrameData.h"

class ImageFrame : public Observable<ImageFrameData>
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

	void DrawLine(POINT from, POINT to);

protected:
	ImageFrameData GetChangedData() const override;

private:
	std::unique_ptr<Gdiplus::Bitmap> m_pBitmap;
	double m_resizeBitmapCoef = 1;
	POINT m_leftTop;
	SIZE m_size;
	ImageFrameData m_changedData;
};
