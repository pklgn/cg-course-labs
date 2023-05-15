#pragma once
#include "Cube.h"
#include "../TexturedPolytope.h"

class TextureCube : public TexturedPolytope
{
public:
	TextureCube(std::unique_ptr<Cube>&& polytope, const std::string& texturePath);
};
