#if !defined(AFX_SG_STEP_SELECTIONG_H__5078C9CC_4A2F_4480_9FC0_FC5AC00A0EFD__INCLUDED_)
#define AFX_SG_STEP_SELECTIONG_H__5078C9CC_4A2F_4480_9FC0_FC5AC00A0EFD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Sg_Step_Selectiong.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSg_Step_Selectiong dialog

class CSg_Step_Selectiong : public CDialog
{
// Construction
public:
	int Step_flag;
	CSg_Step_Selectiong(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSg_Step_Selectiong)
	enum { IDD = IDD_SG_STEP_SEL };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSg_Step_Selectiong)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSg_Step_Selectiong)
	virtual BOOL OnInitDialog();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	afx_msg void OnRadio4();
	afx_msg void OnRadio5();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void Set_Radio(int idc);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SG_STEP_SELECTIONG_H__5078C9CC_4A2F_4480_9FC0_FC5AC00A0EFD__INCLUDED_)
