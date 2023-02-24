
// ChildView.h : interface of the CChildView class
//


#pragma once
#include "MyInitialsDrawer/MyInitialsDrawer.h"


// CChildView window

class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:

private:
	enum
	{
		ANIMATION_TIMER_ID = 1
	};

	struct MyInitialsAnimation
	{
		UINT FPS = 60;
		UINT TIMER_ID = 1;
		INT START_SPEED = 250;
		INT VELOCITY = 100;

		double GetAngularFrequency()
		{
			return 2 * M_PI / START_SPEED * VELOCITY;
		}

	};

	DWORD m_lastTick;
	UINT_PTR m_nTimerID = 0;
	MyInitialsDrawer m_myInitialsDrawer;
	MyInitialsAnimation m_myInitialsAnimation;
	CRect m_frame;

	double m_wavePhase;

// Operations
public:

private:
	void Animate(void);

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	DECLARE_MESSAGE_MAP()
};

