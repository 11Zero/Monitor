// Set_Sensor_Warning_Value.cpp : implementation file
//

#include "stdafx.h"
#include "Bridge_485.h"
#include "Set_Sensor_Warning_Value.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSet_Sensor_Warning_Value dialog
extern CString GB2312ToUTF8(char* str);
extern CString UTF8ToGB2312(char* str);

	char SensorName[10][30];
	char SensorVal[10][30];
	char SensorUnit[10][30];
	int SensorSelCount=0;
	int Step=0;
	int sensor_callback(void* pData,int nCount,char** pValue,char** pName)
	{
		CString str = "";
		str = UTF8ToGB2312(pValue[Step+1]);
		if(SensorSelCount>3&&(SensorSelCount%3-1>atoi(SensorUnit[0])))
			return 0;
		else
		{
		if(SensorSelCount%3==0)
			sprintf(SensorName[SensorSelCount/3],"%s",str);
		if(SensorSelCount%3==1)
			sprintf(SensorVal[SensorSelCount/3],"%s",str);
		if(SensorSelCount%3==2)
			sprintf(SensorUnit[SensorSelCount/3],"%s",str);
		}
		SensorSelCount++;
		return 0;
	}

CSet_Sensor_Warning_Value::CSet_Sensor_Warning_Value(CWnd* pParent /*=NULL*/)
	: CDialog(CSet_Sensor_Warning_Value::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSet_Sensor_Warning_Value)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSet_Sensor_Warning_Value::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSet_Sensor_Warning_Value)
	DDX_Control(pDX, IDC_GRID_RECT, m_wndGridLocation);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSet_Sensor_Warning_Value, CDialog)
	//{{AFX_MSG_MAP(CSet_Sensor_Warning_Value)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_RADIO5, OnRadio5)
	ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSet_Sensor_Warning_Value message handlers

BOOL CSet_Sensor_Warning_Value::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	strcat(Cfg_Path,"\\");
	Step_flag=0;
	CreateGrid();
	strcpy(Cur_file_name,Cfg_Path);
	strcat(Cur_file_name,"YY_Step1.txt");
	Set_List_Content(IDC_LIST1);
	Set_Radio(IDC_RADIO1);
     
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
//获得当前的施工阶段值
int CSet_Sensor_Warning_Value::Get_Step_value()
{
 int ret(0);
 char tmp_file_name[200];
 FILE *fp;
 strcpy(tmp_file_name,Cfg_Path);strcat(tmp_file_name,"Sgcfg.txt");
 fp=fopen(tmp_file_name,"r");
 if(fp==NULL) return 0;
 char tmp_ps[20];
 fgets(tmp_ps,10,fp);fclose(fp);
 ret=atoi(tmp_ps);

 return ret;
}
//填充列表框内容
void CSet_Sensor_Warning_Value::Set_List_Content(int id_list)
{
   CListBox *pwn;
   FILE *fp;
   char tmp_chr[200];
   pwn=(CListBox *) GetDlgItem(id_list);
   if(pwn!=NULL){
    pwn->ResetContent();
       fp=fopen(Cur_file_name,"r");
	   if(fp!=NULL){
		   while(fgets(tmp_chr,200,fp)!=NULL){
             
			 int len=strlen(tmp_chr);tmp_chr[len-1]='\0';
			 pwn->AddString(tmp_chr);

		   }
        fclose(fp);
	   }

   }
}
void CSet_Sensor_Warning_Value::Set_Radio(int idc)
{
 CButton *ptr;
 ptr=(CButton*) GetDlgItem(idc);
 if(ptr!=NULL){
     ptr->SetCheck(1);
 }
}

void CSet_Sensor_Warning_Value::OnRadio1() 
{
	// TODO: Add your control notification handler code here
	Step_flag=0;
	UpdateGrid();
	strcpy(Cur_file_name,Cfg_Path);strcat(Cur_file_name,"YY_Step1.txt");
	Set_List_Content(IDC_LIST1);
}

