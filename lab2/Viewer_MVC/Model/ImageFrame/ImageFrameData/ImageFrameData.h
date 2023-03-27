#pragma once
#include <windows.h>
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
#include <optional>

struct ImageFrameData
{
	std::optional<Gdiplus::Bitmap*> pBitmap;
	std::optional<POINT> leftTop;
	std::optional<SIZE> size;
};