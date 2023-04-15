#pragma once

class IDrawable
{
public:
	virtual ~IDrawable() = default;

	virtual void Draw() = 0;
};