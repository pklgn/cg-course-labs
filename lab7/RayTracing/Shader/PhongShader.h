#pragma once
#include "IShader.h"
#include "../Material/ComplexMaterial.h"

class PhongShader : public IShader
{
public:
	PhongShader(const ComplexMaterial& material);

	/*
		� �������� ��������� ������� ��������� ����� CSimpleMaterial, �������� � ���������� ������
		��������� ���� ��������� ����������� �������
	*/
	void SetMaterial(ComplexMaterial const& material);

	/*
		���������� ����� � �������
	*/
	virtual CVector4f Shade(CShadeContext const& shadeContext) const;

private:
	ComplexMaterial m_material;
};
