#include "TextureCube.h"

using namespace glance;

TextureCube::TextureCube(std::unique_ptr<Cube>&& polytope, const std::string& texturePath)
	: TexturedPolytope(std::move(polytope), texturePath)
{
}
