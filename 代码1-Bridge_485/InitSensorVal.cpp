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

	char SensorName_init[10][30];
	char SensorVal_init[10][30];
	char SensorUnit_init[10][30];
	int SensorSelCount_init=0;
	int Step_init=0;
	int sensor_init_callback(void* pData,int nCount,char** pValue,char** pName)
	{
		CString str = "";
		str = UTF8ToGB2312(pValue[Step_init+1]);
		if(SensorSelCount_init>3&&(SensorSelCount_init%3-1>atoi(SensorUnit_init[0])))
			return 0;
		else
		{
		if(SensorSelCount_init%3==0)
			sprintf(SensorName_init[SensorSelCount_init/3],"%s",str);
		if(SensorSelCount_init%3==1)
			sprintf(SensorVal_init[SensorSelCount_init/3],"%s",str);
		if(SensorSelCount_init%3==2)
			sprintf(SensorUnit_init[SensorSelCount_init/3],"%s",str);
		}
		SensorSelCount_init++;
		return 0;
	}

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
	DDX_Control(pDX, IDC_GRID_RECT, m_wndGridLocation);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(InitSensorVal, CDialog)
	//{{AFX_MSG_MAP(InitSensorVal)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_RADIO5, OnRadio5)
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
	CString strval;
	for(i=0;i<m_wndGrid.GetRowCount();i++)
	{
		pRow = m_wndGrid.GetRow (i);
		strval = (pRow->GetItem (1)->GetValue()).bstrVal;
		if(strcmp(strval,SensorVal_init[i+1])==0)
		{
			continue;
		}
		sqlcmd.Format("update init_val set step%d='%s' where ID=%d",Step_flag+1,strval,i*3+5);//
		sprintf(pBuf,"%s",sqlcmd);//数值
		sqlcmd = GB2312ToUTF8(pBuf);
		rc = sqlite3_exec( db, sqlcmd, NULL, NULL, &ExeErrorMsg);
	}
	sqlite3_close(db);
	return;
	// TODO: Add extra validation here
	CBridge_485App* pApp=(CBridge_485App*)AfxGetApp();
	CBridge_485Dlg* pd=(CBridge_485Dlg*)pApp->m_pMainWnd;
	pd->UpdateSensorInitVal(Step_flag);
	//double InitVal[5];
/*	CString tempstr="";
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
	CDialog::OnOK();*/
}

void InitSensorVal::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CBridge_485App* pApp=(CBridge_485App*)AfxGetApp();
	CBridge_485Dlg* pd=(CBridge_485Dlg*)pApp->m_pMainWnd;
	CString str;
	/*str.Format("%.2f",pd->InitValOfSensor[0]);
	SetDlgItemText(IDC_YY1INITVAL,str);
	str.Format("%.2f",pd->InitValOfSensor[1]);
	SetDlgItemText(IDC_YY2INITVAL,str);
	str.Format("%.2f",pd->InitValOfSensor[2]);
	SetDlgItemText(IDC_YY3INITVAL,str);
	str.Format("%.2f",pd->InitValOfSensor[3]);
	SetDlgItemText(IDC_SG1INITVAL,str);
	str.Format("%.2f",pd->InitValOfSensor[4]);
	SetDlgItemText(IDC_SG2INITVAL,str);*/

}

