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
extern CString GB2312ToUTF8(char* str);
extern CString UTF8ToGB2312(char* str);


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
	sqlite3 *db=NULL;
	CString FileName = "userdata.dat";
	//CString FilePathName = "";
	CString sqlcmd = "";
    int rc;
	char pBuf[MAX_PATH];                //存放路径的变量
	GetCurrentDirectory(MAX_PATH,pBuf);                   //获取程序的当前目录
	FileName.Format("%s\\DataFolder\\userdata.dat",pBuf);
	sprintf(pBuf,"%s",FileName);
	FileName = GB2312ToUTF8(pBuf);
    rc = sqlite3_open(FileName, &db);
	char* ExeErrorMsg = "";
	int i=0;
	CBCGPGridRow* pRow = NULL;
	CString strname;
	CString strval;
	CString strunit;
	//sqlcmd.Format("drop table init_val");
	//sqlcmd.Format("create table init_val(ID integer primary key autoincrement,step1 CHAR(30),step2 CHAR(30),step3 CHAR(30),step4 CHAR(30),step5 CHAR(30))");
	//sprintf(pBuf,"%s",sqlcmd);
	//sqlcmd = GB2312ToUTF8(pBuf);
	//rc = sqlite3_exec( db, sqlcmd, NULL, NULL, &ExeErrorMsg);
	//AfxMessageBox(ExeErrorMsg);
	sqlite3_close(db);
	return;
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
