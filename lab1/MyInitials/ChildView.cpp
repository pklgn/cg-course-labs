
// ChildView.cpp : implementation of the CChildView class
//

#include "pch.h"
#include "framework.h"
#include "MyInitials.h"
#include "ChildView.h"
#include "MyInitialsDrawer/MyInitialsDrawer.h"
#include "CommandLineParser/CommandLineParser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

const double ROTATION_SPEED = 30;

CChildView::CChildView()
	: m_lastTick(GetTickCount())
{
	CommandLineParser cmdLineParser;
	cmdLineParser.Parse();
	m_frame = { cmdLineParser.GetLeftTop(), cmdLineParser.GetFrameSize() };
	m_myInitialsDrawer.SetFrame(m_frame);
	m_myInitialsDrawer.SetLineThickness(cmdLineParser.GetLineThickness());
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

int CChildView::OnCreate(LPCREATESTRUCT /*lpCreateStruct*/)
{
	m_nTimerID = SetTimer(1, 100, 0);

	return 0;
}

void CChildView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CWnd::OnPaint() for painting messages

	CommandLineParser cmdLineParser;
	cmdLineParser.Parse();

	m_myInitialsDrawer.DrawInitial(dc, LetterDrawer::Letter::E, RGB(33, 115, 70));
	m_myInitialsDrawer.DrawInitial(dc, LetterDrawer::Letter::P, RGB(43, 87, 154));
	m_myInitialsDrawer.DrawInitial(dc, LetterDrawer::Letter::K, RGB(183, 71, 42));
}

void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == m_nTimerID)
	{
		Animate();
	}
}

void CChildView::OnDestroy()
{
	KillTimer(1);
}

void CChildView::Animate(void)
{
	auto currentTick = GetTickCount();
	double delta = (currentTick - m_lastTick) * 0.001;
	m_lastTick = currentTick;

	m_wavePhase += ROTATION_SPEED * delta;
	m_wavePhase = fmod(m_wavePhase, 3.14);

	auto shiftY = static_cast<int>(cos(m_wavePhase) * 20);
	m_frame.top += shiftY;
	m_frame.bottom += shiftY;
	m_myInitialsDrawer.SetInitialShiftY(shiftY);
	m_myInitialsDrawer.SetFrame(m_frame);

	Invalidate();
	UpdateWindow();
}
