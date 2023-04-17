#pragma once
#include <vector>
#include "../LandscapeElement/LandscapeElement.h"

class Landscape
{
public:
	int GetCount() const;
	void AppendLandscapeElement(const LandscapeElement& element);

private:
	std::vector<LandscapeElement> m_elements;
};
