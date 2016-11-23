// fg_485_Net_Node_dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Bridge_485.h"
#include "fg_485_Net_Node_dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Cfg_485_Net_Node_dlg dialog


Cfg_485_Net_Node_dlg::Cfg_485_Net_Node_dlg(CWnd* pParent /*=NULL*/)
	: CDialog(Cfg_485_Net_Node_dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(Cfg_485_Net_Node_dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Cfg_485_Net_Node_dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cfg_485_Net_Node_dlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Cfg_485_Net_Node_dlg, CDialog)
	//{{AFX_MSG_MAP(Cfg_485_Net_Node_dlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Cfg_485_Net_Node_dlg message handlers

BOOL Cfg_485_Net_Node_dlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	Load_Para_485();//显示配置文件内容
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
//显示配置文件内容
void Cfg_485_Net_Node_dlg::Load_Para_485()
{
 FILE *fp;
 char tmp[200];
    fp=fopen(Cfg_File_Name,"r");
	if(fp!=NULL){
		while(fgets(tmp,100,fp)!=NULL) {
		 int len=strlen(tmp);tmp[len-1]='\0';
         Insert_File_Item(IDC_LIST1, tmp);
		}

     fclose(fp);
	}
}
//插入文件条目
void Cfg_485_Net_Node_dlg::Insert_File_Item(int List_id, char *str)
{
	CListBox *ptr;
    ptr=(CListBox *) GetDlgItem(List_id);
	if(ptr!=NULL){
      ptr->AddString(str);
   
	}

}
