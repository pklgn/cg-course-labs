#pragma once

class LetterDrawer
{
public:
	using LineThickness = int;

	enum class Letter
	{
		E,
		P,
		K,
	};

	LetterDrawer(LineThickness lineThickness = 1);

	void SetFrame(const CRect& frame);
	void SetColor(COLORREF color);
	void SetLineThickness(LineThickness lineThickness);

	void DrawLetter(CDC& pDC, Letter letter);

private:
	void DrawLetterE(CDC& pDC);
	void DrawLetterP(CDC& pDC);
	void DrawLetterK(CDC& pDC);

	CRect m_frame;
	COLORREF m_color;
	LineThickness m_lineThickness;
};
