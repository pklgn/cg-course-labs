#include "Landscape.h"

int Landscape::GetCount() const
{
	return static_cast<int>(m_elements.size());
}

void Landscape::AppendLandscapeElement(const std::shared_ptr<LandscapeElement>& element)
{
	m_elements.push_back(element);
}
