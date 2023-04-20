#include "GrassView.h"
#include "../../Common/Types/GeometryTypes.h"
#include "../../Common/OpenGLPrimitive/Curves/QuadraticBezier/QuadraticBezier.h"
#include "../../Common/OpenGLPrimitive/Shapes/Circle/Circle.h"
#include "../../Common/OpenGLPrimitive/Shapes/Rectangle/Rectangle.h"

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
	float radiusX = m_size.width / m_vertices;
	float offset = static_cast<float>(m_vertices - 1) / 2;
	for (float i = -offset, j = 0; i <= offset; ++i, ++j)
	{
		Circle circle({ radiusX, m_size.height }, { m_position.x + i * radiusX, m_position.y }, { m_colors[j] });
		circle.Draw(program);
	}
	Rectangle grassBase({ m_size.width, radiusX }, { m_position.x, m_position.y - m_size.height / 2 }, { m_colors.front() });
	grassBase.Draw(program);
}
