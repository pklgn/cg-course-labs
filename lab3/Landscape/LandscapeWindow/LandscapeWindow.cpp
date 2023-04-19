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
	glm::mat4 view = glm::mat4(1.0f);
	GLint viewLoc = glGetUniformLocation(m_shaderProgram, "u_view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	glm::mat4 projection = glm::ortho(0.0f, float(width), 0.0f, float(height), - 1.0f, 100.0f);
	GLint projectionLoc = glGetUniformLocation(m_shaderProgram, "u_projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glViewport(0, 0, width, height);

	ButterflyView butt({ 50, 50 }, { 100, 100 });
	butt.Show(m_shaderProgram);
}
