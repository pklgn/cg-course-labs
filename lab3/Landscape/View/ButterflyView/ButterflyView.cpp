#include "ButterflyView.h"
#include <GeometryTypes.h>
#include <OpenGLPrimitive/Curves/CubicBezier/CubicBezier.h>
#include <OpenGLPrimitive/Curves/QuadraticBezier/QuadraticBezier.h>
#include <stdexcept>

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

	curve.p1.x = 0.f;
	curve.p1.y = 0.2f;
	curve.p1.z = butterflyDepth;
	curve.p2.x = 0.1f;
	curve.p2.y = -0.3f;
	curve.p2.z = butterflyDepth;
	curve.p3.x = 0.025f;
	curve.p3.y = -0.55f;
	curve.p3.z = butterflyDepth;
	curve.p4.x = 0.f;
	curve.p4.y = -0.5f;
	curve.p4.z = butterflyDepth;

	CubicBezier cubicBezierBottom(m_size, m_position, curve, { m_colors[0] }, m_angle);
	cubicBezierBottom.Draw(program);
}

void ButterflyView::DrawButterflyAntena(unsigned int program) const
{
	float butterflyDepth = 0;
	Curve4d curve;
	curve.p1.x = 0.01f;
	curve.p1.y = 0.3f;
	curve.p1.z = butterflyDepth;
	curve.p2.x = 0.02f;
	curve.p2.y = 0.5f;
	curve.p2.z = butterflyDepth;
	curve.p3.x = 0.2f;
	curve.p3.y = 0.7f;
	curve.p3.z = butterflyDepth;

	QuadraticBezier quadraticBezier(m_size, m_position, curve, { m_colors[1] }, m_angle);
	quadraticBezier.Draw(program);
}

void ButterflyView::DrawBufferflyWingPart(unsigned int program) const
{
	float butterflyDepth = 0;
	Curve4d curve;
	// Top Wing
	curve.p1.x = 0.f;
	curve.p1.y = 0.2f;
	curve.p1.z = butterflyDepth;
	curve.p2.x = 0.8f;
	curve.p2.y = 0.9f;
	curve.p2.z = butterflyDepth;
	curve.p3.x = 1.5f;
	curve.p3.y = 0.0f;
	curve.p3.z = butterflyDepth;
	curve.p4.x = 0.f;
	curve.p4.y = -0.4f;
	curve.p4.z = butterflyDepth;

	CubicBezier cubicBezierTop(m_size, m_position, curve, { m_colors[2] }, m_angle);
	cubicBezierTop.Draw(program);

	// Bottom Wing
	curve.p1.x = 0.f;
	curve.p1.y = 0.f;
	curve.p1.z = butterflyDepth;
	curve.p2.x = 1.0f;
	curve.p2.y = -0.4f;
	curve.p2.z = butterflyDepth;
	curve.p3.x = 0.2f;
	curve.p3.y = -1.4f;
	curve.p3.z = butterflyDepth;
	curve.p4.x = 0.f;
	curve.p4.y = -0.4f;
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