#pragma once

class Mouse
{
public:
	Mouse(float x, float y, float sensitivity);

	void MoveMouse(float x, float y);
	void ZoomMouse();
	void UnzoomMouse();
	float GetX();
	float GetY();
	float GetZoomNormalized();

private:
	float m_x;
	float m_y;
	float m_sensitivity;
	float m_zoom;
	float m_zoomNormalized;
};