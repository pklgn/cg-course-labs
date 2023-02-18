
// ChildView.cpp : implementation of the CChildView class
//

#include "pch.h"
#include "framework.h"
#include "MyInitials.h"
#include "ChildView.h"
#include "MyInitialsDrawer/MyInitialsDrawer.h"

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
	MyInitialsDrawer myInitialsDrawer({ CPoint{ 0, 20 }, CSize{ 330, 300 } }, 20);
	myInitialsDrawer.DrawInitial(dc, LetterDrawer::Letter::E, RGB(255, 0, 0));
	myInitialsDrawer.DrawInitial(dc, LetterDrawer::Letter::P, RGB(255, 255, 0));
	myInitialsDrawer.DrawInitial(dc, LetterDrawer::Letter::K, RGB(30, 120, 0));
}

