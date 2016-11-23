#if !defined(AFX_TESTING_WARNING_VALUE_FUN_H__DD8DD197_E2ED_4DF0_B3E9_38D14A0548EB__INCLUDED_)
#define AFX_TESTING_WARNING_VALUE_FUN_H__DD8DD197_E2ED_4DF0_B3E9_38D14A0548EB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Testing_Warning_Value_Fun.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTesting_Warning_Value_Fun dialog
//验证报警参数
class CTesting_Warning_Value_Fun : public CDialog
{
// Construction
public:
	void Reset_List(int idc);
	int Get_Sensor_Data_From_File(char *file_nam,int *Sensor_Cnt,int *Node_Num,double *Sensor_Val);
	CTesting_Warning_Value_Fun(CWnd* pParent = NULL);   // standard constructor
    void Set_List_Content(int id_list);
    char Cfg_Path[200];//配置文件目录
	char Cur_file_name[200];//不同阶段配置文件名称
	int Step_flag;//当前阶段
	void Set_Radio(int idc);
// Dialog Data
	//{{AFX_DATA(CTesting_Warning_Value_Fun)
	enum { IDD = TESTING_WARNING_FUN };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTesting_Warning_Value_Fun)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTesting_Warning_Value_Fun)
	virtual BOOL OnInitDialog();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	afx_msg void OnRadio4();
	afx_msg void OnRadio5();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTING_WARNING_VALUE_FUN_H__DD8DD197_E2ED_4DF0_B3E9_38D14A0548EB__INCLUDED_)
