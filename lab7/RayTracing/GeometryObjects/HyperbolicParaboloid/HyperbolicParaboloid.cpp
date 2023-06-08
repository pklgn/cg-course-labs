#include "HyperbolicParaboloid.h"
#include "../../Intersection/Intersection.h"
#include "../../Ray/Ray.h"

HyperbolicParaboloid::HyperbolicParaboloid(CMatrix4d const& transform)
	: CGeometryObjectImpl(transform)
{
}

bool HyperbolicParaboloid::Hit(CRay const& ray, CIntersection& intersection) const
{
	// ¬ычисл€ем обратно преобразованный луч (вместо вполнени€ пр€мого преобразовани€ объекта)
	CRay invRay = Transform(ray, GetInverseTransform());

	unsigned numHits = 0; //  оличество точек пересечени€
	double hitTimes[2];

	/*
		Ќачало и направление луча
	*/
	CVector3d const& start = invRay.GetStart();
	CVector3d const& dir = invRay.GetDirection();

	/*
		 оэффициенты квадратного уравнени€ боковой стенки конического цилиндра
	*/
	double a = Sqr(dir.x) - Sqr(dir.z);
	double b = 2 * (start.x * dir.x) - 2 * (start.z * dir.z) - dir.y;
	double c = Sqr(start.x) - Sqr(start.z) - start.y;

	// ƒискриминант квадратного уравнени€
	double discr = b * b - 4 * a * c;

	// ¬рем€, которое луч проходит из точки испускани€, не испытыва€ столкновени€
	// Ќужно дл€ того, чтобы отраженный/преломленный луч мог оторватьс€ от границы объекта после столкновени€
	static const double HIT_TIME_EPSILON = 1e-6;

	/*
		≈сли дискриминант неотрицательный, то есть точки пересечени€ луча поверхностью
	*/
	if (discr > 0)
	{
		double invDoubleA = 1.0 / (2 * a);
		double discRoot = sqrt(discr);

		// ѕервый корень квадратного уравнени€ - врем€ столкновени€ с боковой стенкой
		double t = (-b - discRoot) * invDoubleA;

		// Ќас не интересуют пересечени€, происход€щие "в прошлом" луча
		if (t > HIT_TIME_EPSILON)
		{
			// ѕровер€ем координату z точки пересечени€. ќна не должна выходить за пределы
			// диапазона 0..1
			double hitX = start.x + dir.x * t;
			double hitY = start.z + dir.z * t;
			if (hitX >= -1 && hitX <= 1 &&
				hitY >= -1 && hitY <= 1)
			{
				hitTimes[numHits++] = t;
			}
		}

		// ¬торой корень квадратного уравнени€ - врем€ столкновени€ с боковой стенкой
		t = (-b + discRoot) * invDoubleA;
		// ¬ыполн€ем аналогичные проверки
		if (t > HIT_TIME_EPSILON)
		{
			double hitX = start.x + dir.x * t;
			double hitY = start.z + dir.z * t;
			if (hitX >= -1 && hitX <= 1 &&
				hitY >= -1 && hitY <= 1)
			{
				hitTimes[numHits++] = t;
			}
		}
	}

	// ƒлина проекции луча на ось z, меньше которой считаетс€, что пересечений с основанием и крышкой нет
	static const double EPSILON = 1e-8;

	// ≈сли ни одного пересечени€ не было найдено, дальнейшие вычислени€ проводить бессмысленно
	if (numHits == 0)
	{
		return false;
	}

	/*
		”пор€дочиваем событи€ столкновени€ в пор€дке возрастани€ времени столкновени€
	*/
	if (numHits == 2)
	{
		if (hitTimes[0] > hitTimes[1])
		{
			std::swap(hitTimes[0], hitTimes[1]);
		}
	}

	// ƒл€ всех найденных точек пересечени€ собираем полную информацию и
	// добавл€ем ее в объект intersection
	for (unsigned i = 0; i < numHits; ++i)
	{
		double const& hitTime = hitTimes[i];

		/*
			¬ычисл€ем координаты точки пересечени€
		*/
		CVector3d hitPoint = ray.GetPointAtTime(hitTime);
		CVector3d hitPointInObjectSpace = invRay.GetPointAtTime(hitTime);
		CVector3d hitNormalInObjectSpace;

		hitNormalInObjectSpace = CVector3d(2 * hitPointInObjectSpace.x, -2 * hitPointInObjectSpace.z, -1);

		auto nDotR = Dot(hitNormalInObjectSpace, dir);
		if (nDotR > 0)
		{
			hitNormalInObjectSpace = -hitNormalInObjectSpace;
		}

		/*
			—обираем информацию о точке столкновени€
		*/
		CVector3d hitNormal = GetNormalMatrix() * hitNormalInObjectSpace;


		CHitInfo hit(
			hitTime, *this,
			hitPoint, hitPointInObjectSpace,
			hitNormal, hitNormalInObjectSpace);

		// ƒобавл€ем точку столкновени€ в список
		intersection.AddHit(hit);
	}

	// ¬озвращаем true, если было найдено хот€ бы одно пересечение
	return intersection.GetHitsCount() > 0;
}