
// MyInitials.h : main header file for the MyInitials application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// MyInitialsApp:
// See MyInitials.cpp for the implementation of this class
//

class MyInitialsApp : public CWinApp
{
public:
	MyInitialsApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern MyInitialsApp theApp;
