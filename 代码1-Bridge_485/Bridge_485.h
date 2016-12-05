// Bridge_485.h : main header file for the BRIDGE_485 application
//

#if !defined(AFX_BRIDGE_485_H__87F00AED_7DDE_42BF_A8CC_ABA0A809DD23__INCLUDED_)
#define AFX_BRIDGE_485_H__87F00AED_7DDE_42BF_A8CC_ABA0A809DD23__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CBridge_485App:
// See Bridge_485.cpp for the implementation of this class
//

class CBridge_485App : public CWinApp
{
public:
	CBridge_485App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBridge_485App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CBridge_485App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BRIDGE_485_H__87F00AED_7DDE_42BF_A8CC_ABA0A809DD23__INCLUDED_)
