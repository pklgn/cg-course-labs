#pragma once
#include <vector>
#include "GL/glew.h"
#include "Types/GeometryTypes.h"
#include "OpenGLPrimitive/Primitive.h"
#include "ShaderMVPUniformMap.h"
#include "OpenGLPrimitive/IPrimitiveDrawable.h"
#include "../Model/Rectangle/Rectangle.h"

class Flag
{
public:
	Flag(Size windowSize, Size size, Vector3d position, Vector3d angle = { 0.f, 0.f, 0.f });

	void SetWindowSize(int width, int height);
	Size GetWindowSize() const;

	void Draw() const;
	void UpdateMVPMatrices() const;

private:
	struct FlagUniformMap
	{
		FlagUniformMap(const std::string& screenResolution, const std::string& radius, const std::string& thickness)
		{
			this->screenResolution = screenResolution;
			this->radius = radius;
			this->thickness = thickness;
		}

		std::string screenResolution;
		std::string radius;
		std::string thickness;
	};

	Size m_windowSize;
	Rectangle m_rectangle;

	glance::ShaderProgram m_shaderProgram;
	glance::ShaderMVPUniformMap m_shaderUniformMap;
	FlagUniformMap m_flagUniformMap;
};
