#pragma once
#include <vector>
#include "../IView.h"
#include "../../Common/Types/DimensionTypes.h"
#include "../../Common/Types/ColorTypes.h"

class ButterflyView : public IView
{
public:
	ButterflyView(
		Size size, Vector3d position, const std::vector<RGB>& colors = {}, float angle = 0.f);
	void Show(unsigned int program) const override;

private:
	void DrawButterflyBody(unsigned int program) const;
	void DrawButterflyAntena(unsigned int program) const;
	void DrawBufferflyWingPart(unsigned int program) const;
	void DrawButterflyWing(unsigned int program) const;

	mutable Size m_size;
	Vector3d m_position;
	float m_angle;
};
