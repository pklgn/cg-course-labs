#pragma once
#include <vector>
#include "GL/glew.h"
#include "Types/GeometryTypes.h"
#include "OpenGLPrimitive/Primitive.h"
#include "ShaderMVPUniformMap.h"
#include "OpenGLPrimitive/IPrimitiveDrawable.h"
#include "../Model/Rectangle/Rectangle.h"
#include "Texture.h"

class Mandelbrot
{
public:
	Mandelbrot(Size windowSize, Size size, Vector3d position, Vector3d angle = { 0.f, 0.f, 0.f });

	void SetWindowSize(int width, int height);
	Size GetWindowSize() const;

	void SetMousePosition(const Vector3d& offset);
	Vector3d GetMousePosition() const;

	void Draw() const;
	void UpdateMVPMatrices() const;

private:
	struct MandelbrotUniformMap
	{
		MandelbrotUniformMap(const std::string& systemResolution, const std::string& systemTime, const std::string& mouse, const std::string& texture)
		{
			this->systemResolution = systemResolution;
			this->systemTime = systemTime;
			this->mouse = mouse;
			this->texture = texture;
		}

		std::string systemResolution;
		std::string systemTime;
		std::string mouse;
		std::string texture;
	};

	Size m_windowSize;
	Vector3d m_mousePosition;
	Rectangle m_rectangle;

	glance::ShaderProgram m_shaderProgram;
	glance::ShaderMVPUniformMap m_shaderUniformMap;
	MandelbrotUniformMap m_mandelbrotUniformMap;

	glance::Texture m_texture;
};
