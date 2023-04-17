#pragma once
#include <vector>
#include "../IView.h"
#include "../LandscapeElementView/LandscapeElementView.h"

class LandscapeView : public IView
{
public:
	void Show() const override;

private:
	std::vector<LandscapeElementView> m_elementsView;
};
