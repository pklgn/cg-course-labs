#pragma once
#include <memory>
#include <string>
#include "../../Model/LandscapeElement/LandscapeElement.h"

class LandscapeElementView
{
public:
	using Id = std::string;
	LandscapeElementView(const std::shared_ptr<LandscapeElement>& modelElement);
	Id GetId() const;

	void Draw() const;

private:
	std::shared_ptr<LandscapeElement> m_model;
};
