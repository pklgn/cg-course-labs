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

	ButterflyView butterfly({ 80 * (cosf(glfwGetTime()) + 1.5f) / 2, 80 }, { 100, 100 }, {
																				 { sinf(m_time), 0.95f, 0.7f },
																				 { cosf(m_time), 0.5f, 0.07f },
																				 { 0.5f, sinf(m_time), 0.7f },
																			 },
		50.f);
	butterfly.Show(m_shaderProgram);

	FlowerView flowerView({ 20, 80 }, { 300, 300 }, 6, { {1.f, 0.f, 0.f} });
	flowerView.Show(m_shaderProgram);

	GrassView grassView({ 100, 100 }, { 200, 200 }, 8, { {0.f, 1.f, 0.f} });
	grassView.Show(m_shaderProgram);

	CloudView cloudView({ 100, 100 }, { 400, 400 }, { { 0.8f, 0.8f, 0.8f } });
	cloudView.Show(m_shaderProgram);
}
