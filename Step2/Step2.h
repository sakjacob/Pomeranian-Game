/**
 * \file Step2.h
 *
 * \author Jacob Sak
 *
 * This is the main header file for the step2 application
 */

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CStep2App:
// See Step2.cpp for the implementation of this class
//

class CStep2App : public CWinApp
{
private:
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;

public:
	CStep2App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CStep2App theApp;
