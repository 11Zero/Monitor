#if !defined(AFX_RS_232_PARA_H__E90C76F2_1305_41C6_8675_B75085B0390B__INCLUDED_)
#define AFX_RS_232_PARA_H__E90C76F2_1305_41C6_8675_B75085B0390B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RS_232_Para.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// RS_232_Para dialog

class RS_232_Para : public CDialog
{
// Construction
public:
	RS_232_Para(CWnd* pParent = NULL);   // standard constructor
    void Get_Serial_Com_Port(int List_IDC);
		void Set_ComBo_Select(int Combo_ID, int sel_index);
			int Get_Sel_Port_Num();
			int Get_Com_Cur_Sel_Index(int icd_com);
			void Get_Cur_Com_Str(int idc_com,int sel_index);
		int port_index;//
		int m_PPort;//串行口号码
		int Baud_index;//波特率索引值
		char baud_str[20];
// Dialog Data
	//{{AFX_DATA(RS_232_Para)
	enum { IDD = IDD_SCOMM_PARA };
	CComboBox	m_port_num;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(RS_232_Para)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(RS_232_Para)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnSelchangeCombo2();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RS_232_PARA_H__E90C76F2_1305_41C6_8675_B75085B0390B__INCLUDED_)
