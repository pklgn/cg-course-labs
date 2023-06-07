#include "HyperbolicParaboloid.h"
#include "../../Intersection/Intersection.h"
#include "../../Ray/Ray.h"

HyperbolicParaboloid::HyperbolicParaboloid(CVector3d const& center, CMatrix4d const& transform)
	: CGeometryObjectWithInitialTransformImpl(transform)
{
	CMatrix4d initialTransform;
	initialTransform.Translate(center.x, center.y, center.z);
}

bool HyperbolicParaboloid::Hit(CRay const& ray, CIntersection& intersection) const
{
	// ��������� ������� ��������������� ��� (������ ��������� ������� �������������� �������)
	CRay invRay = Transform(ray, GetInverseTransform());

	unsigned numHits = 0; // ���������� ����� �����������
	double hitTimes[2];

	/*
		������ � ����������� ����
	*/
	CVector3d const& start = invRay.GetStart();
	CVector3d const& dir = (invRay.GetDirection());

	/*
		������������ ����������� ��������� ������� ������ ����������� ��������
	*/
	double a = Sqr(dir.x) - Sqr(dir.z);
	double b = 2 * (start.x * dir.x) - 2 * (start.z * dir.z) - dir.y;
	double c = Sqr(start.x) - Sqr(start.z) - start.y;

	// ������������ ����������� ���������
	double discr = b * b - 4 * a * c;

	// �����, ������� ��� �������� �� ����� ����������, �� ��������� ������������
	// ����� ��� ����, ����� ����������/������������ ��� ��� ���������� �� ������� ������� ����� ������������
	static const double HIT_TIME_EPSILON = 1e-6;

	/*
		���� ������������ ���������������, �� ���� ����� ����������� ���� ������������
	*/
	if (discr > 0)
	{
		double invDoubleA = 1.0 / (2 * a);
		double discRoot = sqrt(discr);

		// ������ ������ ����������� ��������� - ����� ������������ � ������� �������
		double t = (-b - discRoot) * invDoubleA;

		// ��� �� ���������� �����������, ������������ "� �������" ����
		if (t > HIT_TIME_EPSILON)
		{
			// ��������� ���������� z ����� �����������. ��� �� ������ �������� �� �������
			// ��������� 0..1
			double hitX = start.x + dir.x * t;
			double hitY = start.z + dir.z * t;
			if (hitX >= -1 && hitX <= 1 &&
				hitY >= -1 && hitY <= 1)
			{
				hitTimes[numHits++] = t;
			}
		}

		// ������ ������ ����������� ��������� - ����� ������������ � ������� �������
		t = (-b + discRoot) * invDoubleA;
		// ��������� ����������� ��������
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

	// ����� �������� ���� �� ��� z, ������ ������� ���������, ��� ����������� � ���������� � ������� ���
	static const double EPSILON = 1e-8;

	// ���� �� ������ ����������� �� ���� �������, ���������� ���������� ��������� ������������
	if (numHits == 0)
	{
		return false;
	}

	/*
		������������� ������� ������������ � ������� ����������� ������� ������������
	*/
	if (numHits == 2)
	{
		if (hitTimes[0] > hitTimes[1])
		{
			std::swap(hitTimes[0], hitTimes[1]);
		}
	}

	// ��� ���� ��������� ����� ����������� �������� ������ ���������� �
	// ��������� �� � ������ intersection
	for (unsigned i = 0; i < numHits; ++i)
	{
		double const& hitTime = hitTimes[i];

		/*
			��������� ���������� ����� �����������
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
			�������� ���������� � ����� ������������
		*/
		CVector3d hitNormal = GetNormalMatrix() * hitNormalInObjectSpace;


		CHitInfo hit(
			hitTime, *this,
			hitPoint, hitPointInObjectSpace,
			hitNormal, hitNormalInObjectSpace);

		// ��������� ����� ������������ � ������
		intersection.AddHit(hit);
	}

	// ���������� true, ���� ���� ������� ���� �� ���� �����������
	return intersection.GetHitsCount() > 0;
}