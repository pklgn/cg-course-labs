
// ChildView.cpp : implementation of the ChildView class
//

#include "pch.h"
#include "framework.h"
#include "Ellipse.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ChildView

ChildView::ChildView()
{
}

ChildView::~ChildView()
{
}


BEGIN_MESSAGE_MAP(ChildView, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// ChildView message handlers

BOOL ChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void ChildView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CWnd::OnPaint() for painting messages

}

