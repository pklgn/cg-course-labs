#pragma once
#include "ShaderProgram.h"
#include "ShaderMVPUniformMap.h"

class IDrawable
{
public:
	virtual ~IDrawable() = default;

	virtual void Draw(const glance::ShaderProgram& program, const glance::ShaderMVPUniformMap& uniformMap) const = 0;
};