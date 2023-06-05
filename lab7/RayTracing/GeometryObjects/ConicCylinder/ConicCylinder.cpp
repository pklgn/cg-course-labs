#include "ConicCylinder.h"
#include "../../Intersection/Intersection.h"
#include "../../Ray/Ray.h"

ConicCylinder::ConicCylinder(
	double const& height, // ������ �������� (>0)
	double const& baseRadius, // ������ ��������� (>0)
	double const& capRadius, // ������ ������ (>=0, �� �� ��������� ������� ���������)
	CMatrix4d const& tranform)
	: CGeometryObjectWithInitialTransformImpl(tranform)
{
	assert(height >= 0);
	assert(baseRadius >= 0);
	assert(capRadius >= 0);

	/*
	��� ��������� ������ ���������� ����� ����������� ����� ����������� ����� �������������
	� ������� ���������� ��������� ������� 1, �������� ��������� 1 � �������� ������ m_smallRadius.

	������� �������� �������� m_smallRadius �������� ����������� ��������, � ����� ����������
	������� ���������� ��������������, ����������� ������� ���������� ������� � ���������
	*/
	m_smallRadius = (capRadius < baseRadius) ? (capRadius / baseRadius) : (baseRadius / capRadius);

	double maxRadius = (baseRadius > capRadius) ? baseRadius : capRadius;

	/*
	������ ������� ��������������
	*/
	CMatrix4d initialTransform;
	// ������ ��������� ���������������
	initialTransform.Scale(maxRadius, maxRadius, height);
	if (baseRadius < capRadius)
	{
		// � ������ ����� ������ ������ ������ ������� ��������� ���������� ��������������
		// ��������� ���������� ������� ���������� ������� ������������ ��������� z=0 �
		// ����������� �� 1 ����� ��� z
		initialTransform.Translate(0, 0, 1);
		initialTransform.Scale(1, 1, -1);
	}
	SetInitialTransform(initialTransform);
}

