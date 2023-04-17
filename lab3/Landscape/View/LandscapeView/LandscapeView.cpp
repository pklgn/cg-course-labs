#include "LandscapeView.h"

void LandscapeView::Show() const
{
	// TODO: implement
	for (auto&& elementView : m_elementsView)
	{
		elementView.Show();
	}
}
