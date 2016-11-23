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

/////////////////////////////////////////////////////////////////////////////
// Mobile_Dlg dialog


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
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Mobile_Dlg, CDialog)
	//{{AFX_MSG_MAP(Mobile_Dlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Mobile_Dlg message handlers

BOOL Mobile_Dlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	Load_Phone_Num();//
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
