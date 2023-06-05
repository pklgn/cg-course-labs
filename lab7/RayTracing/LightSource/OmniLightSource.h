#pragma once
#include "LightSourceImpl.h"
#include "../Vector/Vector4.h"

/*
	Класс "Точечный источник света", характеризующийся позицией в пространстве.
	Для данного типа источника света можно задать коэффициенты ослабления света в зависимости
	от расстояния до объекта
*/
class COmniLightSource : public CLightSourceImpl
{
public:
	COmniLightSource(
		CVector3d const& position = CVector3d(),
		CMatrix4d const& transform = CMatrix4d());

	/*
	Перегруженный метод установки матрицы трансформации
	*/
	virtual void SetTransform(CMatrix4d const& transform);

	/*
	Вычисление направления из точки пространства к источнику света
	*/
	virtual CVector3d GetDirectionFromPoint(CVector3d const& point) const;

	/*
	Вычисление интенсивности света, излучаемой в заданном направлении
	*/
	virtual double GetIntensityInDirection(CVector3d const& direction) const;

	/*
	Установка коэффициентов ослабления излучаемой интенсивности в зависимости от расстояния
	*/
	void SetAttenuation(
		double const& constantAttenuation,
		double const& linearAttenuation,
		double const& quadraticAttenuation);

private:
	// Коэффициенты ослабления света в зависимосит от расстояния
	double m_constantAttenuation;
	double m_linearAttenuation;
	double m_quadraticAttenuation;
};

using COmniLightPtr = std::shared_ptr<COmniLightSource>;