#pragma once
#include <afxwin.h>
#include "MyInitials.h"

class MyInitialsDrawer
{
public:
	// TODO: не использовать size_t для толщины линии, используется для задания размеров индексов в памяти для обычных величин int
	MyInitialsDrawer(const CRect&, size_t lineThickness);
	
	// TODO: если не ожидается нулевой указатель, то следует использовать ссылку, добавить названия параметрам
	void DrawInitial(CDC*, MyInitials, COLORREF);

private:
	bool m_isFrameFull;
	CRect m_frame;
	CRect m_activeFrame;
	size_t m_lineThickness;
};