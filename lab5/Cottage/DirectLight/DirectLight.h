#pragma once
#include <GL/glew.h>
#include <array>
#include "DimensionTypes.h"

// TODO: вынести этот класс в библиотеку
class DirectLight
{
public:
	DirectLight(Vector3d const& lightDirection = { 0, 0, 1 });

	void SetDirection(Vector3d const& direction);
	void SetDiffuseIntensity(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1);
	void SetAmbientIntensity(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1);
	void SetSpecularIntensity(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1);

	void SetLight(GLenum light);

private:
	Vector3d m_direction;
	std::array<GLfloat, 4> m_diffuse;
	std::array<GLfloat, 4> m_ambient;
	std::array<GLfloat, 4> m_specular;
};
