
// ChildView.h : interface of the ChildView class
//


#pragma once


// ChildView window

class ChildView : public CWnd
{
// Construction
public:
	ChildView();

// Attributes
public:

private:
	COLORREF m_circleColor = RGB(255, 0, 0); // ������� ���� �� ���������
	int m_centerX = 200; // ����� ���������� �� �����������
	int m_centerY = 200; // ����� ���������� �� ���������
	int m_radius = 100; // ������ ����������

// Operations
public:

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~ChildView();

	// Generated message map functions
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
};

