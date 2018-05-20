// Laba8.h : main header file for the Laba8 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CLaba8App:
// See Laba8.cpp for the implementation of this class
//

class CLaba8App : public CWinApp
{
public:
	CLaba8App();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CLaba8App theApp;
