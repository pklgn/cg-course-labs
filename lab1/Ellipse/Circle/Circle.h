#pragma once
class Circle
{
public:
	constexpr Circle(LONG centerX, LONG centerY, UINT radius, COLORREF color = RGB(0, 0, 0)) noexcept
		: m_center({ centerX, centerY })
		, m_radius(radius)
		, m_color(color)
	{
	}

	void Draw(CDC& dc);

private:
	POINT m_center;
	UINT m_radius;
	COLORREF m_color;
};
