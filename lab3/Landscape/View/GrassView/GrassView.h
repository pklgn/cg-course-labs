#pragma once
#include <vector>
#include "../IView.h"
#include "../../Common/Types/DimensionTypes.h"
#include "../../Common/Types/ColorTypes.h"

class GrassView : public IView
{
public:
	GrassView(
		Size size, Vector3d position, unsigned int vertices, const std::vector<RGB>& colors = {}, float angle = 0.f);

	void Show(unsigned int program) const override;

private:
	mutable Size m_size;
	Vector3d m_position;
	float m_angle;
	std::vector<RGB> m_colors;
	unsigned int m_vertices;
};