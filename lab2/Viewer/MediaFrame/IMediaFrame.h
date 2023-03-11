#pragma once
#include <windows.h>

class IMediaFrame
{
public:
	virtual ~IMediaFrame() = default;

	virtual void Display(HWND hwnd) = 0;
	virtual void Resize(POINT size) = 0;
	virtual void Move(POINT dst) = 0;
};
