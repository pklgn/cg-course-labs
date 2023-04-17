#pragma once
#include "../../Common/Types/DimensionTypes.h"

class LandscapeElement
{
public:
	void SetSize(Size size);
	Size GetSize() const;

	void SetPosition(Vector2d position);
	Vector2d GetPosition() const;

private:
	Size m_size;
	Vector2d m_position;
};
