#define _USE_MATH_DEFINES
#include <cmath>
#include "GraphWindow.h"
#include "../OpenGLPrimitive/Curves/CubicBezier/CubicBezier.h"

void GraphWindow::Draw(int width, int height)
{
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT);

	Curve4d curve;
	curve.p1.x = 0.f;
	curve.p1.y = 0.3f;
	curve.p1.z = 0.f;
	curve.p2.x = 0.125f;
	curve.p2.y = 0.3f;
	curve.p2.z = 0.f;
	curve.p3.x = 0.0725f;
	curve.p3.y = -0.15f;
	curve.p3.z = 0.f;
	curve.p4.x = 0.f;
	curve.p4.y = -0.1f;
	curve.p4.z = 0.f;
	CubicBezier cubicBezier({ 100, 100 }, { 200, 200 }, curve);
	cubicBezier.Draw();
}
