#pragma once
#include <glm/glm.hpp>

class IPolytopeDrawable
{
public:
	virtual ~IPolytopeDrawable() = default;

	virtual void Draw() const = 0;

	virtual glm::mat4 BuildModelMatrix() const = 0;
};