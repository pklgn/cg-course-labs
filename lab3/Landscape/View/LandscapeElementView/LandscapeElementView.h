#pragma once
#include <memory>
#include <string>
#include "../../Model/LandscapeElement/LandscapeElement.h"
#include "../IView.h"

class LandscapeElementView : public IView
{
public:
	using Id = std::string;
	LandscapeElementView(const std::shared_ptr<LandscapeElement>& modelElement);
	Id GetId() const;

private:
	std::shared_ptr<LandscapeElement> m_model;
};
