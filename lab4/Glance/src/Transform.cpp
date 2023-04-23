#include "../pch.h"

#include "Transform.h"

glm::mat4 Transform::BuildTranslate(float x, float y, float z)
{
	glm::mat4 trans = glm::mat4(1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		x, y, z, 1.0);

	return trans;
}

glm::mat4 Transform::BuildRotateX(float rad)
{
	glm::mat4 xrot = glm::mat4(1.0, 0.0, 0.0, 0.0,
		0.0, cos(rad), -sin(rad), 0.0,
		0.0, sin(rad), cos(rad), 0.0,
		0.0, 0.0, 0.0, 1.0);

	return xrot;
}

glm::mat4 Transform::BuildRotateY(float rad)
{
	glm::mat4 yrot = glm::mat4(cos(rad), 0.0, sin(rad), 0.0,
		0.0, 1.0, 0.0, 0.0,
		-sin(rad), 0.0, cos(rad), 0.0,
		0.0, 0.0, 0.0, 1.0);

	return yrot;
}

glm::mat4 Transform::BuildRotateZ(float rad)
{
	glm::mat4 zrot = glm::mat4(cos(rad), -sin(rad), 0.0, 0.0,
		sin(rad), cos(rad), 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0);

	return zrot;
}

glm::mat4 Transform::BuildScale(float x, float y, float z)
{
	glm::mat4 scale = glm::mat4(x, 0.0, 0.0, 0.0,
		0.0, y, 0.0, 0.0,
		0.0, 0.0, z, 0.0,
		0.0, 0.0, 0.0, 1.0);

	return scale;
}
