#if !defined(AFX_BROW_CUR_DATA_H__4006EC2D_6A90_4094_B7DC_A4C3877C54DD__INCLUDED_)
#define AFX_BROW_CUR_DATA_H__4006EC2D_6A90_4094_B7DC_A4C3877C54DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Brow_Cur_Data.h : header file
//
#include "stdafx.h"
#include "CChart.h"
#define WM_RECEIVEDATA WM_USER+100
/////////////////////////////////////////////////////////////////////////////
// Brow_Cur_Data dialog

class Brow_Cur_Data : public CDialog
{
// Construction
public:
	void CreateChart();
	void SetBottomMessage(CString* str);
	void Forecast();//double input[][],double input_test[][],double output[][],double output_test[][]
	//grid_item g_gi1[30];
	void InitGrid();
	//CGridCtrl m_Grid;
	BOOL IsFirstTime;
	CChartDateTimeAxis* pBottomAxis;
	CChartLineSerie* pSeries;//指向一根监测图线
	CChartLineSerie* pPreSeries;//指向一根预测图线
	int nCount;//采集数据计量
	int TimeDelay;//从主程序获取采集时间间隔
	double XPoints[20];//缓存20个图点
	double YPoints[20];//缓存20个图点
	CStringArray m_StrArray;//用于缓存主程序发来的实时数据
	Brow_Cur_Data(CWnd* pParent = NULL);   // standard constructor
	CChartCtrl m_Chart;
	void DrawData(CChartLineSerie* pSerie,double* X,double* Y);//画图线
	void DrawPreData(CChartLineSerie* pSerie);//画预测图线
	void InitAxis();//初始化图表
	void WriteToSQL(CString *pDataStr, int Node, int Ch, sqlite3 *pdb);//将数据写入数据库，这里只是测试
	int GetDataCount;//计数器，判断在样本数据是否足够
	//CBCGPChartCtrl	m_wndChart;
//	double Input[20][3];
//	double Output[3][3];
//	double PreOutput[3][1];
//	double PreInput[20][1];
//	double PreXPoints[4];//缓存个预测图点
//	double PreYPoints[4];//缓存个预测图点
// Dialog Data
	//{{AFX_DATA(Brow_Cur_Data)
	enum { IDD = IDD_CUR_DATA_DIALOG };
	CBCGPChartCtrl	m_wndChart;
	CStatic	m_MsgPicture;
	CComboBox	m_Com_Node;
	CComboBox	m_Com_Channel;
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
	afx_msg void OnTempbutton();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonDraw();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	LRESULT OnReceiveData(WPARAM wParam,LPARAM lParam);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BROW_CUR_DATA_H__4006EC2D_6A90_4094_B7DC_A4C3877C54DD__INCLUDED_)
