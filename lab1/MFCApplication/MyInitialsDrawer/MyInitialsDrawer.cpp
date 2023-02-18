#include "../pch.h"
#include "MyInitialsDrawer.h"

MyInitialsDrawer::MyInitialsDrawer(const CRect& frame, size_t lineThickness)
	: m_frame(frame)
	, m_activeFrame({ frame.left, frame.top, frame.Width() / MY_INITIALS_SIZE - lineThickness / 2, frame.Height() })
	, m_isFrameFull(frame.Width() == 0 || frame.Height() == 0)
	, m_lineThickness(lineThickness)
{
}

void MyInitialsDrawer::DrawInitial(CDC* pDC, MyInitials initial, COLORREF color)
{
	if (m_isFrameFull)
	{
		return;
	}

	CPen pen(PS_SOLID, 2, color);
	CBrush brush(color);

	CPen* pOldPen = pDC->SelectObject(&pen);
	CBrush* pOldBrush = pDC->SelectObject(&brush);

	// TODO: использовать static_cast либо gsl, либо использовать класс CRect там нужные координаты
	// TODO: вынести код рисования каждой буквы в отдельный метод
	// TODO: не использовать Doc/View
	switch (initial)
	{
	case MyInitials::E:
		pDC->Rectangle((int)m_activeFrame.left,
			(int)m_activeFrame.top,
			(int)(m_activeFrame.left + m_lineThickness),
			(int)(m_activeFrame.top + m_activeFrame.Height()));

		pDC->Rectangle((int)m_activeFrame.left,
			(int)m_activeFrame.top,
			(int)(m_activeFrame.left + m_activeFrame.Width()),
			(int)(m_activeFrame.top + m_lineThickness));

		pDC->Rectangle((int)m_activeFrame.left,
			(int)(m_activeFrame.top + m_activeFrame.Height() / 2 - m_lineThickness / 2),
			(int)(m_activeFrame.left + m_activeFrame.Width()),
			(int)(m_activeFrame.top + m_activeFrame.Height() / 2 + m_lineThickness / 2));

		pDC->Rectangle((int)m_activeFrame.left,
			(int)(m_activeFrame.top + m_activeFrame.Height() - m_lineThickness),
			(int)(m_activeFrame.left + m_activeFrame.Width()),
			(int)(m_activeFrame.top + m_activeFrame.Height()));
		break;
	case MyInitials::P:
		pDC->Rectangle((int)m_activeFrame.left,
			(int)m_activeFrame.top,
			(int)(m_activeFrame.left + m_lineThickness),
			(int)(m_activeFrame.top + m_activeFrame.Height()));

		pDC->Rectangle((int)m_activeFrame.left,
			(int)m_activeFrame.top,
			(int)(m_activeFrame.left + +m_activeFrame.Width()),
			(int)(m_activeFrame.top + m_lineThickness));

		pDC->Rectangle((int)(m_activeFrame.left + m_activeFrame.Width() - m_lineThickness),
			(int)m_activeFrame.top,
			(int)(m_activeFrame.left + +m_activeFrame.Width()),
			(int)(m_activeFrame.top + m_activeFrame.Height()));
		break;
	case MyInitials::K: {
		pDC->Rectangle((int)m_activeFrame.left,
			(int)m_activeFrame.top,
			(int)(m_activeFrame.left + m_lineThickness),
			(int)(m_activeFrame.top + m_activeFrame.Height()));

		const POINT upperPoints[] = { POINT{ (long)m_activeFrame.left, (long)(m_activeFrame.top + m_activeFrame.Height() / 2) },
			POINT{ (long)(m_activeFrame.left + m_activeFrame.Width() - m_lineThickness), (long)m_activeFrame.top },
			POINT{ (long)(m_activeFrame.left + m_activeFrame.Width()), (long)m_activeFrame.top },
			POINT{ (long)(m_activeFrame.left + m_lineThickness), (long)(m_activeFrame.top + m_activeFrame.Height() / 2) } };
		pDC->Polygon(upperPoints, 4);

		const POINT lowerPoints[] = { POINT{ (long)m_activeFrame.left, (long)(m_activeFrame.top + m_activeFrame.Height() / 2) },
			POINT{ (long)(m_activeFrame.left + m_activeFrame.Width() - m_lineThickness), (long)(m_activeFrame.top + m_activeFrame.Height()) },
			POINT{ (long)(m_activeFrame.left + m_activeFrame.Width()), (long)(m_activeFrame.top + m_activeFrame.Height()) },
			POINT{ (long)(m_activeFrame.left + m_lineThickness), (long)(m_activeFrame.top + m_activeFrame.Height() / 2) } };
		pDC->Polygon(lowerPoints, 4);

		break;
	}
	default:
		throw std::invalid_argument("Unknown initial was given");
		break;
	}

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);

	m_activeFrame.left += m_frame.Width() / MY_INITIALS_SIZE;
}
