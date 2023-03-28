#pragma once
#include "../../Model/Collage/Collage.h"
#include "../../View/CollageView/CollageView.h"

class CollageController
{
public:
	CollageController(Collage& collage, CollageView& collageView);

	void AppendImage(Gdiplus::Image& img, const RECT& clientRect);

	void OnSize(int cx, int cy);
	void OnPaint(Gdiplus::Graphics& g, const RECT& clientRect);
	void OnLButtonUp();
	void OnLButtonDown(POINT mousePosition, BOOL fDoubleClick);
	void OnLButtonDblClk(POINT mousePosition, BOOL fDoubleClick);
	void OnDestroy();
	RECT OnMouseMove(POINT mousePosition);

private:
	ImageFrame* FindActiveImageFrame(POINT mousePosition);

	Collage& m_collage;
	CollageView& m_collageView;

	POINT m_prevMousePosition;
	ImageFrame* m_pActiveImageFrame = nullptr;
};
