#pragma once
#include "../../Common/Types/ColorTypes.h"
#include "../../Common/Types/DimensionTypes.h"
#include "../IView.h"
#include <vector>

class CloudView : public IView
{
public:
	CloudView(
		Size size, Vector3d position, const std::vector<RGB>& colors = {}, float angle = 0.f);

	void Show(unsigned int program) const override;

private:
	mutable Size m_size;
	Vector3d m_position;
	float m_angle;
	std::vector<RGB> m_colors;
};