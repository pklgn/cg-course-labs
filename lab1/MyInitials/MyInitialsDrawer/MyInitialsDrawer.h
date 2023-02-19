#pragma once
#include <afxwin.h>
#include "../LetterDrawer/LetterDrawer.h"

class MyInitialsDrawer
{
public:
	const static int MY_INITIALS_LENGTH = 3;

	MyInitialsDrawer();
	// FIXED: не использовать size_t для толщины линии, используется для задания размеров индексов в памяти для обычных величин int
	MyInitialsDrawer(const CRect& frame, LetterDrawer::LineThickness lineThickness);
	
	// FIXED: если не ожидается нулевой указатель, то следует использовать ссылку, добавить названия параметрам
	void DrawInitial(CDC&, LetterDrawer::Letter, COLORREF);

	void SetInitialShiftY(int shift);
	void SetFrame(const CRect& frame);
	void SetLineThickness(LetterDrawer::LineThickness lineThickness);

	int GetInitialShiftY() const;

private:
	bool m_isFrameFull;
	CRect m_frame;
	CRect m_activeFrame;
	LetterDrawer m_letterDrawer;
	LetterDrawer::LineThickness m_lineThickness = 1;
	int m_initialShiftY;
};