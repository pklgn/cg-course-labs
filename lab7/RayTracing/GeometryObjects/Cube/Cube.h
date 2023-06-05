#pragma once
#include "../../GeometryObject/GeometryObjectImpl.h"

class Cube : public CGeometryObjectImpl
{
public:
	Cube(double size = 1,
		CVector3d const& center = CVector3d(),
		CMatrix4d const& transform = CMatrix4d());

	/*
		������������� ����� ��������� ������� �������� ������������� �������
	*/
	virtual CMatrix4d const& GetInverseTransform() const;

	/*
		���������� ����� ����������� ���� � �����
	*/
	virtual bool Hit(CRay const& ray, CIntersection& intersection) const override;

protected:
	virtual void OnUpdateTransform() override;

private:
	double m_size;
	CVector3d m_center;
	CMatrix4d m_transform;

	/*
	��������� �������� ������� �������������, ����������� � ������ ����������
	�������������� ������� ����� � ������� ������������� �����
	*/
	CMatrix4d m_inverseTransform;

	/*
		��������� �������������, ����������� �������������� ������� ����� ���������� ������� � �������
		� ������ ��������� � ����� ��������� ������� � ������� � ��������� �����
	*/
	CMatrix4d m_initialTransform;
};
