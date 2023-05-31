#include "PhongShader.h"
#include "../LightSource/ILightSource.h"
#include "../Scene/Scene.h"
#include "../Vector/Vector4.h"
#include "../Vector/VectorMath.h"
#include "ShadeContext.h"

void PhongShader::SetMaterial(ComplexMaterial const& material)
{
	m_material = material;
}

CVector4f PhongShader::Shade(CShadeContext const& shadeContext) const
{
	/*
		Получаем сцену из контекста закрашивания для того, чтобы вычислить вклад
		каждого из источников света в освещенность обрабатываемой точки
	*/
	CScene const& scene = shadeContext.GetScene();

	// Результирующий цвет
	CVector4f shadedColor;

	const size_t numLights = scene.GetLightsCount();

	// Пробегаемся по всем источникам света в сцене
	for (size_t i = 0; i < numLights; ++i)
	{
		// Получаем источник света
		ILightSource const& light = scene.GetLight(i);

		// Вычисляем вектор направления на источник света из текущей точки
		CVector3d lightDirection = light.GetDirectionFromPoint(shadeContext.GetSurfacePoint());

		// Вычисляем интенсивность света в направлении от источника к текущей точке
		double lightIntensity = light.GetIntensityInDirection(-lightDirection);

		// Получаем нормаль к поверхности в обрабатываемой точке
		CVector3d const& n = shadeContext.GetSurfaceNormal();

		// Вычисляем скалярное произведение нормали и орт-вектора направления на источник света
		double nDotL = Max(Dot(n, Normalize(lightDirection)), 0.0);

		// Вычисляем диффузный цвет точки
		CVector4f diffuseColor = static_cast<float>(nDotL * lightIntensity) * light.GetDiffuseIntensity() * m_material.GetDiffuseColor();

		// Найдем зеркальный цвет точки
		// halfway вектор модели Блинна-Фонга; см https://compgraphics.info/3D/lighting/phong_reflection_model.php
		CVector3d h = Normalize(lightDirection - shadeContext.GetRayDirection());
		double hDotN = Max(Dot(h, n), 0.0);
		CVector4f specularColor = static_cast<float>(pow(hDotN, m_material.GetSpecularCoefficient())) * light.GetSpecularIntensity() * m_material.GetSpecularColor();


		// Найдем фоновую составляю света
		CVector4f ambientColor = light.GetAmbientIntensity() * m_material.GetAmbientColor();

		// К результирующему цвету прибавляется вычисленный диффузный цвет
		shadedColor += diffuseColor;
		shadedColor += specularColor;
		shadedColor += ambientColor;

	} // Проделываем данные действия для других источников света

	// Возвращаем результирующий цвет точки
	return shadedColor;
}
