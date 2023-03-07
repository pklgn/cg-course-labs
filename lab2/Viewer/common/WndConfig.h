#pragma once
#include <tchar.h>
#include <string>
#include <unordered_map>

struct EnumClassHash
{
	template <typename T>
	std::size_t operator()(T t) const
	{
		return static_cast<std::size_t>(t);
	}
};

enum class WndKeyEntities : size_t
{
	CLASS_NAME = 0,
	WINDOW_TITLE,
};

const std::unordered_map<WndKeyEntities, TCHAR, EnumClassHash> WNDENTITIES = {
	{ WndKeyEntities::CLASS_NAME, _T("MainWndClass") },
	{ WndKeyEntities::WINDOW_TITLE, _T("Drawing raster images") },
};
