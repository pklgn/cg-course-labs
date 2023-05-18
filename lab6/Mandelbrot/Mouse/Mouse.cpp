#include "Mouse.h"
#include "math.h"

Mouse::Mouse(float x, float y, float sensitivity)
{
	m_x = x;
	m_y = y;
	m_sensitivity = sensitivity;
	m_zoom = 1.0;
	m_zoomNormalized = 1.0;
}

void Mouse::MoveMouse(float x, float y)
{
	m_x += x * m_sensitivity * m_zoomNormalized; // Move less the more zoom we have
	m_y += y * m_sensitivity * m_zoomNormalized;
}

void Mouse::ZoomMouse()
{
	m_zoom += 0.1 * 1 / m_zoomNormalized;
	m_zoomNormalized = 1.0 / m_zoom;
}

void Mouse::UnzoomMouse()
{
	if (m_zoom - 0.1 < 1.0)
	{
		return;
	}
	m_zoom -= 0.1 * 1 / m_zoomNormalized;
	m_zoomNormalized = 1.0 / m_zoom;
}

float Mouse::GetX()
{
	return m_x;
}

float Mouse::GetY()
{
	return m_y;
}

float Mouse::GetZoomNormalized()
{
	return m_zoomNormalized;
}