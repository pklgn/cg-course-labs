﻿#pragma once
#include <memory>
#include <windows.h>
#include <gdiplus.h>
#include "../common/GdiplusInitializer.h"

class ImageFrame
{
public:
	ImageFrame(const WCHAR* filename);
	ImageFrame(std::unique_ptr<Gdiplus::Bitmap> bitmap);

	// FIXED: пометить конст методом
	void Display(Gdiplus::Graphics& g);
	// FIXED: убрать зависимость от HWND и передавать прямоугольник
	void Center(const RECT& clientRect, double resizeCoef = 1);
	void SetBitmap(const WCHAR* filename);
	void SetBitmap(std::unique_ptr<Gdiplus::Bitmap> bitmap);
	double WndFit(const RECT& clientRect);

	void Move(POINT deltaPosition);

	POINT GetLeftTop() const;
	SIZE GetSize() const;

private:
	std::unique_ptr<Gdiplus::Image*> m_thumbnailImage;
	std::unique_ptr<Gdiplus::Bitmap> m_pBitmap;
	POINT m_leftTop;
	SIZE m_size;
};