#if !defined(AFX_BROWSE_HISTORY_DATA_H__1451DDDE_0B6C_4017_9B2B_8E0BA03727DB__INCLUDED_)
#define AFX_BROWSE_HISTORY_DATA_H__1451DDDE_0B6C_4017_9B2B_8E0BA03727DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Browse_History_Data.h : header file
//
#include "ChartCtrl\ChartCtrl.h"
#include "sqlite3.h"
/////////////////////////////////////////////////////////////////////////////
// Browse_History_Data dialog

class Browse_History_Data : public CDialog
{
// Construction
public:
	CChartCtrl m_Chart_Histroy;
	sqlite3 *db; 
	void DrawHistFrame();
	int CountOfPoints;//����20��ͼ����Ҫ�������ڵ���������
	CScrollBar m_ScrollBar;
	//int mCountOfTable;
	SCROLLINFO ScrollBarinfo;
//	CChartScrollBar* m_pScrollBar;
	//int callback(void* ,int nCount,char** pValue,char** pName);
	BOOL BrowseDat();
//	CChartLineSerie* pCurSeries;//��ǰ���
	CChartLineSerie* pHistSeries;//��ʷ���
	double Yvalues[20];//�ù�����һ��ҳ���10���ڵ�����
	double Xvalues[20];//�ù�����һ��ҳ���10���ڵ�����
	double CurY;//���浱ǰ�������
	double CurX;//���浱ǰ�������
	void Load_File_Data();
	Browse_History_Data(CWnd* pParent = NULL);   // standard constructor
    char His_Data_File[200];//���ݿ��ļ�����
	CString Hist_File;//���ݿ��ļ�����
	FILE *fptr;
	void Insert_File_Item(int List_id, char *str);
// Dialog Data
	//{{AFX_DATA(Browse_History_Data)
	enum { IDD = IDD_HIST_BROW_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Browse_History_Data)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Browse_History_Data)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnCancel();
	afx_msg void OnBrowseButton();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnCloseHist();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BROWSE_HISTORY_DATA_H__1451DDDE_0B6C_4017_9B2B_8E0BA03727DB__INCLUDED_)
