#include "FlowerView.h"
#include "../../Common/Types/GeometryTypes.h"
#include "../../Common/OpenGLPrimitive/Shapes/Circle/Circle.h"

const RGB DEFAULT_COLOR = { 1.f, 1.f, 1.f };

FlowerView::FlowerView(Size size, Vector3d position, unsigned int vertices, const std::vector<RGB>& colors, float angle)
	: m_size(size)
	, m_position(position)
	, m_angle(angle)
	, m_vertices(vertices)
{
	if (colors.size() == 1)
	{
		m_colors.resize(m_vertices, colors.front());
	}
	else
	{
		m_colors.resize(m_vertices, { 0.f, 1.f, 0.f });
	}
}

void FlowerView::Show(unsigned int program) const
{
	RGB color = DEFAULT_COLOR;
	for (auto angle = 0, j = 0; angle < 180; angle += 180 / m_vertices, ++j)
	{
		color = m_colors[j];
		Circle circle(m_size, m_position, { color, { color.b, color.g, color.r } }, angle);
		circle.Draw(program);
	}
	auto maxDimension = std::max(m_size.width, m_size.height);
	Circle circle({ maxDimension / 2, maxDimension / 2 }, m_position, { DEFAULT_COLOR });
	circle.Draw(program);
}