void CSet_Sensor_Warning_Value::OnRadio2() 
{
	// TODO: Add your control notification handler code here
	Step_flag=1;
	UpdateGrid();
	strcpy(Cur_file_name,Cfg_Path);strcat(Cur_file_name,"YY_Step2.txt");
	Set_List_Content(IDC_LIST1);
}

void CSet_Sensor_Warning_Value::OnRadio3() 
{
	// TODO: Add your control notification handler code here
	Step_flag=2;
	UpdateGrid();
	strcpy(Cur_file_name,Cfg_Path);strcat(Cur_file_name,"YY_Step3.txt");
	Set_List_Content(IDC_LIST1);
}

void CSet_Sensor_Warning_Value::OnRadio4() 
{
	// TODO: Add your control notification handler code here
	Step_flag=3;
	UpdateGrid();
	strcpy(Cur_file_name,Cfg_Path);strcat(Cur_file_name,"SG_Step1.txt");
	Set_List_Content(IDC_LIST1);
}

void CSet_Sensor_Warning_Value::OnRadio5() 
{
	// TODO: Add your control notification handler code here
	Step_flag=4;
	UpdateGrid();
		strcpy(Cur_file_name,Cfg_Path);strcat(Cur_file_name,"SG_Step2.txt");
	Set_List_Content(IDC_LIST1);
}

void CSet_Sensor_Warning_Value::CreateGrid()
{
	Step = Step_flag;
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
	SensorSelCount = 0;
	memset(SensorName,0,sizeof(SensorName)/sizeof(SensorName[0][0]));
	memset(SensorVal,0,sizeof(SensorVal)/sizeof(SensorVal[0][0]));
	memset(SensorUnit,0,sizeof(SensorUnit)/sizeof(SensorUnit[0][0]));
	sqlite3_exec(db,"select * from warning_val",sensor_callback,NULL,&ExeErrorMsg);//callback1为回调函数
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
	m_wndGrid.InsertColumn (1, _T("报警值"), 75);
	m_wndGrid.InsertColumn (2, _T("单位"), 75);
	m_wndGrid.SetHeaderAlign(0,HDF_CENTER);
	m_wndGrid.SetHeaderAlign(1,HDF_CENTER);
	m_wndGrid.SetHeaderAlign(2,HDF_CENTER);
	m_wndGrid.SetColumnAlign(0,HDF_CENTER);
	m_wndGrid.SetColumnAlign(1,HDF_CENTER);
	m_wndGrid.SetColumnAlign(2,HDF_CENTER);
	//m_wndGrid.AddRow()
	//srand ((unsigned) time (NULL));
	for (int i = 0; i < atoi(SensorUnit[0]); i++)
	{
		CBCGPGridRow* pRow = m_wndGrid.CreateRow (m_wndGrid.GetColumnCount ());
		ASSERT_VALID (pRow);
		CString strItem;
		strItem.Format (_T("%s"),SensorName[i+1]);
		pRow->GetItem (0)->SetValue ((_variant_t) strItem);
		strItem.Format (_T("%s"),SensorVal[i+1]);
		pRow->GetItem (1)->SetValue ((_variant_t) strItem);
		strItem.Format (_T("%s"),SensorUnit[i+1]);
		pRow->GetItem (2)->SetValue ((_variant_t) strItem);
		m_wndGrid.AddRow (pRow, FALSE);
	}
	//m_wndGrid.LoadState (_T("MultiLineHeaderGrid"));
	m_wndGrid.AdjustLayout ();

	
	return;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE

}

