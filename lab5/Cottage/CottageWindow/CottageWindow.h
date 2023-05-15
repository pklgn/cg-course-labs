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

	Cottage m_cottage;
	
	std::unique_ptr<glance::Skybox> m_skyboxPtr;
	glance::ShaderProgram m_skyboxShaderProgram;
	glance::ShaderMVPUniformMap m_skyboxShaderUniformMap;


	// TODO: должны ли здесь храниться матрицы преобразования
	glm::mat4 m_view;
	glm::mat4 m_projection;

	bool m_activeMouse = false;
};
