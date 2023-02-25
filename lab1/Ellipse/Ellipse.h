
// Ellipse.h : main header file for the Ellipse application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// EllipseApp:
// See Ellipse.cpp for the implementation of this class
//

class EllipseApp : public CWinApp
{
public:
	EllipseApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern EllipseApp theApp;
