// Mobile_Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Bridge_485.h"
#include "Mobile_Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern CString GB2312ToUTF8(char* str);
extern CString UTF8ToGB2312(char* str);
/////////////////////////////////////////////////////////////////////////////
// Mobile_Dlg dialog
	char Name[10][20];
	char Phone[10][50];
	int SelCount=0;
	int phone_callback(void* pData,int nCount,char** pValue,char** pName)
	{
		CString str = "";
		str = UTF8ToGB2312(pValue[1]);
		sprintf(Name[SelCount],"%s",str);
		str = UTF8ToGB2312(pValue[2]);
		sprintf(Phone[SelCount],"%s",str);
		SelCount++;
		return 0;
	}
Mobile_Dlg::Mobile_Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(Mobile_Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(Mobile_Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Mobile_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Mobile_Dlg)
	DDX_Control(pDX, IDC_GRID_RECT, m_wndGridLocation);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Mobile_Dlg, CDialog)
	//{{AFX_MSG_MAP(Mobile_Dlg)
	ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Mobile_Dlg message handlers

BOOL Mobile_Dlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	Load_Phone_Num();//
	CreateGrid();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
//调入手机号
void Mobile_Dlg::Load_Phone_Num()
{
/*	for(int i=0;i<10;i++) {
      Add_Phone_Num(IDC_COMBO1, "张长会_13866120701");
	}
	*/
	FILE *fp;
	int i,phone_num;
	char tmp1[100],tmp2[100];
//	MessageBox("ok",(char *) &Cfg_File_name[0]);
    int len;
	fp=fopen(Cfg_File_name,"r");
	if(fp!=NULL) {
		for(i=0;i<7;i++) {fgets(tmp1,100,fp); }
		fgets(tmp1,100,fp);phone_num=atoi(tmp1);
		//sprintf(tmp2,"%d",phone_num);
	//	MessageBox(tmp2);
		if(phone_num>=1) {
			for(i=0;i<phone_num;i++) {
		      fgets(tmp1,100,fp);len=strlen(tmp1);tmp1[len-1]='\0';
			  fgets(tmp2,100,fp);len=strlen(tmp2);tmp2[len-1]='\0';
		      strcat(tmp1,"  ");strcat(tmp1,tmp2);
			  Add_Phone_Num(IDC_COMBO1,tmp1);
			}

	    Set_Com_Sel_index(IDC_COMBO1,0);
		}
	   fclose(fp);
	   }


}
//添加手机号
void Mobile_Dlg::Add_Phone_Num(int com_box_id, char *str)
{
 CComboBox *ptr;
 ptr=(CComboBox *) GetDlgItem(com_box_id);
 if(ptr!=NULL) {
    ptr->InsertString(-1,str);

 }

}
//
void Mobile_Dlg::Set_Com_Sel_index(int com_box_id, int index)
{
 CComboBox *ptr;
 ptr=(CComboBox *) GetDlgItem(com_box_id);
 if(ptr!=NULL) {
    ptr->SetCurSel(index);

 }
}

