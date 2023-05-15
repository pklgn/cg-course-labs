#include "TexturePyramid.h"
#include "Texture.h"

using namespace glance;

TexturePyramid::TexturePyramid(std::unique_ptr<Pyramid>&& polytope, const std::string& texturePath)
	: TexturedPolytope(std::move(polytope), texturePath)
{
}
