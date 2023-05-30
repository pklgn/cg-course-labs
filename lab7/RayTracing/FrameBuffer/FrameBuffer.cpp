#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(unsigned width, unsigned height)
	: m_pixels(width * height)
	, m_width(width)
	, m_height(height)
{
}

unsigned FrameBuffer::GetWidth() const noexcept
{
	return m_width;
}

unsigned FrameBuffer::GetHeight() const noexcept
{
	return m_height;
}

void FrameBuffer::Clear(std::uint32_t color)
{
	std::fill(m_pixels.begin(), m_pixels.end(), color);
}

const std::uint32_t* FrameBuffer::GetPixels(unsigned row) const noexcept
{
	assert(row < m_height);
	return &m_pixels[size_t(row * m_width)];
}

std::uint32_t* FrameBuffer::GetPixels(unsigned row) noexcept
{
	assert(row < m_height);
	return &m_pixels[size_t(row * m_width)];
}

std::uint32_t FrameBuffer::GetPixel(unsigned x, unsigned y) const noexcept
{
	assert(x < m_width);
	assert(y < m_height);
	return m_pixels[size_t(y * m_width + x)];
}

void FrameBuffer::SetPixel(unsigned x, unsigned y, std::uint32_t color) noexcept
{
	assert(x < m_width);
	assert(y < m_height);
	m_pixels[size_t(y * m_width + x)] = color;
}
