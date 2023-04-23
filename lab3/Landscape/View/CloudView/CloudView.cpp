#include "CloudView.h"
#include <OpenGLPrimitive/Shapes/Circle/Circle.h>

constexpr int CLOUDS_NUMBER = 4;
const RGB DEFAULT_COLOR = { 0.75f, 0.75f, 0.75f };

CloudView::CloudView(Size size, Vector3d position, const std::vector<RGB>& colors, float angle)
	: BaseView(size, position, angle, colors)
{
	if (colors.size() == 1)
	{
		m_colors.resize(CLOUDS_NUMBER, colors.front());
	}
	else
	{
		m_colors.resize(CLOUDS_NUMBER, DEFAULT_COLOR);
	}
}

void CloudView::Show(unsigned int program) const
{
	Circle circle({ m_size.width / 1.5f, m_size.height / 1.5f }, { m_position.x + m_size.width / 3, m_position.y + m_size.height / 3 }, { m_colors.back(), { 0.f, 0.f, 1.f } });
	circle.Draw(program);

	for (int i = 0; i < CLOUDS_NUMBER - 1; ++i)
	{
		Circle circle({ m_size.width / 2, m_size.height / 2 }, { m_position.x + m_size.width / 4 * i, m_position.y }, { m_colors[i], { 0.f, 0.f, 1.f } });
		circle.Draw(program);
	}
}
