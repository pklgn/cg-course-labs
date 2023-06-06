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
	// Куб заданного размера и с центром в заданной точке получается
	// путем масштабирования и переноса базового куба (куб размером 1 с центром в начале координат)
	m_initialTransform.Translate(center.x, center.y, center.z);
	m_initialTransform.Scale(m_size, m_size, m_size);

	// Обновляем матрицу обратного преобразования
	OnUpdateTransform();
}

/*
	Вычисление матрицы обратного преобразования объекта
*/
CMatrix4d const& Cube::GetInverseTransform() const
{
	// При последующих вызовах метода GetInverseTransform() будет возвращено ранее вычисленное преобразование
	return m_inverseTransform;
}

void Cube::OnUpdateTransform()
{
	CGeometryObjectImpl::OnUpdateTransform();

	// При обновлении матрицы трансформации объекта необходимо обновить матрицу обратного преобразования

	// Инвертируем матрицу начального преобразования
	CMatrix4d inverseInitialTransform = m_initialTransform.GetInverseMatrix();

	// Получаем обратную матрицу преобразования геометрического объект в целом
	CMatrix4d const& inverseGeomObjectTransform = CGeometryObjectImpl::GetInverseTransform();

	// Вычисляем результирующую матрицу преобразоваиня, перемножив обратные матрицы в обратном порядке
	m_inverseTransform = inverseInitialTransform * inverseGeomObjectTransform;
}

bool Cube::Hit(CRay const& ray, CIntersection& intersection) const
{
	CRay invRay = Transform(ray, GetInverseTransform());
	auto rayOrigin = invRay.GetStart();
	auto rayDirection = invRay.GetDirection();
	double t1 = (m_center.x - m_size - rayOrigin.x) / rayDirection.x;
	double t2 = (m_center.x + m_size - rayOrigin.x) / rayDirection.x;
	double t3 = (m_center.y - m_size - rayOrigin.y) / rayDirection.y;
	double t4 = (m_center.y + m_size - rayOrigin.y) / rayDirection.y;
	double t5 = (m_center.z - m_size - rayOrigin.z) / rayDirection.z;
	double t6 = (m_center.z + m_size - rayOrigin.z) / rayDirection.z;
	
	// https://gamedev.stackexchange.com/questions/18436/most-efficient-aabb-vs-ray-collision-algorithms
	double tmin = std::max(std::max(std::min(t1, t2), std::min(t3, t4)), std::min(t5, t6));
	double tmax = std::min(std::min(std::max(t1, t2), std::max(t3, t4)), std::max(t5, t6));

	// if tmax < 0, ray (line) is intersecting AABB, but the whole AABB is behind us
	if (tmax < 0)
	{
		return false;
	}

	// if tmin > tmax, ray doesn't intersect AABB
	if (tmin > tmax)
	{
		return false;
	}


	CVector3d hitPoint = ray.GetPointAtTime(tmin);
	CVector3d hitPointInObjectSpace = invRay.GetPointAtTime(tmin);

	double epsilon = 0.000000000001;

	double cx = std::abs(hitPointInObjectSpace.x - (m_center.x - m_size));
	double fx = std::abs(hitPointInObjectSpace.x - (m_center.x + m_size));
	double cy = std::abs(hitPointInObjectSpace.y - (m_center.y - m_size));
	double fy = std::abs(hitPointInObjectSpace.y - (m_center.y + m_size));
	double cz = std::abs(hitPointInObjectSpace.z - (m_center.z - m_size));
	double fz = std::abs(hitPointInObjectSpace.z - (m_center.z + m_size));

	CVector3d normalInObjectSpace;
	if (cx < epsilon)
		normalInObjectSpace = CVector3d(-1.0, 0.0, 0.0);
	else if (fx < epsilon)
		normalInObjectSpace = CVector3d(1.0, 0.0, 0.0);
	else if (cy < epsilon)
		normalInObjectSpace = CVector3d(0.0, -1.0, 0.0);
	else if (fy < epsilon)
		normalInObjectSpace = CVector3d(0.0, 1.0, 0.0);
	else if (cz < epsilon)
		normalInObjectSpace = CVector3d(0.0, 0.0, -1.0);
	else if (fz < epsilon)
		normalInObjectSpace = CVector3d(0.0, 0.0, 1.0);
	else
		normalInObjectSpace = CVector3d(0.0, 0.0, 0.0);
	// TODO: нормализовать матрицу нормали
	// https://ru.stackoverflow.com/questions/767567/%D0%A8%D0%B5%D0%B9%D0%B4%D0%B5%D1%80%D1%8B-%D0%97%D0%B0%D1%87%D0%B5%D0%BC-%D0%BD%D1%83%D0%B6%D0%BD%D0%B0-%D0%BC%D0%B0%D1%82%D1%80%D0%B8%D1%86%D0%B0-%D0%BD%D0%BE%D1%80%D0%BC%D0%B0%D0%BB%D0%B5%D0%B9-normalmatrix-%D0%B8-%D0%BA%D0%B0%D0%BA-%D0%B5%D1%91-%D0%BD%D0%B0%D0%B9%D1%82%D0%B8

	CVector3d normalInWorldSpace = GetNormalMatrix() * normalInObjectSpace;

	// В список точек пересечения добавляем информацию о найденной точке 
	intersection.AddHit(CHitInfo(
		tmin, // Когда столкнулись
		*this, // С кем
		hitPoint, hitPointInObjectSpace, // Точка соударения луча с поверхностью
		normalInWorldSpace, normalInObjectSpace // Нормаль к поверхности в точке соударения
		));

	return true;
}


