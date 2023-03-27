#pragma once
#include <tchar.h>
#include <winnt.h>
#include <string>
#include <unordered_map>

enum class WndKeyEntities
{
	CLASS_NAME = 0,
	WINDOW_TITLE,
};

struct EnumClassHash
{
	template <typename T>
	std::size_t operator()(const T& t) const
	{
		return static_cast<std::size_t>(t);
	}
};

const std::unordered_map<WndKeyEntities, LPCWSTR, EnumClassHash> WNDENTITIES = {
	{ WndKeyEntities::CLASS_NAME, _T("MainWndClass") },
	{ WndKeyEntities::WINDOW_TITLE, _T("Drawing raster images") },
};