void CSet_Sensor_Warning_Value::UpdateGrid()
{
	//m_wndGrid.RemoveAll();
	Step = Step_flag;
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
	SensorSelCount = 0;
	memset(SensorName,0,sizeof(SensorName)/sizeof(SensorName[0][0]));
	memset(SensorVal,0,sizeof(SensorVal)/sizeof(SensorVal[0][0]));
	memset(SensorUnit,0,sizeof(SensorUnit)/sizeof(SensorUnit[0][0]));
	sqlite3_exec(db,"select * from warning_val",sensor_callback,NULL,&ExeErrorMsg);//callback1为回调函数
	sqlite3_close(db);

	int RowCount=m_wndGrid.GetRowCount();
	for (int i = 0; i < atoi(SensorUnit[0]); i++)
	{
		CBCGPGridRow* pRow =NULL;
		if(i>=RowCount)
			pRow = m_wndGrid.CreateRow (m_wndGrid.GetColumnCount ());
		else
			pRow = m_wndGrid.GetRow (i);
		ASSERT_VALID (pRow);
		CString strItem;
		strItem.Format (_T("%s"),SensorName[i+1]);
		pRow->GetItem (0)->SetValue ((_variant_t) strItem);
		strItem.Format (_T("%s"),SensorVal[i+1]);
		pRow->GetItem (1)->SetValue ((_variant_t) strItem);
		strItem.Format (_T("%s"),SensorUnit[i+1]);
		pRow->GetItem (2)->SetValue ((_variant_t) strItem);
		if(i>=RowCount)
			m_wndGrid.AddRow (pRow, TRUE);
	}
	if(atoi(SensorUnit[0])<RowCount)
	{
		for(int i=0;i<RowCount-atoi(SensorUnit[0]);i++)
			m_wndGrid.RemoveRow(atoi(SensorUnit[0]), TRUE);
	}
	Invalidate();
}

void CSet_Sensor_Warning_Value::OnBtnAdd() 
{
	CBCGPGridRow* pRow = m_wndGrid.CreateRow (m_wndGrid.GetColumnCount ());	
	m_wndGrid.AddRow (pRow, TRUE);
}

