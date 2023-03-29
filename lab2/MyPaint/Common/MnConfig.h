#pragma once
#include <tchar.h>
#include <winnt.h>
#include <unordered_map>

enum class MenuIDKey
{
	NEW,
	SAVE
};

const std::unordered_map<MenuIDKey, UINT> MenuID = {
	{ MenuIDKey::NEW, 1 },
	{ MenuIDKey::SAVE, 2 },
};