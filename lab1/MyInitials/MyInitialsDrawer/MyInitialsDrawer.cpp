#include "../pch.h"
#include "MyInitialsDrawer.h"

MyInitialsDrawer::MyInitialsDrawer()
	: m_isFrameFull(false)
	, m_letterDrawer()
	, m_initialShiftY(0)
{
}

MyInitialsDrawer::MyInitialsDrawer(const CRect& frame, LetterDrawer::LineThickness lineThickness)
	: m_frame(frame)
	, m_activeFrame(CPoint{ frame.left, frame.top }, CSize{ frame.Width() / MY_INITIALS_LENGTH - lineThickness / 2, frame.Height() })
	, m_isFrameFull(frame.Width() == 0 || frame.Height() == 0)
	, m_letterDrawer(lineThickness)
	, m_initialShiftY(0)
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

	m_activeFrame.top += m_initialShiftY;
	m_activeFrame.bottom += m_initialShiftY;

	m_letterDrawer.SetColor(color);
	m_letterDrawer.SetFrame(m_activeFrame);

	// FIXED: использовать static_cast либо gsl, либо использовать класс CRect там нужные координаты
	// FIXED: вынести код рисования каждой буквы в отдельный метод
	// FIXED: не использовать Doc/View
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

void MyInitialsDrawer::SetInitialShiftY(int shift)
{
	m_initialShiftY = shift;
}

void MyInitialsDrawer::SetFrame(const CRect& frame)
{
	m_isFrameFull = frame.Width() == 0 || frame.Height() == 0;
	m_frame = frame;
	m_activeFrame = { CPoint{ frame.left, frame.top }, CSize{ frame.Width() / MY_INITIALS_LENGTH - m_lineThickness / 2, frame.Height() } };
}

void MyInitialsDrawer::SetLineThickness(LetterDrawer::LineThickness lineThickness)
{
	m_lineThickness = lineThickness;
	m_letterDrawer.SetLineThickness(lineThickness);
}

int MyInitialsDrawer::GetInitialShiftY() const
{
	return m_initialShiftY;
}
