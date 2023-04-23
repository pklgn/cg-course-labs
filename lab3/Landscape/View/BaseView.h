#pragma once
#include <vector>

#include <ColorTypes.h>
#include <DimensionTypes.h>

#include "IView.h"

class BaseView : public IView
{
public:
	BaseView(Size size, Vector3d position, float angle, const std::vector<RGB> colors);

protected:
	mutable Size m_size;
	Vector3d m_position;
	float m_angle;
	std::vector<RGB> m_colors;
};