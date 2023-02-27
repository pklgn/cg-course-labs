#include "../pch.h"
#include "Circle.h"

void DrawEmptyCircle(CDC& dc, POINT center, UINT radius, COLORREF outlineColor)
{
	int x = 0;
	int y = radius;
	int delta = 1 - 2 * radius;
	int error = 0;
	while (y >= 0)
	{
		dc.SetPixel(center.x + x, center.y + y, outlineColor);
		dc.SetPixel(center.x + x, center.y - y, outlineColor);
		dc.SetPixel(center.x - x, center.y + y, outlineColor);
		dc.SetPixel(center.x - x, center.y - y, outlineColor);
		error = 2 * (delta + y) - 1;
		if ((delta < 0) && (error <= 0))
		{
			delta += 2 * ++x + 1;
			continue;
		}
		error = 2 * (delta - x) - 1;
		if ((delta > 0) && (error > 0))
		{
			delta += 1 - 2 * --y;
			continue;
		}
		x++;
		delta += 2 * (x - y);
		y--;
	}
}

void Circle::Draw(CDC& dc)
{
	// Рисование окружности
	DrawEmptyCircle(dc, m_center, m_radius, m_color);
}
