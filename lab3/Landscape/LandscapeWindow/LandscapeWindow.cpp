#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "LandscapeWindow.h"
#include "../Common/OpenGLPrimitive/Shapes/Circle/Circle.h"
#include "../Common/OpenGLPrimitive/Shapes/Rectangle/Rectangle.h"
#include "../View/ButterflyView/ButterflyView.h"
#include "../View/FlowerView/FlowerView.h"
#include "../View/GrassView/GrassView.h"
#include "../View/CloudView/CloudView.h"

void LandscapeWindow::UpdateUVMatrices(int width, int height)
{
	glm::mat4 view = glm::mat4(1.0f);
	GLint viewLoc = glGetUniformLocation(m_shaderProgram, "u_view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	glm::mat4 projection = glm::ortho(0.0f, float(width), 0.0f, float(height), -1.0f, 100.0f);
	GLint projectionLoc = glGetUniformLocation(m_shaderProgram, "u_projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glViewport(0, 0, width, height);
}

void LandscapeWindow::Draw(int width, int height)
{
	glClear(GL_COLOR_BUFFER_BIT);

	UpdateUVMatrices(width, height);

	// ground
	Rectangle ground({ float(width), float(height) }, { width / 2.f, height / 2.f }, { { 0.f, 0.5f, 0.2f }, { 0.27f, 0.95f, 0.21f } });
	ground.Draw(m_shaderProgram);

	Rectangle sky({ float(width), float(height / 3) }, { width / 2.f, height * 5.f / 6.f }, { { 0.f, 0.5f, 1.f }, { 0.65f, 0.8f, 0.95f }, { 0.36f, 0.61f, 0.88f } });
	sky.Draw(m_shaderProgram);

	CloudView firstCloud({ 100, 100 }, { 100, 470 }, { { 0.8f, 0.8f, 0.8f } });
	firstCloud.Show(m_shaderProgram);

	CloudView secondCloud({ 120, 120 }, { 450, 490 }, { { 0.8f, 0.8f, 0.8f } });
	secondCloud.Show(m_shaderProgram);

	Circle sun({ 120, 120 }, { 300, 500 }, { { 1.f, 1.f, 0.32f } });
	sun.Draw(m_shaderProgram);

	ButterflyView firstButterfly({ 80 * (cosf(glfwGetTime()) + 1.5f) / 2, 80 }, { 100, 100 }, {
																				 { sinf(m_time), 0.95f, 0.7f },
																				 { cosf(m_time), 0.5f, 0.07f },
																				 { 0.5f, sinf(m_time), 0.7f },
																			 },
		50.f);
	firstButterfly.Show(m_shaderProgram);

	ButterflyView secondButterfly({ 70 * (cosf(glfwGetTime()) + 1.5f) / 2, 70 }, { 700, 200 }, {
																							 { 0.95f, sinf(m_time), 0.7f },
																							 { cosf(m_time), 0.5f, 0.07f },
																							 { 0.5f, sinf(m_time), 0.7f },
																						 },
		-45.f);
	secondButterfly.Show(m_shaderProgram);

	ButterflyView thirdButterfly({ 100 * (cosf(glfwGetTime()) + 1.5f) / 2, 100 }, { 500, 300 }, {
																								  { 0.95f, sinf(m_time), 0.0f },
																								  { 0.5f, cosf(m_time), 0.07f },
																								  { 0.95f, sinf(m_time), 0.7f },
																							  },
		10.f);
	thirdButterfly.Show(m_shaderProgram);

	GrassView firstGrass({ 100, 100 }, { 700, 10 }, 8, { {1.f, 0.75f, 0.8f} });
	firstGrass.Show(m_shaderProgram);
	
	GrassView secondGrass({ 100, 100 }, { 600, 10 }, 6, { { 0.1f, 0.75f, 0.05f } });
	secondGrass.Show(m_shaderProgram);

	GrassView thirdGrass({ 100, 100 }, { 500, 10 }, 12, {
															{ 1.f, 1.f, 0.0f },
														});
	thirdGrass.Show(m_shaderProgram);

	FlowerView firstFlower({ 20, 80 }, { 300, 300 }, 6, { { 1.f, 0.f, 0.f } });
	firstFlower.Show(m_shaderProgram);

	FlowerView secondFlower({ 20, 80 }, { 100, 250 }, 6, { { 0.f, 0.f, 1.f } });
	secondFlower.Show(m_shaderProgram);

	FlowerView thirdFlower({ 40, 80 }, { 300, 50 }, 4, { { 0.f, 1.f, 1.f } });
	thirdFlower.Show(m_shaderProgram);

	FlowerView forthFlower({ 60, 120 }, { 400, 200 }, 8, { { 0.f, 0.f, 0.f } });
	forthFlower.Show(m_shaderProgram);
}
