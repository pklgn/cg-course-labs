
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

const UINT_PTR MILLISECONDS_IN_SECOND = 1000;

CChildView::CChildView()
	: m_lastTick(GetTickCount())
{
	CommandLineParser cmdLineParser;
	cmdLineParser.Parse();
	m_frame = { cmdLineParser.GetLeftTop(), cmdLineParser.GetFrameSize() };
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
	ON_WM_ERASEBKGND()
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
	m_nTimerID = SetTimer(m_myInitialsAnimation.TIMER_ID,
		(UINT)(MILLISECONDS_IN_SECOND / m_myInitialsAnimation.FPS),
		NULL);

	return 0;
}

void CChildView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CDC dcMem;
	CBitmap bmpDC;
	CBitmap* pOldBmp;

	CRect rcClient;
	GetClientRect(&rcClient);

	dcMem.CreateCompatibleDC(&dc);
	bmpDC.CreateCompatibleBitmap(&dc, rcClient.right, rcClient.bottom);
	
	pOldBmp = dcMem.SelectObject(&bmpDC);
	// https://stackoverflow.com/questions/11037228/gdi-how-to-create-and-fill-bitmap
	CBrush brush(RGB(255, 255, 255));
	dcMem.FillRect(&rcClient, &brush);

	if (dcMem.GetSafeHdc() != NULL)
	{
		m_myInitialsDrawer.SetFrame(m_frame);

		m_myInitialsDrawer.DrawInitial(dcMem, LetterDrawer::Letter::E, RGB(33, 115, 70));
		m_myInitialsDrawer.DrawInitial(dcMem, LetterDrawer::Letter::P, RGB(43, 87, 154));
		m_myInitialsDrawer.DrawInitial(dcMem, LetterDrawer::Letter::K, RGB(183, 71, 42));

		dc.BitBlt(0, 0, rcClient.right, rcClient.bottom, &dcMem, 0, 0, SRCCOPY);
	}

	dcMem.SelectObject(pOldBmp);
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
	KillTimer(m_myInitialsAnimation.TIMER_ID);
}

void CChildView::Animate(void)
{
	auto currentTick = GetTickCount();
	auto deltaTime = (currentTick - m_lastTick) / static_cast<double>(MILLISECONDS_IN_SECOND);

	auto deltaHeight = deltaTime * (m_myInitialsAnimation.START_SPEED - m_myInitialsAnimation.VELOCITY * deltaTime / 2);
	m_frame.bottom = m_frame.Height() + deltaHeight;
	m_frame.top = deltaHeight;

	auto animationAngularFrequency = m_myInitialsAnimation.GetAngularFrequency();
	m_myInitialsDrawer.SetInitialShiftY(static_cast<int>(std::sin(animationAngularFrequency * deltaTime) * 30));

	if (deltaHeight < 0)
	{
		m_lastTick = currentTick;
	}

	Invalidate();
	UpdateWindow();
}

BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}