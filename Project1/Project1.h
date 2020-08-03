
// Project1.h : main header file for the Project1 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


/** CProject1App:
* See Project1.cpp for the implementation of this class
*/

class CProject1App : public CWinApp
{
public:
	CProject1App() noexcept;


// Overrides
public:
	/// init \returns bool
	virtual BOOL InitInstance();
	/// exit \returns int
	virtual int ExitInstance();

// Implementation

public:
	/// on app about
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
private:
	/// startupinput
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	/// token
	ULONG_PTR gdiplusToken = 0;
};

extern CProject1App theApp;
