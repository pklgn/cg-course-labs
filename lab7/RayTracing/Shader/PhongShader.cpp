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
		�������� ����� �� ��������� ������������ ��� ����, ����� ��������� �����
		������� �� ���������� ����� � ������������ �������������� �����
	*/
	CScene const& scene = shadeContext.GetScene();

	// �������������� ����
	CVector4f shadedColor;

	const size_t numLights = scene.GetLightsCount();

	// ����������� �� ���� ���������� ����� � �����
	for (size_t i = 0; i < numLights; ++i)
	{
		// �������� �������� �����
		ILightSource const& light = scene.GetLight(i);

		// ��������� ������ ����������� �� �������� ����� �� ������� �����
		CVector3d lightDirection = light.GetDirectionFromPoint(shadeContext.GetSurfacePoint());

		// ������� ����, �������� ��� �� ����� ������� � ������������ ������� � ����������� �������� ��������� �����
		bool isInShadow = CastSecondaryRay(shadeContext.GetSurfacePoint(), shadeContext.GetScene(), lightDirection);

		// ��������� ������������� ����� � ����������� �� ��������� � ������� �����
		double lightIntensity = light.GetIntensityInDirection(-lightDirection);

		// �������� ������� � ����������� � �������������� �����
		CVector3d const& n = shadeContext.GetSurfaceNormal();

		// ��������� ��������� ������������ ������� � ���-������� ����������� �� �������� �����
		double nDotL = Max(Dot(n, Normalize(lightDirection)), 0.0);

		// ��������� ��������� ���� �����
		CVector4f diffuseColor = static_cast<float>(nDotL * lightIntensity) * light.GetDiffuseIntensity() * m_material.GetDiffuseColor();

		// ������ ���������� ���� �����
		// halfway ������ ������ ������-�����; �� https://compgraphics.info/3D/lighting/phong_reflection_model.php
		CVector3d h = Normalize(lightDirection - shadeContext.GetRayDirection());
		double hDotN = Max(Dot(h, n), 0.0);
		CVector4f specularColor = static_cast<float>(pow(hDotN, m_material.GetSpecularCoefficient())) * light.GetSpecularIntensity() * m_material.GetSpecularColor();


		// ������ ������� ��������� �����
		CVector4f ambientColor = light.GetAmbientIntensity() * m_material.GetAmbientColor();

		// � ��������������� ����� ������������ ����������� ��������� ����
		if (!isInShadow)
		{
			shadedColor += diffuseColor;
			shadedColor += specularColor;
		}
		shadedColor += ambientColor;

	} // ����������� ������ �������� ��� ������ ���������� �����

	// ���������� �������������� ���� �����
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
