#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>

class Transform
{
	static glm::mat4 BuildTranslate(float x, float y, float z);
	static glm::mat4 BuildRotateX(float rad);
	static glm::mat4 BuildRotateY(float rad);
	static glm::mat4 BuildRotateZ(float rad);
	static glm::mat4 BuildScale(float x, float y, float z);
};