void Mobile_Dlg::CreateGrid()
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
	//rc = sqlite3_exec( db, "drop table MyTable_4", NULL, NULL, &ExeErrorMsg);
	//sqlcmd = "create table phone(ID integer primary key autoincrement,name CHAR(30),phone CHAR(50));";
	/*sqlcmd = "INSERT INTO phone	VALUES (1,'张长会','13866120701')";
	sprintf(pBuf,"%s",sqlcmd);
	sqlcmd = GB2312ToUTF8(pBuf);
	rc = sqlite3_exec( db, sqlcmd, NULL, NULL, &ExeErrorMsg);
	sqlcmd = "INSERT INTO phone	VALUES (2,'孟再生','15155133889')";
	sprintf(pBuf,"%s",sqlcmd);
	sqlcmd = GB2312ToUTF8(pBuf);
	rc = sqlite3_exec( db, sqlcmd, NULL, NULL, &ExeErrorMsg);*/
	SelCount = 0;
	memset(Name,0,sizeof(Name)/sizeof(Name[0][0]));
	sqlite3_exec(db,"select * from phone",phone_callback,NULL,&ExeErrorMsg);//callback1为回调函数
	sqlite3_close(db);
	//return ;




	CWaitCursor wait;
	
	CRect rectGrid;
	//m_wndGridLocation.GetClientRect (&rectGrid);
	//m_wndGridLocation.MapWindowPoints (this, &rectGrid);
	m_wndGridLocation.GetWindowRect( &rectGrid );
	ScreenToClient( &rectGrid );

	m_wndGrid.Create (WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, rectGrid, this, IDC_GRID_RECT);
	m_wndGrid.EnableHeader (TRUE, BCGP_GRID_HEADER_MOVE_ITEMS);
	m_wndGrid.EnableInvertSelOnCtrl ();

	// Set grid tab order (first):
	m_wndGrid.SetWindowPos (&CWnd::wndTop, -1, -1, -1, -1, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
	//m_wndGrid.SetReadOnly ();
	m_wndGrid.InsertColumn (0, _T("姓名"), 75);
	m_wndGrid.InsertColumn (1, _T("电话"), 120);
	m_wndGrid.SetHeaderAlign(0,HDF_CENTER);
	m_wndGrid.SetHeaderAlign(1,HDF_CENTER);
	m_wndGrid.SetColumnAlign(0,HDF_CENTER);
	m_wndGrid.SetColumnAlign(1,HDF_CENTER);
	//m_wndGrid.AddRow()
	//srand ((unsigned) time (NULL));
	for (int i = 0; i < SelCount; i++)
	{
		CBCGPGridRow* pRow = m_wndGrid.CreateRow (m_wndGrid.GetColumnCount ());
		ASSERT_VALID (pRow);
		CString strItem;
		strItem.Format (_T("%s"),Name[i]);
		pRow->GetItem (0)->SetValue ((_variant_t) strItem);
		strItem.Format (_T("%s"),Phone[i]);
		pRow->GetItem (1)->SetValue ((_variant_t) strItem);
		m_wndGrid.AddRow (pRow, FALSE);
	}
	//m_wndGrid.LoadState (_T("MultiLineHeaderGrid"));
	m_wndGrid.AdjustLayout ();
	return;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE


}


void Mobile_Dlg::OnBtnAdd() 
{
	CBCGPGridRow* pRow = m_wndGrid.CreateRow (m_wndGrid.GetColumnCount ());
	m_wndGrid.AddRow (pRow, TRUE);	
	return;
}

void Mobile_Dlg::OnOK() 
{
	sqlite3 *db=NULL;
	CString FileName = "userdata.dat";
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
	CString strphone;
	for(i=0;i<m_wndGrid.GetRowCount();i++)
	{
		pRow = m_wndGrid.GetRow (i);
		strname = (pRow->GetItem (0)->GetValue()).bstrVal;
		strphone = (pRow->GetItem (1)->GetValue()).bstrVal;
		if(strcmp(strname,"")==0||strcmp(strphone,"")==0)
			continue;
		if(i<SelCount&&strcmp(strname,Name[i])==0&&strcmp(strphone,Phone[i])==0)
			continue;
		else
		{
			if(i<SelCount)
			{
				sqlcmd.Format("update phone set name='%s',phone='%s' where ID=%d",strname,strphone,i+1);
			}
			else
			{
				sqlcmd.Format("insert into phone values(%d,'%s','%s')",i+1,strname,strphone);
			}
			sprintf(pBuf,"%s",sqlcmd);
			sqlcmd = GB2312ToUTF8(pBuf);
			rc = sqlite3_exec( db, sqlcmd, NULL, NULL, &ExeErrorMsg);
		}
	}
	sqlite3_close(db);
	CDialog::OnOK();
}
