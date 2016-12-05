// Brow_Cur_Data.cpp : implementation file
//

#include "stdafx.h"
#include "Bridge_485.h"
#include "Brow_Cur_Data.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Brow_Cur_Data dialog


Brow_Cur_Data::Brow_Cur_Data(CWnd* pParent /*=NULL*/)
	: CDialog(Brow_Cur_Data::IDD, pParent)
{
	//{{AFX_DATA_INIT(Brow_Cur_Data)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Brow_Cur_Data::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Brow_Cur_Data)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Brow_Cur_Data, CDialog)
	//{{AFX_MSG_MAP(Brow_Cur_Data)
	ON_MESSAGE(WM_RECEIVEMSG,OnReceivemsg)
	ON_BN_CLICKED(IDC_BUTTON_TESTMSG, OnButtonTestmsg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Brow_Cur_Data message handlers
void Brow_Cur_Data::DrawData()
{



}


void Brow_Cur_Data::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDialog::PostNcDestroy();
	delete this;
}

void Brow_Cur_Data::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	DestroyWindow();
}

void Brow_Cur_Data::OnOK() 
{
	CTime m_cur_time=CTime::GetCurrentTime();
	CString ss=m_cur_time.Format("%Y_%m_%d_%H_%M_%S");
	CString m_strFolderPath="DataFolder" ;
	// �ж�·���Ƿ���� 
	if (!PathIsDirectory(m_strFolderPath) ) 
	{ 
		CString strMsg; 
		strMsg.Format ("ָ��·��\"%s\"�����ڣ��Ƿ񴴽�?", m_strFolderPath); 
		if (AfxMessageBox(strMsg, MB_YESNO) == IDYES) 
		{ 
			if (!CreateDirectory(m_strFolderPath, NULL)) 
			{ 
				strMsg.Format ("����·��\"%s\"ʧ�ܣ����洢�ڸ�Ŀ¼��", m_strFolderPath); 
				AfxMessageBox(strMsg);
			} 
		} 
	}
	sqlite3* db;
	int rc = sqlite3_open(m_strFolderPath+"\\"+"data.dat",&db);
	ASSERT(rc == SQLITE_OK);
	if(rc == SQLITE_OK)
	{
		AfxMessageBox("�򿪳ɹ�");
		SetWindowText("����д���ļ�:"+ss);
	}
	else
	{	
		CString OpenErrorMsg = "";
		OpenErrorMsg.Format("���ݿ�򿪳���.\n����ԭ��:%s\n", sqlite3_errmsg(db));
		AfxMessageBox(OpenErrorMsg);
		return;
	}
	long StartTime=GetTickCount();
	CString TableName = "";
	CString sqlcmd = "";
	char* ExeErrorMsg = "";
	for(int i = 1;i <=5;i++)//Node����
	{
		for(int j = 1;j <=7;j++)//Channel����
		{
			TableName.Format("Node_%d_Ch_%d",i,j);
			sqlcmd = "create table if not exists "+TableName+
				"(NUM integer primary key autoincrement, DataTime varchar(30),SensorVal integer(15))";
			rc = sqlite3_exec(db, sqlcmd, NULL, NULL, &ExeErrorMsg);
			if(rc != SQLITE_OK)
				AfxMessageBox(ExeErrorMsg);
			//else
				//AfxMessageBox("�����ɹ�");			
		}
	}
	long EndTime=GetTickCount();
	CString RunTime = "";
	RunTime.Format("�����ɹ�,��ʱ%.2fs",(EndTime-StartTime)/1000.0);
	AfxMessageBox(RunTime);
	sqlite3_close(db);
}


LRESULT Brow_Cur_Data::OnReceivemsg(WPARAM wParam, LPARAM lParam)
{
	//AfxMessageBox("onreceivemsg");
	CString str = "";
	str.Format("wParam = %d,lParam = %d",wParam,lParam);
	SetWindowText(str);
	return 0;
}

void Brow_Cur_Data::OnButtonTestmsg() 
{
	// TODO: Add your control notification handler code here
	
}
