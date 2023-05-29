#pragma once
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
	unsigned GetWidth() const noexcept;

	// Высота буфера в пикселях
	unsigned GetHeight() const noexcept;

	// Очистка содержимого буфера заданным цветом
	void Clear(boost::uint32_t color = 0);

	// Получение адреса начала соотв. строки пикселей (для чтения)
	const boost::uint32_t* GetPixels(unsigned row = 0) const noexcept;

	// Получение адреса начала соотв. строки пикселей (для записи)
	boost::uint32_t* GetPixels(unsigned row = 0) noexcept;

	// Получение цвета пикселя с заданными координатами
	boost::uint32_t GetPixel(unsigned x, unsigned y) const noexcept;

	// Установка цвета пикселя с заданными координатами
	void SetPixel(unsigned x, unsigned y, boost::uint32_t color) noexcept;

private:
	std::vector<boost::uint32_t> m_pixels;
	unsigned m_width;
	unsigned m_height;
};
