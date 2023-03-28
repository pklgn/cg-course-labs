#pragma once
#include <optional>
#include "../../ImageFrame/ImageFrame.h"

struct CollageData
{
	std::optional<ImageFrame*> pImageFrame;
	std::optional<size_t> collageIndex;
};