#pragma once
#include <memory>
#include <windows.h>
#include <gdiplus.h>
#include "../../Common/Observer/IObserver.h"
#include "../../Model/ImageFrame/ImageFrame.h"

class ImageFrameView : public IObserver<ImageFrameData>
{
public:
	ImageFrameView(ImageFrame& imageFrame);
	~ImageFrameView();

	void Display(Gdiplus::Graphics& g);

	void Update(const ImageFrameData& data);

private:
	std::unique_ptr<Gdiplus::Image*> m_pThumbnailImage;
	ImageFrame& m_imageFrame;
};
