#pragma once
#include <vector>
#include <memory>
#include "../LandscapeElement/LandscapeElement.h"

class Landscape
{
public:
	int GetCount() const;
	void AppendLandscapeElement(const std::shared_ptr<LandscapeElement>& element);

private:
	std::vector<std::shared_ptr<LandscapeElement>> m_elements;
};
