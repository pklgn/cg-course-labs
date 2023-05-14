#pragma once
#include <string>

namespace glance
{

struct ShaderMVPUniformMap
{
	ShaderMVPUniformMap(const std::string& modelUniform, const std::string& viewUniform, const std::string& projectionUniform);

	std::string modelUniform;
	std::string viewUniform;
	std::string projectionUniform;
};

}