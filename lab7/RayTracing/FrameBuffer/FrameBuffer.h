﻿#pragma once
#include <boost/cstdint.hpp>
#include <cassert>
#include <vector>

/*
	Класс CFrameBuffer, представляющий из себя 32-битный буфер кадра
	фиксированного размера
*/

class FrameBuffer
{
public:
	FrameBuffer(unsigned width, unsigned height);

	// Ширина буфера в пикселях
	unsigned GetWidth() const noexcept
	{
		return m_width;
	}

	// Высота буфера в пикселях
	unsigned GetHeight() const noexcept
	{
		return m_height;
	}

	// Очистка содержимого буфера заданным цветом
	void Clear(boost::uint32_t color = 0);

	// Получение адреса начала соотв. строки пикселей (для чтения)
	const boost::uint32_t* GetPixels(unsigned row = 0) const noexcept
	{
		assert(row < m_height);
		return &m_pixels[size_t(row * m_width)];
	}

	// Получение адреса начала соотв. строки пикселей (для записи)
	boost::uint32_t* GetPixels(unsigned row = 0) noexcept
	{
		assert(row < m_height);
		return &m_pixels[size_t(row * m_width)];
	}

	// Получение цвета пикселя с заданными координатами
	boost::uint32_t GetPixel(unsigned x, unsigned y) const noexcept
	{
		assert(x < m_width);
		assert(y < m_height);
		return m_pixels[size_t(y * m_width + x)];
	}

	// Установка цвета пикселя с заданными координатами
	void SetPixel(unsigned x, unsigned y, boost::uint32_t color) noexcept
	{
		assert(x < m_width);
		assert(y < m_height);
		m_pixels[size_t(y * m_width + x)] = color;
	}

private:
	std::vector<boost::uint32_t> m_pixels;
	unsigned m_width;
	unsigned m_height;
};
