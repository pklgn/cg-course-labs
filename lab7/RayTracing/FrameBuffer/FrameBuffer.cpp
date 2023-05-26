#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(unsigned width, unsigned height)
	: m_pixels(width * height)
	, m_width(width)
	, m_height(height)
{
}

void FrameBuffer::Clear(boost::uint32_t color)
{
	std::fill(m_pixels.begin(), m_pixels.end(), color);
}
