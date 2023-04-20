#include "GrassView.h"
#include "../../Common/Types/GeometryTypes.h"
#include "../../Common/OpenGLPrimitive/Curves/QuadraticBezier/QuadraticBezier.h"

const RGB DEFAULT_COLOR = { 0.f, 1.f, 0.f };

GrassView::GrassView(Size size, Vector3d position, unsigned int vertices, const std::vector<RGB>& colors, float angle)
	: BaseView(size, position, angle, colors)
	, m_vertices(vertices)
{
	if (colors.size() == 1)
	{
		m_colors.resize(m_vertices, colors.front());
	}
	else
	{
		m_colors.resize(m_vertices, DEFAULT_COLOR);
	}
}

void GrassView::Show(unsigned int program) const
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
	curve.p3.y = -1.f;
	curve.p3.z = butterflyDepth;

	for (int i = 210, j = 0; i > 120 && j < m_vertices; i -= (90 / m_vertices), ++j)
	{
		glLineWidth(2.0f);
		QuadraticBezier quadraticBezier(m_size, m_position, curve, { m_colors[j] }, i);
		quadraticBezier.SetDrawMode(GL_LINE_STRIP);
		quadraticBezier.Draw(program);
		glLineWidth(1.0f);
	}
}


