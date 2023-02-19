
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

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
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

void CChildView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CWnd::OnPaint() for painting messages

	CommandLineParser cmdLineParser;
	cmdLineParser.Parse();

	MyInitialsDrawer myInitialsDrawer({ cmdLineParser.GetLeftTop(), cmdLineParser.GetFrameSize() }, cmdLineParser.GetLineThickness());
	myInitialsDrawer.DrawInitial(dc, LetterDrawer::Letter::E, RGB(33, 115, 70));
	myInitialsDrawer.DrawInitial(dc, LetterDrawer::Letter::P, RGB(43, 87, 154));
	myInitialsDrawer.DrawInitial(dc, LetterDrawer::Letter::K, RGB(183, 71, 42));
}

