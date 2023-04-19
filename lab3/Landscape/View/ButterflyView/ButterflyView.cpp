#include "ButterflyView.h"
#include "../../Common/OpenGLPrimitive/Curves/QuadraticBezier/QuadraticBezier.h"
#include "../../Common/OpenGLPrimitive/Curves/CubicBezier/CubicBezier.h"
#include "../../Common/Types/GeometryTypes.h"
#include "../../Common/OpenGLPrimitive/Shapes/Circle/Circle.h"

ButterflyView::ButterflyView(
	Size size, Vector3d position, const std::vector<RGB>& colors, float angle)
	: m_size(size)
	, m_position(position)
	, m_angle(angle)
{
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

	CubicBezier cubicBezierTop(m_size, m_position, curve, { {} }, m_angle);
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

	CubicBezier cubicBezierBottom(m_size, m_position, curve, {}, m_angle);
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

	QuadraticBezier quadraticBezier(m_size, m_position, curve, {}, m_angle);
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

	CubicBezier cubicBezierTop(m_size, m_position, curve, {}, m_angle);
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

	CubicBezier cubicBezierBottom(m_size, m_position, curve, {}, m_angle);
	cubicBezierBottom.Draw(program);
}

void DrawButterflyWingCircle(unsigned int program, float radius, float tranX, float transY, float angle)
{
	Circle circle({ radius, radius }, { tranX, transY, 0.f }, {}, angle);
	circle.Draw(program);
}

void ButterflyView::DrawButterflyWing(unsigned int program) const
{
	DrawBufferflyWingPart(program);
	DrawBufferflyWingPart(program);
	DrawButterflyWingCircle(program, 0.13, 0.48, 0.28, m_angle);
	DrawButterflyWingCircle(program, 0.14, 0.25, -0.4, m_angle);
}

void ButterflyView::Show(unsigned int program) const
{
	DrawButterflyBody(program);
	DrawButterflyAntena(program);
	DrawButterflyWing(program);
	m_size = {
		-m_size.width,
		m_size.height
	};
	DrawButterflyBody(program);
	DrawButterflyAntena(program);
	DrawButterflyWing(program);
}