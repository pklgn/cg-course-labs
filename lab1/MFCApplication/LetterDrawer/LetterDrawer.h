#pragma once

class LetterDrawer
{
public:
	LetterDrawer(CRect frame);

	void DrawELetter(CDC* pDC, COLORREF);
	void DrawPLetter(CDC* pDC, COLORREF);
	void DrawKLetter(CDC* pDC, COLORREF);

private:
	CRect m_frame;
};
