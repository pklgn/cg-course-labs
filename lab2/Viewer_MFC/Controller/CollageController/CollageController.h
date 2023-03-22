#pragma once
class CollageController
{
public:
	void OnPaint(Collage&, CollageView&);
	void OnMouseMove();
	void OnLButtonDown();
	void OnLButtonUp();

private:
	Collage m_collage;
	CollageView m_collageView;
};