void InitSensorVal::CreateGrid()
{
	Step_init = Step_flag;
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
	SensorSelCount_init = 0;
	memset(SensorName_init,0,sizeof(SensorName_init)/sizeof(SensorName_init[0][0]));
	memset(SensorVal_init,0,sizeof(SensorVal_init)/sizeof(SensorVal_init[0][0]));
	memset(SensorUnit_init,0,sizeof(SensorUnit_init)/sizeof(SensorUnit_init[0][0]));
	sqlite3_exec(db,"select * from init_val",sensor_init_callback,NULL,&ExeErrorMsg);//callback1为回调函数
	sqlite3_close(db);
	//return ;



	
	CWaitCursor wait;
	
	CRect rectGrid;
	m_wndGridLocation.GetWindowRect( &rectGrid );
	ScreenToClient( &rectGrid );
	m_wndGrid.Create (WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, rectGrid, this, IDC_GRID_RECT);
	m_wndGrid.EnableHeader (TRUE, BCGP_GRID_HEADER_MOVE_ITEMS);
	m_wndGrid.EnableInvertSelOnCtrl ();
	// Set grid tab order (first):
	m_wndGrid.SetWindowPos (&CWnd::wndTop, -1, -1, -1, -1, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
	//m_wndGrid.SetReadOnly ();
//////////////////////////////////////////
	m_wndGrid.InsertColumn (0, _T("名称"), 75);
	m_wndGrid.InsertColumn (1, _T("初始值"), 75);
	m_wndGrid.InsertColumn (2, _T("单位"), 75);
	m_wndGrid.SetHeaderAlign(0,HDF_CENTER);
	m_wndGrid.SetHeaderAlign(1,HDF_CENTER);
	m_wndGrid.SetHeaderAlign(2,HDF_CENTER);
	m_wndGrid.SetColumnAlign(0,HDF_CENTER);
	m_wndGrid.SetColumnAlign(1,HDF_CENTER);
	m_wndGrid.SetColumnAlign(2,HDF_CENTER);
	//m_wndGrid.AddRow()
	//srand ((unsigned) time (NULL));
	for (int i = 0; i < atoi(SensorUnit_init[0]); i++)
	{
		CBCGPGridRow* pRow = m_wndGrid.CreateRow (m_wndGrid.GetColumnCount ());
		ASSERT_VALID (pRow);
		CString strItem;
		strItem.Format (_T("%s"),SensorName_init[i+1]);
		pRow->GetItem (0)->SetValue ((_variant_t) strItem);
		strItem.Format (_T("%s"),SensorVal_init[i+1]);
		pRow->GetItem (1)->SetValue ((_variant_t) strItem);
		strItem.Format (_T("%s"),SensorUnit_init[i+1]);
		pRow->GetItem (2)->SetValue ((_variant_t) strItem);
		m_wndGrid.AddRow (pRow, FALSE);
	}
	//m_wndGrid.LoadState (_T("MultiLineHeaderGrid"));
	m_wndGrid.AdjustLayout ();

	
	return;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL InitSensorVal::OnInitDialog() 
{
	CDialog::OnInitDialog();
	Step_flag=0;	
	// TODO: Add extra initialization here
	CreateGrid();
	//GetDlgItem(IDC_RADIO1)->
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void InitSensorVal::UpdateGrid()
{
	//m_wndGrid.RemoveAll();
	Step_init = Step_flag;
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
	SensorSelCount_init = 0;
	if(rc != SQLITE_OK)
	{
		AfxMessageBox(ExeErrorMsg);
		return;
	}
	memset(SensorName_init,0,sizeof(SensorName_init)/sizeof(SensorName_init[0][0]));
	memset(SensorVal_init,0,sizeof(SensorVal_init)/sizeof(SensorVal_init[0][0]));
	memset(SensorUnit_init,0,sizeof(SensorUnit_init)/sizeof(SensorUnit_init[0][0]));
	sqlite3_exec(db,"select * from init_val",sensor_init_callback,NULL,&ExeErrorMsg);//callback1为回调函数
	sqlite3_close(db);

	int RowCount=m_wndGrid.GetRowCount();
	for (int i = 0; i < atoi(SensorUnit_init[0]); i++)
	{
		CBCGPGridRow* pRow =NULL;
		if(i>=RowCount)
			pRow = m_wndGrid.CreateRow (m_wndGrid.GetColumnCount ());
		else
			pRow = m_wndGrid.GetRow (i);
		ASSERT_VALID (pRow);
		CString strItem;
		strItem.Format (_T("%s"),SensorName_init[i+1]);
		pRow->GetItem (0)->SetValue ((_variant_t) strItem);
		strItem.Format (_T("%s"),SensorVal_init[i+1]);
		pRow->GetItem (1)->SetValue ((_variant_t) strItem);
		strItem.Format (_T("%s"),SensorUnit_init[i+1]);
		pRow->GetItem (2)->SetValue ((_variant_t) strItem);
		if(i>=RowCount)
			m_wndGrid.AddRow (pRow, TRUE);
	}
	if(atoi(SensorUnit_init[0])<RowCount)
	{
		for(int i=0;i<RowCount-atoi(SensorUnit_init[0]);i++)
			m_wndGrid.RemoveRow(atoi(SensorUnit_init[0]), TRUE);
	}
	Invalidate();
	return;
}
void InitSensorVal::OnRadio1() 
{
	OnOK();
	Step_flag=0;
	UpdateGrid();
	//AfxMessageBox(str);
	
}

void InitSensorVal::OnRadio2() 
{
	OnOK();
	Step_flag=1;
	UpdateGrid();
	
}

void InitSensorVal::OnRadio3() 
{
	OnOK();
	Step_flag=2;
	UpdateGrid();
	
}

void InitSensorVal::OnRadio4() 
{
	OnOK();
	Step_flag=3;
	UpdateGrid();
	
}

void InitSensorVal::OnRadio5() 
{
	OnOK();
	Step_flag=4;
	UpdateGrid();
	
}
