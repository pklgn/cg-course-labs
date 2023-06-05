#pragma once
#include "ILightSource.h"
#include "../Matrix/Matrix4.h"
#include "../Vector/Vector4.h"
#include "../Vector/VectorMath.h"

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

	virtual CVector3d const& GetPositionInWorldSpace() const
	{
		return m_positionInWorldSpace;
	}

protected:
	CLightSourceImpl(CMatrix4d const& transform = CMatrix4d(), const CVector3d& position = CVector3d())
		: m_transform(transform)
		, m_position(position)

	{
	}

	//	Обновление позиции источника света в мировых координатах в зависимости от матрицы трансформации
	void UpdatePositionInWorldSpace()
	{
		m_positionInWorldSpace = GetTransform() * CVector4d(m_position, 1);
	}

private:
	CVector4f m_diffuseIntensity;
	CVector4f m_ambientIntensity;
	CVector4f m_specularIntensity;
	CMatrix4d m_transform;

	// Начальная позиция источника света
	CVector3d m_position;
	// Вычисленная позиция источника света в мировых координатах
	CVector3d m_positionInWorldSpace;
};
