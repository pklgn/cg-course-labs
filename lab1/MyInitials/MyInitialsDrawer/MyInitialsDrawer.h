#pragma once
#include <afxwin.h>
#include "../LetterDrawer/LetterDrawer.h"

class MyInitialsDrawer
{
public:
	const static int MY_INITIALS_LENGTH = 3;
	// TODO: не использовать size_t для толщины линии, используется для задания размеров индексов в памяти для обычных величин int
	MyInitialsDrawer(const CRect&, LetterDrawer::LineThickness lineThickness);
	
	// TODO: если не ожидается нулевой указатель, то следует использовать ссылку, добавить названия параметрам
	void DrawInitial(CDC&, LetterDrawer::Letter, COLORREF);

private:
	bool m_isFrameFull;
	CRect m_frame;
	CRect m_activeFrame;
	LetterDrawer m_letterDrawer;
};