#pragma once
#include <afxwin.h>
#include "../Common/Frame/Frame.h"
#include "MyInitials.h"

class MyInitialsDrawer
{
public:
	// TODO: �� ������������ size_t ��� ������� �����, ������������ ��� ������� �������� �������� � ������ ��� ������� ������� int
	MyInitialsDrawer(const RectD&, size_t lineThickness);
	
	// TODO: ���� �� ��������� ������� ���������, �� ������� ������������ ������, �������� �������� ����������
	void DrawInitial(CDC*, MyInitials, COLORREF);

private:
	bool m_isFrameFull;
	RectD m_frame;
	RectD m_activeFrame;
	size_t m_lineThickness;
};