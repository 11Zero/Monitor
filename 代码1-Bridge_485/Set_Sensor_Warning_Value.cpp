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
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSet_Sensor_Warning_Value, CDialog)
	//{{AFX_MSG_MAP(CSet_Sensor_Warning_Value)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_RADIO5, OnRadio5)
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
	strcpy(Cur_file_name,Cfg_Path);strcat(Cur_file_name,"YY_Step1.txt");
	Set_List_Content(IDC_LIST1);
}

void CSet_Sensor_Warning_Value::OnRadio2() 
{
	// TODO: Add your control notification handler code here
	Step_flag=1;
	strcpy(Cur_file_name,Cfg_Path);strcat(Cur_file_name,"YY_Step2.txt");
	Set_List_Content(IDC_LIST1);
}

void CSet_Sensor_Warning_Value::OnRadio3() 
{
	// TODO: Add your control notification handler code here
	Step_flag=2;
	strcpy(Cur_file_name,Cfg_Path);strcat(Cur_file_name,"YY_Step3.txt");
	Set_List_Content(IDC_LIST1);
}

void CSet_Sensor_Warning_Value::OnRadio4() 
{
	// TODO: Add your control notification handler code here
	Step_flag=3;
	strcpy(Cur_file_name,Cfg_Path);strcat(Cur_file_name,"SG_Step1.txt");
	Set_List_Content(IDC_LIST1);
}

void CSet_Sensor_Warning_Value::OnRadio5() 
{
	// TODO: Add your control notification handler code here
	Step_flag=4;
		strcpy(Cur_file_name,Cfg_Path);strcat(Cur_file_name,"SG_Step2.txt");
	Set_List_Content(IDC_LIST1);
}

void CSet_Sensor_Warning_Value::CreateGrid()
{
	CRect rectClient;
	GetClientRect (rectClient);

}
