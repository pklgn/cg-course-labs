#include <stdexcept>
#include "ButterflyView.h"
#include "../../Common/OpenGLPrimitive/Curves/QuadraticBezier/QuadraticBezier.h"
#include "../../Common/OpenGLPrimitive/Curves/CubicBezier/CubicBezier.h"
#include "../../Common/Types/GeometryTypes.h"
#include "../../Common/OpenGLPrimitive/Shapes/Circle/Circle.h"

constexpr int BUTTERFLY_PARTS_NUMBER = 3;

ButterflyView::ButterflyView(
	Size size, Vector3d position, const std::vector<RGB>& colors, float angle)
	: BaseView(size, position, angle, colors)
{
	if (colors.size() < BUTTERFLY_PARTS_NUMBER)
	{
		auto msg = "Invalid number of butterfly parts was found. It should be at least " + BUTTERFLY_PARTS_NUMBER;
		throw std::invalid_argument(msg);
	}

	m_colors = colors;
}

void ButterflyView::DrawButterflyBody(unsigned int program) const
{
	float butterflyDepth = 0;
	Curve4d curve;
	curve.p1.x = 0.f;
	curve.p1.y = 0.3f;
	curve.p1.z = butterflyDepth;
	curve.p2.x = 0.125f;
	curve.p2.y = 0.3f;
	curve.p2.z = butterflyDepth;
	curve.p3.x = 0.0725f;
	curve.p3.y = -0.15f;
	curve.p3.z = butterflyDepth;
	curve.p4.x = 0.f;
	curve.p4.y = -0.1f;
	curve.p4.z = butterflyDepth;

	CubicBezier cubicBezierTop(m_size, m_position, curve, { m_colors[0] }, m_angle);
	cubicBezierTop.Draw(program);

	curve.p1.x = 0;
	curve.p1.y = 0.2;
	curve.p1.z = butterflyDepth;
	curve.p2.x = 0.1;
	curve.p2.y = -0.3;
	curve.p2.z = butterflyDepth;
	curve.p3.x = 0.025;
	curve.p3.y = -0.55;
	curve.p3.z = butterflyDepth;
	curve.p4.x = 0;
	curve.p4.y = -0.5;
	curve.p4.z = butterflyDepth;

	CubicBezier cubicBezierBottom(m_size, m_position, curve, { m_colors[0] }, m_angle);
	cubicBezierBottom.Draw(program);
}

void ButterflyView::DrawButterflyAntena(unsigned int program) const
{
	float butterflyDepth = 0;
	Curve4d curve;
	curve.p1.x = 0.01;
	curve.p1.y = 0.3;
	curve.p1.z = butterflyDepth;
	curve.p2.x = 0.02;
	curve.p2.y = 0.5;
	curve.p2.z = butterflyDepth;
	curve.p3.x = 0.2;
	curve.p3.y = 0.7;
	curve.p3.z = butterflyDepth;

	QuadraticBezier quadraticBezier(m_size, m_position, curve, { m_colors[1] }, m_angle);
	quadraticBezier.Draw(program);
}

void ButterflyView::DrawBufferflyWingPart(unsigned int program) const
{
	float butterflyDepth = 0;
	Curve4d curve;
	// Top Wing
	curve.p1.x = 0;
	curve.p1.y = 0.2;
	curve.p1.z = butterflyDepth;
	curve.p2.x = 0.8;
	curve.p2.y = 0.9;
	curve.p2.z = butterflyDepth;
	curve.p3.x = 1.5;
	curve.p3.y = 0.0;
	curve.p3.z = butterflyDepth;
	curve.p4.x = 0;
	curve.p4.y = -0.4;
	curve.p4.z = butterflyDepth;

	CubicBezier cubicBezierTop(m_size, m_position, curve, { m_colors[2] }, m_angle);
	cubicBezierTop.Draw(program);

	// Bottom Wing
	curve.p1.x = 0;
	curve.p1.y = 0;
	curve.p1.z = butterflyDepth;
	curve.p2.x = 1.0;
	curve.p2.y = -0.4;
	curve.p2.z = butterflyDepth;
	curve.p3.x = 0.2;
	curve.p3.y = -1.4;
	curve.p3.z = butterflyDepth;
	curve.p4.x = 0;
	curve.p4.y = -0.4;
	curve.p4.z = butterflyDepth;

	CubicBezier cubicBezierBottom(m_size, m_position, curve, { m_colors[2] }, m_angle);
	cubicBezierBottom.Draw(program);
}

void ButterflyView::DrawButterflyWing(unsigned int program) const
{
	DrawBufferflyWingPart(program);
	DrawBufferflyWingPart(program);
}

void ButterflyView::Show(unsigned int program) const
{
	
	DrawButterflyAntena(program);
	DrawButterflyWing(program);
	DrawButterflyBody(program);
	m_size = {
		-m_size.width,
		m_size.height
	};
	DrawButterflyBody(program);
	DrawButterflyAntena(program);
	DrawButterflyWing(program);
}