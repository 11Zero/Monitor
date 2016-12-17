#if !defined(AFX_INITSENSORVAL_H__6EA674F1_523F_4FAD_A31D_398AA6F13935__INCLUDED_)
#define AFX_INITSENSORVAL_H__6EA674F1_523F_4FAD_A31D_398AA6F13935__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InitSensorVal.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// InitSensorVal dialog

class InitSensorVal : public CDialog
{
// Construction
public:
	void UpdateGrid();
	void CreateGrid();
	InitSensorVal(CWnd* pParent = NULL);   // standard constructor
	int Step_flag;
// Dialog Data
	//{{AFX_DATA(InitSensorVal)
	enum { IDD = IDD_SENSOR_INIT_VAL };
	CStatic	m_wndGridLocation;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(InitSensorVal)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CBCGPGridCtrl m_wndGrid;

	// Generated message map functions
	//{{AFX_MSG(InitSensorVal)
	virtual void OnOK();
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	afx_msg void OnRadio4();
	afx_msg void OnRadio5();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INITSENSORVAL_H__6EA674F1_523F_4FAD_A31D_398AA6F13935__INCLUDED_)
