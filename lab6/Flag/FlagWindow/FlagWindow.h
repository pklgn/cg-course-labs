#pragma once
#include <memory>
#include <BaseWindow.hpp>
#include "../Flag/Flag.h"
#include "OpenGLPrimitive/Skybox.h"
#include "ShaderMVPUniformMap.h"

class FlagWindow : public glance::BaseWindow
{
public:
	FlagWindow(int w, int h, const char* title);

private:
	void Draw(int width, int height) override;

	Flag m_flag;
};
