#include "LandscapeWindow.h"
#include "../View/ButterflyView/ButterflyView.h"
#include "../View/CloudView/CloudView.h"
#include "../View/FlowerView/FlowerView.h"
#include "../View/GrassView/GrassView.h"
#include <OpenGLPrimitive/Shapes/Circle/Circle.h>
#include <OpenGLPrimitive/Shapes/Rectangle/Rectangle.h>

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

	Circle sun({ 120, 120 }, { 300, 500 }, { { 1.f, 1.f, 0.32f } });
	sun.Draw(m_shaderProgram);

	CloudView firstCloud({ 100, 100 }, { 100, 470 }, { { 0.8f, 0.8f, 0.8f } });
	firstCloud.Show(m_shaderProgram);

	CloudView secondCloud({ 120, 120 }, { 450, 490 }, { { 0.8f, 0.8f, 0.8f } });
	secondCloud.Show(m_shaderProgram);

	ButterflyView firstButterfly({ 80 * float(cos(glfwGetTime()) + 1.5f) / 2.f, 80 }, { 100, 100 }, {
																				 { float(sin(m_time)), 0.95f, 0.7f },
																				 { float(cos(m_time)), 0.5f, 0.07f },
																				 { 0.5f, float(sin(m_time)), 0.7f },
																			 },
		50.f);
	firstButterfly.Show(m_shaderProgram);

	ButterflyView secondButterfly({ 70 * float(cos(glfwGetTime()) + 1.5f) / 2, 70 }, { 700, 200 }, {
																							 { 0.95f, float(sin(m_time)), 0.7f },
																							 { float(cos(m_time)), 0.5f, 0.07f },
																							 { 0.5f, float(sin(m_time)), 0.7f },
																						 },
		-45.f);
	secondButterfly.Show(m_shaderProgram);

	ButterflyView thirdButterfly({ 100 * float(cos(glfwGetTime()) + 1.5f) / 2, 100 }, { 500, 300 }, {
																								  { 0.95f, float(sin(m_time)), 0.0f },
																								  { 0.5f, float(cos(m_time)), 0.07f },
																								  { 0.95f, float(sin(m_time)), 0.7f },
																							  },
		10.f);
	thirdButterfly.Show(m_shaderProgram);

	GrassView firstGrass({ 200, 100 }, { 700, 60 }, 8, { { 0.26f, 0.6f, 0.3f } });
	firstGrass.Show(m_shaderProgram);
	
	GrassView secondGrass({ 150, 100 }, { 500, 10 }, 6, { { 0.0f, 0.3f, 0.0f } });
	secondGrass.Show(m_shaderProgram);

	GrassView thirdGrass({ 200, 100 }, { 120, 10 }, 12, {
															{ 0.075f, 0.53f, 0.03f },
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
