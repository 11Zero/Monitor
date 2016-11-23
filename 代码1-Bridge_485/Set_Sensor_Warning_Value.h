#if !defined(AFX_SET_SENSOR_WARNING_VALUE_H__FD2270C7_8C73_428C_A326_CFC18318A767__INCLUDED_)
#define AFX_SET_SENSOR_WARNING_VALUE_H__FD2270C7_8C73_428C_A326_CFC18318A767__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Set_Sensor_Warning_Value.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSet_Sensor_Warning_Value dialog
#include "BCG\stdafx.h"
class CSet_Sensor_Warning_Value : public CDialog
{
// Construction
public:
	void CreateGrid();
	void Set_List_Content(int id_list);
	int Get_Step_value(void);
	CSet_Sensor_Warning_Value(CWnd* pParent = NULL);   // standard constructor
    char Cfg_Path[200];//配置文件目录
	char Cur_file_name[200];//不同阶段配置文件名称
	int Step_flag;//当前阶段
	void Set_Radio(int idc);
	//CBCGPGridCtrl* m_pCurrGrid;
// Dialog Data
	//{{AFX_DATA(CSet_Sensor_Warning_Value)
	enum { IDD = IDD_SENSOR_WARNING_VALUE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSet_Sensor_Warning_Value)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSet_Sensor_Warning_Value)
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

#endif // !defined(AFX_SET_SENSOR_WARNING_VALUE_H__FD2270C7_8C73_428C_A326_CFC18318A767__INCLUDED_)
