#if !defined(AFX_BROW_CUR_DATA_H__4006EC2D_6A90_4094_B7DC_A4C3877C54DD__INCLUDED_)
#define AFX_BROW_CUR_DATA_H__4006EC2D_6A90_4094_B7DC_A4C3877C54DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Brow_Cur_Data.h : header file
//
#define WM_RECEIVEMSG WM_USER+100
/////////////////////////////////////////////////////////////////////////////
// Brow_Cur_Data dialog

class Brow_Cur_Data : public CDialog
{
// Construction
public:
	void CreateChart();
	Brow_Cur_Data(CWnd* pParent = NULL);   // standard constructor
	void DrawData();
// Dialog Data
	//{{AFX_DATA(Brow_Cur_Data)
	enum { IDD = IDD_CUR_DATA_DIALOG };
	CBCGPChartCtrl	m_wndChart;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Brow_Cur_Data)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Brow_Cur_Data)
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnButtonTestmsg();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	LRESULT OnReceivemsg(WPARAM wParam, LPARAM lParam);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BROW_CUR_DATA_H__4006EC2D_6A90_4094_B7DC_A4C3877C54DD__INCLUDED_)
