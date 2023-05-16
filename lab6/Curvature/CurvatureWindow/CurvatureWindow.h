#pragma once
#include <memory>
#include <BaseWindow.hpp>
#include "../Curvature/Curvature.h"
#include "OpenGLPrimitive/Skybox.h"
#include "ShaderMVPUniformMap.h"

class CurvatureWindow : public glance::BaseWindow
{
public:
	CurvatureWindow(int w, int h, const char* title);

private:
	void Draw(int width, int height) override;

	Curvature m_curvature;
};
