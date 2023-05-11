#pragma once
#include <memory>
#include <BaseWindow.hpp>
#include "../Cottage/Cottage.h"
#include "OpenGLPrimitive/Skybox.h"

class CottageWindow : public glance::BaseWindow
{
public:
	CottageWindow(int w, int h, const char* title);

private:
	void UpdateVPMatrices(int width, int height);
	void Draw(int width, int height) override;

	std::unique_ptr<Cottage> m_cottagePtr;
	std::unique_ptr<glance::Skybox> m_skyboxPtr;

	glm::mat4 m_view;
	glm::mat4 m_projection;
};
