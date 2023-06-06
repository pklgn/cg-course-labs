#pragma once
#include "IShader.h"
#include "../Material/ComplexMaterial.h"

class PhongShader : public IShader
{
public:
	PhongShader(const ComplexMaterial& material);

	/*
		В качестве параметра шейдера выступает класс CSimpleMaterial, хранящий в простейшем случае
		диффузный цвет материала поверхности объекта
	*/
	void SetMaterial(ComplexMaterial const& material);

	/*
		Вычисление цвета с объекта
	*/
	virtual CVector4f Shade(CShadeContext const& shadeContext) const;

private:
	ComplexMaterial m_material;
};
