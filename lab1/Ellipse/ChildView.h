
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
	COLORREF m_circleColor = RGB(255, 0, 0); // Красный цвет по умолчанию
	int m_centerX = 200; // Центр окружности по горизонтали
	int m_centerY = 200; // Центр окружности по вертикали
	int m_radius = 100; // Радиус окружности

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

