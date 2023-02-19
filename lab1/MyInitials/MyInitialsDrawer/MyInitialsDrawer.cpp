#include "../pch.h"
#include "MyInitialsDrawer.h"

MyInitialsDrawer::MyInitialsDrawer(const CRect& frame, LetterDrawer::LineThickness lineThickness)
	: m_frame(frame)
	, m_activeFrame(CPoint{ frame.left, frame.top }, CSize{ frame.Width() / MY_INITIALS_LENGTH - lineThickness / 2, frame.Height() })
	, m_isFrameFull(frame.Width() == 0 || frame.Height() == 0)
	, m_letterDrawer(lineThickness)
{
}

void MyInitialsDrawer::DrawInitial(CDC& pDC, LetterDrawer::Letter initial, COLORREF color)
{
	if (m_isFrameFull)
	{
		return;
	}

	CPen pen(PS_SOLID, 2, color);
	CBrush brush(color);

	CPen* pOldPen = pDC.SelectObject(&pen);
	CBrush* pOldBrush = pDC.SelectObject(&brush);

	m_letterDrawer.SetColor(color);
	m_letterDrawer.SetFrame(m_activeFrame);

	// TODO: использовать static_cast либо gsl, либо использовать класс CRect там нужные координаты
	// TODO: вынести код рисования каждой буквы в отдельный метод
	// TODO: не использовать Doc/View
	switch (initial)
	{
	case LetterDrawer::Letter::E:
	case LetterDrawer::Letter::P:
	case LetterDrawer::Letter::K: {
		m_letterDrawer.DrawLetter(pDC, initial);
		break;
	}
	default:
		throw std::invalid_argument("Non-existent initial was given");
		break;
	}

	pDC.SelectObject(pOldPen);
	pDC.SelectObject(pOldBrush);

	m_activeFrame.left += m_frame.Width() / MY_INITIALS_LENGTH;
	m_activeFrame.right += m_frame.Width() / MY_INITIALS_LENGTH;

	if (m_activeFrame.left == m_frame.right)
	{
		m_isFrameFull = true;
	}
}
