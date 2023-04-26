#include "DirectLight.h"

DirectLight::DirectLight(Vector3d const& lightDirection)
	: m_direction(lightDirection)
{
	// TODO: вынести значения освещения по умолчанию в конфиг
	SetDiffuseIntensity(0.8, 0.8, 0.8, 1);
	SetAmbientIntensity(0.2, 0.2, 0.2, 1);
	SetSpecularIntensity(0.5, 0.5, 0.5, 1);
}

void DirectLight::SetDirection(Vector3d const& direction)
{
	m_direction = direction;
}

void DirectLight::SetDiffuseIntensity(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	m_diffuse[0] = r;
	m_diffuse[1] = g;
	m_diffuse[2] = b;
	m_diffuse[3] = a;
}

void DirectLight::SetAmbientIntensity(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	m_ambient[0] = r;
	m_ambient[1] = g;
	m_ambient[2] = b;
	m_ambient[3] = a;
}

void DirectLight::SetSpecularIntensity(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	m_specular[0] = r;
	m_specular[1] = g;
	m_specular[2] = b;
	m_specular[3] = a;
}

void DirectLight::SetLight(GLenum light)
{
	GLfloat lightDirection[4] = {
		m_direction.x,
		m_direction.y,
		m_direction.z,
		0
	};
	glLightfv(light, GL_POSITION, lightDirection);
	glLightfv(light, GL_DIFFUSE, m_diffuse.data());
	glLightfv(light, GL_AMBIENT, m_ambient.data());
	glLightfv(light, GL_SPECULAR, m_specular.data());
}
