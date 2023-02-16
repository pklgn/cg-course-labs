#pragma once

template <typename T>
struct Rect
{
	T left;
	T top;
	T width;
	T height;

	bool operator==(const Rect& rhs)
	{
		return left == rhs.left && top == rhs.top && width == rhs.width && height == rhs.height;
	}
};

typedef Rect<double> RectD;