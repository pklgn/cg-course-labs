#include "BaseView.h"

BaseView::BaseView(Size size, Vector3d position, float angle, const std::vector<RGB> colors)
	: m_size(size)
	, m_position(position)
	, m_angle(angle)
{
}
