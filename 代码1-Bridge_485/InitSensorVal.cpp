// InitSensorVal.cpp : implementation file
//

#include "stdafx.h"
#include "Bridge_485.h"
#include "InitSensorVal.h"
#include "Bridge_485Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// InitSensorVal dialog


InitSensorVal::InitSensorVal(CWnd* pParent /*=NULL*/)
	: CDialog(InitSensorVal::IDD, pParent)
{
	//{{AFX_DATA_INIT(InitSensorVal)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

}


void InitSensorVal::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(InitSensorVal)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(InitSensorVal, CDialog)
	//{{AFX_MSG_MAP(InitSensorVal)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// InitSensorVal message handlers

void InitSensorVal::OnOK() 
{
	// TODO: Add extra validation here
	CBridge_485App* pApp=(CBridge_485App*)AfxGetApp();
	CBridge_485Dlg* pd=(CBridge_485Dlg*)pApp->m_pMainWnd;
	//double InitVal[5];
	CString tempstr="";
	GetDlgItemText(IDC_YY1INITVAL,tempstr);
	pd->InitValOfSensor[0] = atof(tempstr);
	GetDlgItemText(IDC_YY2INITVAL,tempstr);
	pd->InitValOfSensor[1] = atof(tempstr);
	GetDlgItemText(IDC_YY3INITVAL,tempstr);
	pd->InitValOfSensor[2] = atof(tempstr);
	GetDlgItemText(IDC_SG1INITVAL,tempstr);
	pd->InitValOfSensor[3] = atof(tempstr);
	GetDlgItemText(IDC_SG2INITVAL,tempstr);
	pd->InitValOfSensor[4] = atof(tempstr);
	CDialog::OnOK();
}

void InitSensorVal::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CBridge_485App* pApp=(CBridge_485App*)AfxGetApp();
	CBridge_485Dlg* pd=(CBridge_485Dlg*)pApp->m_pMainWnd;
	CString str;
	str.Format("%.2f",pd->InitValOfSensor[0]);
	SetDlgItemText(IDC_YY1INITVAL,str);
	str.Format("%.2f",pd->InitValOfSensor[1]);
	SetDlgItemText(IDC_YY2INITVAL,str);
	str.Format("%.2f",pd->InitValOfSensor[2]);
	SetDlgItemText(IDC_YY3INITVAL,str);
	str.Format("%.2f",pd->InitValOfSensor[3]);
	SetDlgItemText(IDC_SG1INITVAL,str);
	str.Format("%.2f",pd->InitValOfSensor[4]);
	SetDlgItemText(IDC_SG2INITVAL,str);

}