void CSet_Sensor_Warning_Value::OnOK() 
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
	int EmptyCount=0;
	for(i=0;i<m_wndGrid.GetRowCount();i++)
	{
		pRow = m_wndGrid.GetRow (i);
		strname = (pRow->GetItem (0)->GetValue()).bstrVal;
		strval = (pRow->GetItem (1)->GetValue()).bstrVal;
		strunit = (pRow->GetItem (2)->GetValue()).bstrVal;
		if(strcmp(strval,"")==0||strcmp(strunit,"")==0)
		{
			EmptyCount++;
			continue;
		}
		if(EmptyCount==0&&i<atoi(SensorUnit[0])&&strcmp(strname,SensorName[i+1])==0&&strcmp(strval,SensorVal[i+1])==0&&strcmp(strunit,SensorUnit[i+1])==0)
		{
			continue;
		}
		if(i<atoi(SensorUnit[0])||i<SensorSelCount/3-1)
		{
			sqlcmd.Format("update warning_val set step%d='%s' where ID=%d",Step+1,strname,3*(i-EmptyCount)+4);//
			sprintf(pBuf,"%s",sqlcmd);//名称
			sqlcmd = GB2312ToUTF8(pBuf);
			rc = sqlite3_exec( db, sqlcmd, NULL, NULL, &ExeErrorMsg);
			sqlcmd.Format("update warning_val set step%d='%s' where ID=%d",Step+1,strval,3*(i-EmptyCount)+5);//
			sprintf(pBuf,"%s",sqlcmd);//数值
			sqlcmd = GB2312ToUTF8(pBuf);
			rc = sqlite3_exec( db, sqlcmd, NULL, NULL, &ExeErrorMsg);
			sqlcmd.Format("update warning_val set step%d='%s' where ID=%d",Step+1,strunit,3*(i-EmptyCount)+6);//
			sprintf(pBuf,"%s",sqlcmd);//单位
			sqlcmd = GB2312ToUTF8(pBuf);
			rc = sqlite3_exec( db, sqlcmd, NULL, NULL, &ExeErrorMsg);
		}
		else
		{
			SensorSelCount++;
			sqlcmd.Format("insert into warning_val values (%d,'','','','','')",SensorSelCount);//
			sprintf(pBuf,"%s",sqlcmd);//名称
			sqlcmd = GB2312ToUTF8(pBuf);
			rc = sqlite3_exec( db, sqlcmd, NULL, NULL, &ExeErrorMsg);
			SensorSelCount++;
			sqlcmd.Format("insert into warning_val values (%d,'','','','','')",SensorSelCount);//
			sprintf(pBuf,"%s",sqlcmd);//数值
			sqlcmd = GB2312ToUTF8(pBuf);
			rc = sqlite3_exec( db, sqlcmd, NULL, NULL, &ExeErrorMsg);
			SensorSelCount++;
			sqlcmd.Format("insert into warning_val values (%d,'','','','','')",SensorSelCount);//
			sprintf(pBuf,"%s",sqlcmd);//单位
			sqlcmd = GB2312ToUTF8(pBuf);
			rc = sqlite3_exec( db, sqlcmd, NULL, NULL, &ExeErrorMsg);

			sqlcmd.Format("update warning_val set step%d='%s' where ID=%d",Step+1,strname,3*(i-EmptyCount)+4);//
			sprintf(pBuf,"%s",sqlcmd);//名称
			sqlcmd = GB2312ToUTF8(pBuf);
			rc = sqlite3_exec( db, sqlcmd, NULL, NULL, &ExeErrorMsg);
			AfxMessageBox(ExeErrorMsg);
			sqlcmd.Format("update warning_val set step%d='%s' where ID=%d",Step+1,strval,3*(i-EmptyCount)+5);//
			sprintf(pBuf,"%s",sqlcmd);//数值
			sqlcmd = GB2312ToUTF8(pBuf);
			rc = sqlite3_exec( db, sqlcmd, NULL, NULL, &ExeErrorMsg);
			sqlcmd.Format("update warning_val set step%d='%s' where ID=%d",Step+1,strunit,3*(i-EmptyCount)+6);//
			sprintf(pBuf,"%s",sqlcmd);//单位
			sqlcmd = GB2312ToUTF8(pBuf);
			rc = sqlite3_exec( db, sqlcmd, NULL, NULL, &ExeErrorMsg);
		}
	}
	for(i=m_wndGrid.GetRowCount()-EmptyCount+1;i<SensorSelCount/3;i++)
	{
		strname="";
		strval="";
		strunit="";
		sqlcmd.Format("update warning_val set step%d='%s' where ID=%d",Step+1,strname,3*i+1);//
		sprintf(pBuf,"%s",sqlcmd);//名称
		sqlcmd = GB2312ToUTF8(pBuf);
		rc = sqlite3_exec( db, sqlcmd, NULL, NULL, &ExeErrorMsg);
		sqlcmd.Format("update warning_val set step%d='%s' where ID=%d",Step+1,strval,3*i+2);//
		sprintf(pBuf,"%s",sqlcmd);//数值
		sqlcmd = GB2312ToUTF8(pBuf);
		rc = sqlite3_exec( db, sqlcmd, NULL, NULL, &ExeErrorMsg);
		sqlcmd.Format("update warning_val set step%d='%s' where ID=%d",Step+1,strunit,3*i+3);//
		sprintf(pBuf,"%s",sqlcmd);//单位
		sqlcmd = GB2312ToUTF8(pBuf);
		rc = sqlite3_exec( db, sqlcmd, NULL, NULL, &ExeErrorMsg);
	}

	sqlcmd.Format("update warning_val set step%d='%d' where ID=3",Step+1,m_wndGrid.GetRowCount()-EmptyCount);//
	sprintf(pBuf,"%s",sqlcmd);//单位
	sqlcmd = GB2312ToUTF8(pBuf);
	rc = sqlite3_exec( db, sqlcmd, NULL, NULL, &ExeErrorMsg);
	sqlite3_close(db);
}
