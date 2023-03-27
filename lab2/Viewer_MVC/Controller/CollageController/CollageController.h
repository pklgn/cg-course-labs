#pragma once
#include "../../Model/Collage/Collage.h"
#include "../../View/CollageView/CollageView.h"

class CollageController
{
public:
	CollageController(Collage& collage, CollageView& collageView);

	void OnDestroy();
	void OnPaint(Gdiplus::Graphics& g, const RECT& clientRect);
	RECT OnMouseMove(POINT mousePosition);
	void OnLButtonDown(POINT mousePosition);
	void OnLButtonUp();

	void AppendImage(Gdiplus::Image& img);

private:
	ImageFrame* FindActiveImageFrame(POINT mousePosition);

	Collage& m_collage;
	CollageView& m_collageView;

	POINT m_prevMousePosition;
	ImageFrame* m_activeImageFrame = nullptr;
};
