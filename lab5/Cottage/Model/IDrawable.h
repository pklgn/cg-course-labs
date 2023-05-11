#pragma once
#include "ShaderProgram.h"

class IDrawable
{
	virtual void Draw(const glance::ShaderProgram& program) const = 0;
};