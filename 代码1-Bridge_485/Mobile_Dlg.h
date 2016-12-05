#if !defined(AFX_MOBILE_DLG_H__DD59B573_1B65_4F68_B2D0_1D08F1DDB9BF__INCLUDED_)
#define AFX_MOBILE_DLG_H__DD59B573_1B65_4F68_B2D0_1D08F1DDB9BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Mobile_Dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Mobile_Dlg dialog

class Mobile_Dlg : public CDialog
{
// Construction
public:
	void Set_Com_Sel_index(int com_box_id,int index);
	void Add_Phone_Num(int com_box_id,char *str);
	void Load_Phone_Num();
	Mobile_Dlg(CWnd* pParent = NULL);   // standard constructor
	char Cfg_File_name[200];//报警参数设置
	void CreateGrid();

// Dialog Data
	//{{AFX_DATA(Mobile_Dlg)
	enum { IDD = IDD_MOBILE_PHENG };
	CStatic	m_wndGridLocation;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Mobile_Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CBCGPGridCtrl		m_wndGrid;
	// Generated message map functions
	//{{AFX_MSG(Mobile_Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnAdd();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOBILE_DLG_H__DD59B573_1B65_4F68_B2D0_1D08F1DDB9BF__INCLUDED_)
