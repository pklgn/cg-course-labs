#include "LandscapeElementView.h"
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

LandscapeElementView::LandscapeElementView(const std::shared_ptr<LandscapeElement>& modelElement)
{
}

LandscapeElementView::Id LandscapeElementView::GetId() const
{
	return m_model->GetId();
}

void LandscapeElementView::Show() const
{
	// TODO: implement
}
