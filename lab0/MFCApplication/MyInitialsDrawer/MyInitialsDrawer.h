#pragma once
#include <afxwin.h>
#include "../Common/Frame/Frame.h"
#include "MyInitials.h"

class MyInitialsDrawer
{
public:
	// TODO: не использовать size_t для толщины линии, используется для задания размеров индексов в памяти для обычных величин int
	MyInitialsDrawer(const RectD&, size_t lineThickness);
	
	// TODO: если не ожидается нулевой указатель, то следует использовать ссылку, добавить названия параметрам
	void DrawInitial(CDC*, MyInitials, COLORREF);

private:
	bool m_isFrameFull;
	RectD m_frame;
	RectD m_activeFrame;
	size_t m_lineThickness;
};