#pragma once
#include <afxwin.h>
#include "MyInitials.h"

class MyInitialsDrawer
{
public:
	// TODO: �� ������������ size_t ��� ������� �����, ������������ ��� ������� �������� �������� � ������ ��� ������� ������� int
	MyInitialsDrawer(const CRect&, size_t lineThickness);
	
	// TODO: ���� �� ��������� ������� ���������, �� ������� ������������ ������, �������� �������� ����������
	void DrawInitial(CDC*, MyInitials, COLORREF);

private:
	bool m_isFrameFull;
	CRect m_frame;
	CRect m_activeFrame;
	size_t m_lineThickness;
};