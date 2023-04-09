#pragma once
#include "../../GraphWindow/IDrawable.h"

class CoordinateSystem : public IDrawable
{
public:
	CoordinateSystem(float left, float right, float bottom, float top);

	void Draw() override;

private:
	float m_width;
	float m_height;
};
