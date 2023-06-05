#pragma once
#include "../../GeometryObject/GeometryObjectImpl.h"

class Cube : public CGeometryObjectImpl
{
public:
	Cube(double size = 1,
		CVector3d const& center = CVector3d(),
		CMatrix4d const& transform = CMatrix4d());

	/*
		Перегруженный метод получения матрицы обратной трансформации объекта
	*/
	virtual CMatrix4d const& GetInverseTransform() const;

	/*
		Нахождение точки пересечения луча с кубом
	*/
	virtual bool Hit(CRay const& ray, CIntersection& intersection) const override;

protected:
	virtual void OnUpdateTransform() override;

private:
	double m_size;
	CVector3d m_center;
	CMatrix4d m_transform;

	/*
	Параметры обратной матрицы трансформации, построенной с учетом начального
	преобразования базовой сферы и матрицы трансформации сферы
	*/
	CMatrix4d m_inverseTransform;

	/*
		Начальная трансформация, выполняющая преобразование базовой сферы единичного радиуса с центром
		в начале координат в сферу заданного радиуса с центром в указанной точке
	*/
	CMatrix4d m_initialTransform;
};
