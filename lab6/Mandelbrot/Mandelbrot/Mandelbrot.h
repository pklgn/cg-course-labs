#pragma once
#include <vector>
#include "GL/glew.h"
#include "Types/GeometryTypes.h"
#include "OpenGLPrimitive/Primitive.h"
#include "ShaderMVPUniformMap.h"
#include "OpenGLPrimitive/IPrimitiveDrawable.h"
#include "../Model/Rectangle/Rectangle.h"

class Mandelbrot
{
public:
	Mandelbrot(Size windowSize, Size size, Vector3d position, Vector3d angle = { 0.f, 0.f, 0.f });

	void SetWindowSize(int width, int height);
	Size GetWindowSize() const;

	void Draw() const;
	void UpdateMVPMatrices() const;

private:
	struct MandelbrotUniformMap
	{
		MandelbrotUniformMap(const std::string& systemResolution, const std::string& systemTime, const std::string& mouse)
		{
			this->systemResolution = systemResolution;
			this->systemTime = systemTime;
			this->mouse = mouse;
		}

		std::string systemResolution;
		std::string systemTime;
		std::string mouse;
	};

	Size m_windowSize;
	Rectangle m_rectangle;

	glance::ShaderProgram m_shaderProgram;
	glance::ShaderMVPUniformMap m_shaderUniformMap;
	MandelbrotUniformMap m_mandelbrotUniformMap;
};
