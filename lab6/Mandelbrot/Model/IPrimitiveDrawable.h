#pragma once
#include <glm/glm.hpp>

class IPrimitiveDrawable
{
public:
	virtual ~IPrimitiveDrawable() = default;

	virtual void Draw() const = 0;

	virtual glm::mat4 BuildModelMatrix() const = 0;
};