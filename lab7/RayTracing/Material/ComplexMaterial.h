#pragma once
#include "../Vector/Vector4.h"

/*
	—ложный материал, дл€ которого задан только лишь все три составл€ющих в модели ‘онга
*/
class ComplexMaterial
{
public:
	ComplexMaterial(void)
	{
	}

	CVector4f const& GetDiffuseColor() const
	{
		return m_diffuseColor;
	}

	void SetDiffuseColor(CVector4f const& diffuseColor)
	{
		m_diffuseColor = diffuseColor;
	}

	CVector4f const& GetAmbientColor() const
	{
		return m_ambientColor;
	}

	void SetAmbientColor(CVector4f const& ambientColor)
	{
		m_ambientColor = ambientColor;
	}

	CVector4f const& GetSpecularColor() const
	{
		return m_specularColor;
	}

	void SetSpecularColor(CVector4f const& specularColor)
	{
		m_specularColor = specularColor;
	}

	float GetSpecularCoefficient() const
	{
		return m_specularCoefficient;
	}

	void SetSpecularCoefficient(float coefficient)
	{
		m_specularCoefficient = coefficient;
	}

private:
	CVector4f m_diffuseColor;
	CVector4f m_ambientColor;
	CVector4f m_specularColor;
	
	float m_specularCoefficient{128};
};