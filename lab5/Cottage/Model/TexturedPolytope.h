#pragma once
#include "OpenGLPrimitive/BasePrimitive.h"
#include "Texture.h"
#include "BasePolytope.h"

class TexturedPolytope : public IPolytopeDrawable
{
public:
	void Draw() const override;
	glm::mat4 BuildModelMatrix() const override;

protected:
	TexturedPolytope(std::unique_ptr<IPolytopeDrawable>&& polytope, const std::string& texturePath);

private:
	std::unique_ptr<IPolytopeDrawable> m_polytope;
	glance::Texture m_texture;
};
