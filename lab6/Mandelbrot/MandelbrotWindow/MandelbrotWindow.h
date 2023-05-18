#pragma once
#include <memory>
#include <BaseWindow.hpp>
#include "../Mandelbrot/Mandelbrot.h"
#include "OpenGLPrimitive/Skybox.h"
#include "ShaderMVPUniformMap.h"
#include "../Mouse/Mouse.h"

class MandelbrotWindow : public glance::BaseWindow
{
public:
	MandelbrotWindow(int w, int h, const char* title);

private:
	void Draw(int width, int height) override;

	Mandelbrot m_mandelbrot;

	Mouse m_mouse;

};
