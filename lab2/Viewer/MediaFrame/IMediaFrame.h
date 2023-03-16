#pragma once
#include <windows.h>
#include <gdiplus.h>

class IMediaFrame
{
public:
	virtual ~IMediaFrame() = default;

	virtual void Display(Gdiplus::Graphics& g) = 0;
	virtual void Resize(SIZE size) = 0;
	virtual void Move(POINT dst) = 0;
	virtual void Center(HWND hwnd, double resizeCoef = 1) = 0;
	virtual double WndFit(HWND hwnd) = 0;
};
