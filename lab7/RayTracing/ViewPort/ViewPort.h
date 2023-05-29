﻿#pragma once

class CViewPort
{
public:
	/*
	Инициализация видового порта нулевых размеров в координатами верхнего левого угла (0, 0)
	*/
	CViewPort() throw();

	/*
	Инициализация видового порта с заданными размерами и положением
	*/
	CViewPort(unsigned left, unsigned top, unsigned width, unsigned height) throw();

	// Проверяем, находится ли точка внутри видового порта
	bool TestPoint(int x, int y)const throw()
	{
		unsigned ux = x;
		unsigned uy = y;

		return
			(ux >= m_left && ux < GetRight()) &&
			(uy >= m_top && uy < GetBottom());

	}

	unsigned GetLeft()const throw()
	{
		return m_left;
	}

	unsigned GetTop()const throw()
	{
		return m_top;
	}

	unsigned GetBottom()const throw()
	{
		return m_top + m_height;
	}

	unsigned GetRight()const throw()
	{
		return m_left + m_width;
	}

	unsigned GetWidth()const throw()
	{
		return m_width;
	}

	unsigned GetHeight()const throw()
	{
		return m_height;
	}

private:
	unsigned m_left;
	unsigned m_top;
	unsigned m_width;
	unsigned m_height;
};
