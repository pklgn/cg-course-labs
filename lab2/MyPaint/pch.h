// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

// add headers that you want to pre-compile here
// https://stackoverflow.com/questions/48882439/how-to-restore-auto-ptr-in-visual-studio-c17 решает проблему отсутствующего auto_ptr в std:c++17
#define _HAS_AUTO_PTR_ETC 1

#include <algorithm>
#include <fstream>
#include <windows.h>
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
#include <memory>
#include <mutex>
#include <stdexcept>
#include <tchar.h>
#include <vector>
#include <optional>
#include <windowsx.h>
#include <winuser.h>

#endif // PCH_H
