#pragma once
#include "../../GraphWindow/IDrawable.h"

class Chart : public IDrawable
{
public:
	Chart(float left, float right, float bottom, float top);

	void Draw() override;

private:
	float m_left;
	float m_right;
	float m_bottom;
	float m_top;
};
