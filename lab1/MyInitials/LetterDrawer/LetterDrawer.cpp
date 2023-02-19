#include "../pch.h"
#include "LetterDrawer.h"

LetterDrawer::LetterDrawer(LineThickness lineThickness)
	: m_lineThickness(lineThickness)
	, m_color(RGB(0, 0, 0))
{
}

void LetterDrawer::SetFrame(const CRect& frame)
{
	m_frame = frame;
}

void LetterDrawer::SetColor(COLORREF color)
{
	m_color = color;
}

void LetterDrawer::SetLineThickness(LineThickness lineThickness)
{
	m_lineThickness = lineThickness;
}

void LetterDrawer::DrawLetter(CDC& pDC, Letter letter)
{
	switch (letter)
	{
	case LetterDrawer::Letter::E:
		DrawLetterE(pDC);
		break;
	case LetterDrawer::Letter::P:
		DrawLetterP(pDC);
		break;
	case LetterDrawer::Letter::K:
		DrawLetterK(pDC);
		break;
	default:
		break;
	}
}

void LetterDrawer::DrawLetterE(CDC& pDC)
{
	pDC.Rectangle(m_frame.left,
		m_frame.top,
		m_frame.left + m_lineThickness,
		m_frame.top + m_frame.Height());

	pDC.Rectangle(m_frame.left,
		m_frame.top,
		m_frame.left + m_frame.Width(),
		m_frame.top + m_lineThickness);

	pDC.Rectangle(m_frame.left,
		m_frame.top + m_frame.Height() / 2 - m_lineThickness / 2,
		m_frame.left + m_frame.Width(),
		m_frame.top + m_frame.Height() / 2 + m_lineThickness / 2);

	pDC.Rectangle(m_frame.left,
		m_frame.top + m_frame.Height() - m_lineThickness,
		m_frame.left + m_frame.Width(),
		m_frame.top + m_frame.Height());
}

void LetterDrawer::DrawLetterP(CDC& pDC)
{
	pDC.Rectangle(m_frame.left,
		m_frame.top,
		m_frame.left + m_lineThickness,
		m_frame.top + m_frame.Height());

	pDC.Rectangle(m_frame.left,
		m_frame.top,
		m_frame.left + m_frame.Width(),
		m_frame.top + m_lineThickness);

	pDC.Rectangle(m_frame.left + m_frame.Width() - m_lineThickness,
		m_frame.top,
		m_frame.left + m_frame.Width(),
		m_frame.top + m_frame.Height());
}

void LetterDrawer::DrawLetterK(CDC& pDC)
{
	pDC.Rectangle(m_frame.left,
		m_frame.top,
		m_frame.left + m_lineThickness,
		m_frame.top + m_frame.Height());

	const CPoint upperPoints[] = { CPoint{ m_frame.left, m_frame.top + m_frame.Height() / 2 },
		CPoint{ m_frame.left + m_frame.Width() - m_lineThickness, m_frame.top },
		CPoint{ m_frame.left + m_frame.Width(), m_frame.top },
		CPoint{ m_frame.left + m_lineThickness, m_frame.top + m_frame.Height() / 2 } };
	pDC.Polygon(upperPoints, 4);

	const CPoint lowerPoints[] = { CPoint{ m_frame.left, m_frame.top + m_frame.Height() / 2 },
		CPoint{ m_frame.left + m_frame.Width() - m_lineThickness, m_frame.top + m_frame.Height() },
		CPoint{ m_frame.left + m_frame.Width(), m_frame.top + m_frame.Height() },
		CPoint{ m_frame.left + m_lineThickness, m_frame.top + m_frame.Height() / 2 } };
	pDC.Polygon(lowerPoints, 4);
}
