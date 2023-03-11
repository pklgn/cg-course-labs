#pragma once
#include <tchar.h>
#include <winnt.h>
#include <string>
#include <unordered_map>
#include "EnumClassHash.h"

enum class WndKeyEntities
{
	CLASS_NAME = 0,
	WINDOW_TITLE,
};

const std::unordered_map<WndKeyEntities, LPCWSTR, EnumClassHash> WNDENTITIES = {
	{ WndKeyEntities::CLASS_NAME, _T("MainWndClass") },
	{ WndKeyEntities::WINDOW_TITLE, _T("Drawing raster images") },
};
