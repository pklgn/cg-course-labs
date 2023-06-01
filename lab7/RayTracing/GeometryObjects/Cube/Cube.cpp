#include "Cube.h"
#include <algorithm>
#include "../../Ray/Ray.h"
#include "../../Intersection/Intersection.h"

Cube::Cube(double size, CVector3d const& center, CMatrix4d const& transform)
	: CGeometryObjectImpl(transform)
	, m_size(size)
	, m_center(center)
	, m_transform(transform)
{
}

bool Cube::Hit(CRay const& ray, CIntersection& intersection) const
{
	CRay invRay = Transform(ray, GetInverseTransform());
	auto rayOrigin = invRay.GetStart();
	auto rayDirection = invRay.GetDirection();
	double tmin = (m_center.x - m_size - rayOrigin.x) / rayDirection.x;
	double tmax = (m_center.x + m_size - rayOrigin.x) / rayDirection.x;
	double tymin = (m_center.y - m_size - rayOrigin.y) / rayDirection.y;
	double tymax = (m_center.y + m_size - rayOrigin.y) / rayDirection.y;

	if (tmin > tymax || tymin > tmax)
	{
		return false;
	}

	if (tymin > tmin)
	{
		tmin = tymin;
	}

	if (tymax < tmax)
	{
		tmax = tymax;
	}

	double tzmin = (m_center.z - m_size - rayOrigin.z) / rayDirection.z;
	double tzmax = (m_center.z + m_size - rayOrigin.z) / rayDirection.z;

	if (tmin > tzmax || tzmin > tmax)
	{
		return false;
	}

	if (tzmin > tmin)
	{
		tmin = tzmin;
	}

	if (tzmax < tmax)
	{
		tmax = tzmax;
	}

	if (tmin < 0 || tmin > tmax)
	{
		return false;
	}

	CVector3d hitPoint = ray.GetPointAtTime(tmin);

	CVector3d hitPointInObjectSpace = invRay.GetPointAtTime(tmin);

	CVector3d normalInObjectSpace = {
		(hitPoint.x == (m_center.x - m_size)
			? -1.0
				: hitPoint.x == (m_center.x + m_size)
				? 1.0
				: 0.0),
		(hitPoint.y == (m_center.y - m_size)
			? -1.0
				: hitPoint.y == (m_center.y + m_size)
				? 1.0
				: 0.0),
		(hitPoint.z == (m_center.z - m_size)
			? -1.0
				: hitPoint.z == (m_center.z + m_size)
				? 1.0
				: 0.0)
	};

	CVector3d normalInWorldSpace = GetNormalMatrix() * normalInObjectSpace;

	// В список точек пересечения добавляем информацию о найденной точке пересечения
	intersection.AddHit(CHitInfo(
		tmin, // Когда столкнулись
		*this, // С кем
		hitPoint, hitPointInObjectSpace, // Точка соударения луча с поверхностью
		normalInWorldSpace, normalInObjectSpace // Нормаль к поверхности в точке соударения
		));

	return true;
}


