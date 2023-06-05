#pragma once
#include "ILightSource_fwd.h"
#include "../Vector/Vector_fwd.h"
#include "../Matrix/Matrix_fwd.h"

/*
	Интерфейс "Источник света"
*/
class ILightSource
{
public:
	virtual ~ILightSource(void) = default;

	/*
		Установка и получение матрицы трансформации источника света
	*/
	virtual void SetTransform(CMatrix4d const& transform) = 0;
	virtual CMatrix4d const& GetTransform() const = 0;

	/*
		Установка и получение интенсивности диффузного света
	*/
	virtual void SetDiffuseIntensity(CVector4f const& diffuseIntensity) = 0;
	virtual CVector4f const& GetDiffuseIntensity() const = 0;

	/*
		Установка и получение интенсивности фонового света
	*/
	virtual void SetAmbientIntensity(CVector4f const& ambientIntensity) = 0;
	virtual CVector4f const& GetAmbientIntensity() const = 0;

	/*
		Установка и получение интенсивности отраженного света
	*/
	virtual void SetSpecularIntensity(CVector4f const& specularIntensity) = 0;
	virtual CVector4f const& GetSpecularIntensity() const = 0;

	/*
		Интенсивность света, излучаемого в направлении от источника к заданной точке, заданной в мировой системе координат.
		Для точечных источников позволяет задать ослабление света в зависимости от расстояния
		Для конических источников света попутно позволяет задать ослабление излучаемого света в зависимости
		от угла отклонения от вектора направления
	*/
	virtual double GetIntensityInDirection(CVector3d const& direction) const = 0;

	/*
		Направление на источник света из указанной точки, заданной в мировой системе координат
	*/
	virtual CVector3d GetDirectionFromPoint(CVector3d const& point) const = 0;

	// Получение позиции источника света в мировых координатах
	virtual CVector3d const& GetPositionInWorldSpace() const = 0;
};