bool ConicCylinder::Hit(CRay const& ray, CIntersection& intersection) const
{
	// ��������� ������� ��������������� ��� (������ ��������� ������� �������������� �������)
	CRay invRay = Transform(ray, GetInverseTransform());

	/*
	��������� ������� ������ �������� ����������� �������� ����� ���:
	G(x, y, z) = x^2 + y^2 - (1 + (s - 1)*z)^2 = 0,
	���:
		0 <= z <= 1,
		r(0) = 1:	������ ���������
		r(1) = s:	������ ������ (�� ��������� ������� ���������)

	���������� ���������� ����� ���� P = S + c*t  (S - ����� ���������� ����, c - ����������� ����)
	� ��������� G, �������� ��������� ������� ������
	A*t^2 + 2*B*t + C = 0, ���:
		A = cx^2 + cy^2 - q^2
		B = Sx*cx + Sy*cy - F*q
		C = Sx^2 + Sy^2 - F^2, ���
			q = (s-1) * cz
			F = 1 + (s-1) * Sz
	���� ������������ B^2 - AC �����������, �� � ������� ������� ����������� ���
	���� ������������ �� �����������, �� ����� ���������, ��� ���������� z ����� ���������� ��������� � ��������� �� 0 �� 1

	������������ � ���������� ������� ���������� ����� ����������� � ���������� z=0.
	������������ ���� � ���������� ���������� ���
		x^2 + y^2 <= 1

	������������ � ������� ����������� �������� - 'nj ����������� � ���������� z=1
	������������ ���� � ������� ���������� ��� ���������� �������
		x^2 + y^2 < s^2
	*/

	/*
	�������������� ������������ ����������� ��������
	*/
	enum HitSurface
	{
		HIT_SIDE,
		HIT_BASE,
		HIT_CAP,
	};

	/*
	������� ���������� � ����������� ���� � ������������� ����������� ��������.
	*/
	struct HitPoint
	{
		double hitTime;
		HitSurface hitSurface;
	};

	unsigned numHits = 0; // ���������� ����� �����������
	HitPoint hitPoints[2]; // � �������� �������� ����������� �������� 2 ����� ����������� ����

	/*
	������ � ����������� ����
	*/
	CVector3d const& start = invRay.GetStart();
	CVector3d const& dir = invRay.GetDirection();

	/*
	��������������� ���������� ��� ��������� ����������
	*/
	double q = m_smallRadius - 1;
	double k = q * dir.z;
	double f = 1 + q * start.z;

	/*
	������������ ����������� ��������� ������� ������ ����������� ��������
	*/
	double a = Sqr(dir.x) + Sqr(dir.y) - Sqr(k);
	double b = (start.x * dir.x) + (start.y * dir.y) - (f * k);
	double c = Sqr(start.x) + Sqr(start.y) - Sqr(f);

	// ������������ ����������� ���������
	double discr = b * b - a * c;

	// �����, ������� ��� �������� �� ����� ����������, �� ��������� ������������
	// ����� ��� ����, ����� ����������/������������ ��� ��� ���������� �� ������� ������� ����� ������������
	static const double HIT_TIME_EPSILON = 1e-6;

	/*
	���� ������������ ���������������, �� ���� ����� ����������� ���� � ������� �������
	*/
	if (discr > 0)
	{
		double invA = 1.0 / a;
		double discRoot = sqrt(discr);

		// ������ ������ ����������� ��������� - ����� ������������ � ������� �������
		double t = (-b - discRoot) * invA;
		// ��� �� ���������� �����������, ������������ "� �������" ����
		if (t > HIT_TIME_EPSILON)
		{
			// ��������� ���������� z ����� �����������. ��� �� ������ �������� �� �������
			// ��������� 0..1
			double hitZ = start.z + dir.z * t;
			if (hitZ >= 0 && hitZ <= 1)
			{
				// ��������� ������� ���������� � ����� �����������
				HitPoint hit = { t, HIT_SIDE };
				hitPoints[numHits++] = hit;
			}
		}

		// ������ ������ ����������� ��������� - ����� ������������ � ������� �������
		t = (-b + discRoot) * invA;
		// ��������� ����������� ��������
		if (t > HIT_TIME_EPSILON)
		{
			double hitZ = start.z + dir.z * t;
			if (hitZ >= 0 && hitZ <= 1)
			{
				HitPoint hit = { t, HIT_SIDE };
				hitPoints[numHits++] = hit;
			}
		}
	}

	// ����� �������� ���� �� ��� z, ������ ������� ���������, ��� ����������� � ���������� � ������� ���
	static const double EPSILON = 1e-8;

	/*
	���� ��� ��������� ������������ ���� � �������� ��� ���� �������, ��� ������ ������ ������
	*/
	if ((numHits < 2) && (std::abs(dir.z) > EPSILON))
	{
		double invDirZ = 1.0 / dir.z;

		// ���� ����� ����� ����������� ���� � ����������
		double t = -start.z * invDirZ;

		/*
		���������� �����������, ������������ � ������������� �����, ��������� �����
		����������� � ���������� z=0 � ���������, ��������� �� ����� ������ ���������
		*/
		if (t >= HIT_TIME_EPSILON)
		{
			double hitX = start.x + dir.x * t;
			double hitY = start.y + dir.y * t;
			if (Sqr(hitX) + Sqr(hitY) < 1)
			{
				HitPoint hit = { t, HIT_BASE };
				hitPoints[numHits++] = hit;
			}
		}

		if (numHits < 2)
		{
			// ���� ����� ����� ����������� ���� � �������
			t = (1 - start.z) * invDirZ;

			// ���������� �����������, ������������ � ������������� �����, ��������� �����
			// ����������� � ���������� z=1 � ���������, ��������� �� ����� ������ ���������
			if (t > HIT_TIME_EPSILON)
			{
				double hitX = start.x + dir.x * t;
				double hitY = start.y + dir.y * t;
				if (Sqr(hitX) + Sqr(hitY) < Sqr(m_smallRadius))
				{
					HitPoint hit = { t, HIT_CAP };
					hitPoints[numHits++] = hit;
				}
			}
		}
	}

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
		if (hitPoints[0].hitTime > hitPoints[1].hitTime)
		{
			// std::swap �� ���������� ������������ ��-�� ������������ gcc
			// � ������� ������ �� ����� ������� � �����, ����������� ������ �������
			HitPoint tmp(hitPoints[0]);
			hitPoints[0] = hitPoints[1];
			hitPoints[1] = tmp;
		}
	}

	// ��� ���� ��������� ����� ����������� �������� ������ ���������� �
	// ��������� �� � ������ intersection
	for (unsigned i = 0; i < numHits; ++i)
	{
		HitPoint const& h = hitPoints[i];

		double const& hitTime = h.hitTime;

		/*
		��������� ���������� ����� �����������
		*/
		CVector3d hitPoint = ray.GetPointAtTime(hitTime);
		CVector3d hitPointInObjectSpace = invRay.GetPointAtTime(hitTime);
		CVector3d hitNormalInObjectSpace;

		/*
		� ����������� �� ���� ������������ ����������� ��������� ���������� ������� �������
		*/
		if (h.hitSurface == HIT_SIDE)
		{
			hitNormalInObjectSpace = CVector3d(hitPointInObjectSpace.x, hitPointInObjectSpace.y, -q * (1 + q * hitPointInObjectSpace.z));
		}
		else if (h.hitSurface == HIT_BASE)
		{
			hitNormalInObjectSpace = CVector3d(0, 0, -1);
		}
		else
		{
			hitNormalInObjectSpace = CVector3d(0, 0, 1);
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