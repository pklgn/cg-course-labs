#pragma once
#include "IPolytopeDrawable.h"
#include "OpenGLPrimitive/BasePrimitive.h"

class BasePolytope : public IPolytopeDrawable, public BasePrimitive
{
public:
	BasePolytope(const std::string& verticesFilePath, Size size, Vector3d position, Vector3d angle = { 0.f, 0.f, 0.f });

	void Draw() const override;

	glm::mat4 BuildModelMatrix() const override;
};