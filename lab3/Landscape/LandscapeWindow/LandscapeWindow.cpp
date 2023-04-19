#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "LandscapeWindow.h"
#include "../Common/OpenGLPrimitive/Shapes/Circle/Circle.h"
#include "../Common/OpenGLPrimitive/Shapes/Rectangle/Rectangle.h"
#include "../Common/Types/DimensionTypes.h"
#include "../Common/Types/GeometryTypes.h"
#include "../Common/OpenGLLog/OpenGLLog.h"
#include "../Common/OpenGLPrimitive/Curves/CubicBezier/CubicBezier.h"
#include "../Common/OpenGLPrimitive/Curves/QuadraticBezier/QuadraticBezier.h"
#include "../View/ButterflyView/ButterflyView.h"

void LandscapeWindow::Draw(int width, int height)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glm::mat4 view = glm::mat4(1.0f);
	GLint viewLoc = glGetUniformLocation(m_shaderProgram, "u_view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	glm::mat4 projection = glm::ortho(0.0f, float(width), 0.0f, float(height), - 1.0f, 100.0f);
	GLint projectionLoc = glGetUniformLocation(m_shaderProgram, "u_projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glViewport(0, 0, width, height);

	auto time = glfwGetTime();
	ButterflyView butt({ 100 * (cosf(time) + 1.5f) / 2, 100 }, { 100, 100 }, {
																				 { sinf(time), 0.5f, 0.7f },
																				 { cosf(time), 0.5f, 0.7f },
																				 { 0.5f, sinf(time), 0.7f },
																			 },
		50.f);
	butt.Show(m_shaderProgram);

	//Circle circle({ 40 * (cosf(glfwGetTime()) + 1.5f) / 10, 40 }, { 200, 200 }, { { 0.7f, 0.4f, 0.3f } });
	//circle.Draw(m_shaderProgram);

	//Rectangle rectangle({ 50, 80 }, { 500, 500 }, { { 0.5f, 1.f, 0.3f } }, 50.f);
	//rectangle.Draw(m_shaderProgram);
}
