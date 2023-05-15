#pragma once
#include "../TexturedPolytope.h"
#include "Pyramid.h"

class TexturePyramid : public TexturedPolytope
{
public:
	TexturePyramid(std::unique_ptr<Pyramid>&& polytope, const std::string& texturePath);
};
