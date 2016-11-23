#if !defined(AFX_FG_485_NET_NODE_DLG_H__9C845269_91D8_4151_889A_108A95984919__INCLUDED_)
#define AFX_FG_485_NET_NODE_DLG_H__9C845269_91D8_4151_889A_108A95984919__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// fg_485_Net_Node_dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Cfg_485_Net_Node_dlg dialog
//
class Cfg_485_Net_Node_dlg : public CDialog
{
// Construction
public:
	void Insert_File_Item(int List_id,char *str);
	void Load_Para_485();
	Cfg_485_Net_Node_dlg(CWnd* pParent = NULL);   // standard constructor
    char Cfg_File_Name[200];//≈‰÷√Œƒº˛√˚≥∆
// Dialog Data
	//{{AFX_DATA(Cfg_485_Net_Node_dlg)
	enum { IDD = IDD_DIALOG1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cfg_485_Net_Node_dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Cfg_485_Net_Node_dlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FG_485_NET_NODE_DLG_H__9C845269_91D8_4151_889A_108A95984919__INCLUDED_)
