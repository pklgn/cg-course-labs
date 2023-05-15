#include "TexturedPolytope.h"

TexturedPolytope::TexturedPolytope(std::unique_ptr<IPolytopeDrawable>&& polytope, const std::string& texturePath)
	: m_polytope(std::move(polytope))
	, m_texture(texturePath)
{
}

void TexturedPolytope::Draw() const
{
	m_texture.Bind();
	m_polytope->Draw();
}

glm::mat4 TexturedPolytope::BuildModelMatrix() const
{
	return m_polytope->BuildModelMatrix();
}


