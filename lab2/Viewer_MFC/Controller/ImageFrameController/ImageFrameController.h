#pragma once
#include "../../Model/ImageFrame/ImageFrame.h"
#include "../../View/ImageFrameView/ImageFrameView.h"

class ImageFrameController
{
public:
	void OnMouseMove();
	void OnLButtonDown();

private:
	ImageFrame& m_imageFrame;
	ImageFrameView& m_imageFrameView;
};
