#pragma once
#include "../IView.h"
#include "../../Common/Types/DimensionTypes.h"

class ButterflyView : public IView
{
public:
	ButterflyView(Size size, Vector3d position, float angle = 0.f);
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
