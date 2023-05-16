#pragma once
#include <vector>
#include "GL/glew.h"
#include "Types/GeometryTypes.h"
#include "OpenGLPrimitive/Primitive.h"
#include "ShaderMVPUniformMap.h"
#include "OpenGLPrimitive/IPrimitiveDrawable.h"
#include "../Model/Line/Line.h"

class Curvature
{
public:
	Curvature(Size windowSize, Size size, Vector3d position, Vector3d angle = { 0.f, 0.f, 0.f });

	void SetWindowSize(int width, int height);
	Size GetWindowSize() const;

	void Draw() const;
	void UpdateMVPMatrices() const;

private:
	Size m_windowSize;
	Line m_line;

	glance::ShaderProgram m_shaderProgram;
	glance::ShaderMVPUniformMap m_shaderUniformMap;
};
