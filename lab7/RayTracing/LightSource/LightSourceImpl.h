#pragma once
#include "ILightSource.h"
#include "../Matrix/Matrix4.h"
#include "../Vector/Vector4.h"

/*
	Реализация методов, общих для различных типов источников света
*/
class CLightSourceImpl : public ILightSource
{
public:
	/*
		Получение матрицы трансформации источника света
	*/
	CMatrix4d const& GetTransform() const
	{
		return m_transform;
	}

	/*
		Установка матрицы трансформации источника света
	*/
	void SetTransform(CMatrix4d const& transform)
	{
		m_transform = transform;
	}

	/*
	Установка интенсивности диффузной составляющей света
	*/
	virtual void SetDiffuseIntensity(CVector4f const& diffuseIntensity)
	{
		m_diffuseIntensity = diffuseIntensity;
	}

	/*
	Получение интенсивности диффузной составляющей источника света
	*/
	virtual CVector4f const& GetDiffuseIntensity() const
	{
		return m_diffuseIntensity;
	}

	/*
	Установка интенсивности отраженной составляющей света
	*/
	virtual void SetSpecularIntensity(CVector4f const& specularIntensity)
	{
		m_specularIntensity = specularIntensity;
	}

	/*
	Получение интенсивности отраженной составляющей источника света
	*/
	virtual CVector4f const& GetSpecularIntensity() const
	{
		return m_specularIntensity;
	}

	/*
	Установка интенсивности фоновой составляющей света
	*/
	virtual void SetAmbientIntensity(CVector4f const& ambientIntensity)
	{
		m_ambientIntensity = ambientIntensity;
	}

	/*
	Получение интенсивности фоновой составляющей источника света
	*/
	virtual CVector4f const& GetAmbientIntensity() const
	{
		return m_ambientIntensity;
	}

protected:
	CLightSourceImpl(CMatrix4d const& transform = CMatrix4d())
		:m_transform(transform)
	{
	}

private:
	CVector4f m_diffuseIntensity;
	CVector4f m_ambientIntensity;
	CVector4f m_specularIntensity;
	CMatrix4d m_transform;
};
