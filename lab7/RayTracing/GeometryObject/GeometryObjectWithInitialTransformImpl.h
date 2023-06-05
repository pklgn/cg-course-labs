#pragma once
#include "GeometryObjectImpl.h"

class CGeometryObjectWithInitialTransformImpl : public CGeometryObjectImpl
{
public:
	CGeometryObjectWithInitialTransformImpl(CMatrix4d const& tranform = CMatrix4d())
		: CGeometryObjectImpl(tranform)
	{
		UpdateInverseTransform();
	}

	/*
	������������� ����� ��������� ������� �������� ������������� �������
	*/
	virtual CMatrix4d const& GetInverseTransform() const
	{
		// ��� ����������� ������� ������ GetInverseTransform() ����� ���������� ����� ����������� ��������������
		return m_inverseTransform;
	}

protected:
	void SetInitialTransform(CMatrix4d const& initialTransform)
	{
		m_initialTransform = initialTransform;
		UpdateInverseTransform();
	}

	void OnUpdateTransform()
	{
		CGeometryObjectImpl::OnUpdateTransform();

		UpdateInverseTransform();
	}

private:
	void UpdateInverseTransform()
	{
		// ����������� ������� ���������� ��������������
		CMatrix4d inverseInitialTransform = m_initialTransform.GetInverseMatrix();

		// �������� �������� ������� �������������� ��������������� ������ � �����
		CMatrix4d const& inverseGeomObjectTransform = CGeometryObjectImpl::GetInverseTransform();

		// ��������� �������������� ������� ��������������, ���������� �������� ������� � �������� �������
		m_inverseTransform = inverseInitialTransform * inverseGeomObjectTransform;
	}

private:
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