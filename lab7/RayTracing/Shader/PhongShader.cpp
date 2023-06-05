#include "PhongShader.h"
#include "../LightSource/ILightSource.h"
#include "../Intersection/Intersection.h"
#include "../Scene/Scene.h"
#include "../Vector/Vector4.h"
#include "../Vector/VectorMath.h"
#include "ShadeContext.h"
#include "../Ray/Ray.h"
#include "../Intersection/Intersection.h"

bool CastSecondaryRay(const CVector3d& rayStart, const CScene& scene, const CVector3d lightDirection);

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

		// Считаем тени, выпуская луч из точки касания с поверхностью объекта в направлении текущего источника света
		bool isInShadow = CastSecondaryRay(shadeContext.GetSurfacePoint(), shadeContext.GetScene(), lightDirection);

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
		if (!isInShadow)
		{
			shadedColor += diffuseColor;
			shadedColor += specularColor;
		}
		shadedColor += ambientColor;

	} // Проделываем данные действия для других источников света

	// Возвращаем результирующий цвет точки
	return shadedColor;
}

bool CastSecondaryRay(const CVector3d& rayStart, const CScene& scene, const CVector3d lightDirection)
{
	CVector3d rayDirection = Normalize(lightDirection);
	CRay checkShadowRay = CRay(rayStart, rayDirection);
	CIntersection bestIntersection;
	CSceneObject const* pSceneObject = NULL;
	
	bool wasHit = scene.GetFirstHit(checkShadowRay, bestIntersection, &pSceneObject);
	bool result = wasHit;
	if (wasHit)
	{
		auto hitTime = bestIntersection.GetHit(0).GetHitTime();
		result = ((hitTime > 0) && (bestIntersection.GetHit(0).GetHitTime() < lightDirection.GetLength()));
	}

	return result;
}
