// Testing_Warning_Value_Fun.cpp : implementation file
//

#include "stdafx.h"
#include "Bridge_485.h"
#include "Testing_Warning_Value_Fun.h"
#include "Bridge_Dll.h"//报警动态库头文件
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTesting_Warning_Value_Fun dialog


CTesting_Warning_Value_Fun::CTesting_Warning_Value_Fun(CWnd* pParent /*=NULL*/)
	: CDialog(CTesting_Warning_Value_Fun::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTesting_Warning_Value_Fun)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTesting_Warning_Value_Fun::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTesting_Warning_Value_Fun)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTesting_Warning_Value_Fun, CDialog)
	//{{AFX_MSG_MAP(CTesting_Warning_Value_Fun)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_RADIO5, OnRadio5)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTesting_Warning_Value_Fun message handlers

BOOL CTesting_Warning_Value_Fun::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    strcat(Cfg_Path,"\\");
	Step_flag=0;
	/*strcpy(Cur_file_name,Cfg_Path);
	strcat(Cur_file_name,"YY_Step1.txt");
	Set_List_Content(IDC_LIST1);
	*/
	Set_Radio(IDC_RADIO1);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CTesting_Warning_Value_Fun::Set_Radio(int idc)
{
 CButton *ptr;
 ptr=(CButton*) GetDlgItem(idc);
 if(ptr!=NULL){
     ptr->SetCheck(1);
 }
}
//填充列表框内容
void CTesting_Warning_Value_Fun::Set_List_Content(int id_list)
{
   CListBox *pwn;
   int ret;
   //FILE *fp;
   char tmp_chr[200];
   int Node_Cnt(0),Meas_Node_Num[20];
   double Mas_Sensor_Val[160],SG_Warning_Val[160];
   //SG_Warning_Val----预设报警数据
   //报警参数
   int Warning_Sensor_Num(0),Sensor_Pos[320];  double warn_info[320];//
   pwn=(CListBox *) GetDlgItem(id_list);
   if(pwn!=NULL){
    pwn->ResetContent();
	//获得模拟测量数据
	  strcpy(tmp_chr,Cfg_Path);strcat(tmp_chr,"MoNidata.txt");
        ret=Get_Sensor_Data_From_File(tmp_chr, &Node_Cnt, Meas_Node_Num, Mas_Sensor_Val);
	  if(ret==0) return;
	  //获得不同阶段报警数据
  	  //根据施工阶段不同,获得每个传感器的报警值,成功,返回1,失败,返回0.
      ret=Bridge_Dll_Get_Sensor_Warning_Val(Step_flag,SG_Warning_Val);
	 if(ret==0) return;
	 //显示预警告信息
     ret=Bridge_Dll_Get_Warning_flag(Node_Cnt,Meas_Node_Num,SG_Warning_Val,
					Mas_Sensor_Val,&Warning_Sensor_Num,Sensor_Pos,warn_info);

	 //显示相关信息
	 int index(0),i,j;
	 for(i=0;i<Node_Cnt;i++){
		 for(j=0;j<Meas_Node_Num[i];j++){
          sprintf(tmp_chr,"阶段:%d__节点:%d__通道:%d__测量:%10.2f__报警:%10.2f",Step_flag,i,j,
           Mas_Sensor_Val[index],SG_Warning_Val[index]);
		   pwn->AddString(tmp_chr);
		   index++;
		 }
	 }
	 //显示报警信息
	 if(ret==0) return;
	 pwn->AddString("               ");
	 //sprintf(tmp_chr,"%d",Warning_Sensor_Num);MessageBox(tmp_chr);
	 for(i=0;i<Warning_Sensor_Num;i++){
       sprintf(tmp_chr,"报警:%d__节点:%d__通道:%d__测量:%10.2f__报警:%10.2f",Step_flag,
          Sensor_Pos[i*2],Sensor_Pos[i*2+1],warn_info[i*2],warn_info[i*2+1]);
        pwn->AddString(tmp_chr);
	 }

   }
}

void CTesting_Warning_Value_Fun::OnRadio1() 
{
	// TODO: Add your control notification handler code here
	Step_flag=0;Reset_List(IDC_LIST1);
}

void CTesting_Warning_Value_Fun::OnRadio2() 
{
	// TODO: Add your control notification handler code here
	Step_flag=1;Reset_List(IDC_LIST1);
}

void CTesting_Warning_Value_Fun::OnRadio3() 
{
	// TODO: Add your control notification handler code here
	Step_flag=2;Reset_List(IDC_LIST1);
}

void CTesting_Warning_Value_Fun::OnRadio4() 
{
	// TODO: Add your control notification handler code here
	Step_flag=3;Reset_List(IDC_LIST1);
}

void CTesting_Warning_Value_Fun::OnRadio5() 
{
	// TODO: Add your control notification handler code here
	Step_flag=4;Reset_List(IDC_LIST1);
}
//开始对报警参数进行验证
void CTesting_Warning_Value_Fun::OnButton1() 
{
	// TODO: Add your control notification handler code here
    Set_List_Content(IDC_LIST1);
}
//从文件获得模拟数据
int CTesting_Warning_Value_Fun::Get_Sensor_Data_From_File(char *file_name, int *Sensor_Cnt, int *Node_Num, double *Sensor_Val)
{
//*Sensor_Cnt---节点总数
  FILE *fp;
  int index1(0),index2(0),i,j;
  fp=fopen(file_name,"r");
  if(fp==NULL) {
	         MessageBox("打开模拟文件错误..",file_name,MB_OK);
	         return 0;//打开文件错误
  }
  char tmp_chr[200];
  fgets(tmp_chr,20,fp);*Sensor_Cnt=atoi(tmp_chr);
  //sprintf(tmp_chr,"node_num=%d",*Node_Num);
  //MessageBox(tmp_chr);
  for(i=0;i<*Sensor_Cnt;i++){
       fgets(tmp_chr,200,fp);Node_Num[index1]=atoi(tmp_chr);
      // sprintf(tmp_chr,"node_num=%d",Node_Num[index1]);
       //MessageBox(tmp_chr);
	   for( j=0;j<Node_Num[index1];j++){
         fgets(tmp_chr,200,fp);Sensor_Val[index2]=atof(tmp_chr);
         //sprintf(tmp_chr,"node_num=%10.3f",Sensor_Val[index2]);
         //MessageBox(tmp_chr);
		 index2++;
	   }
	   index1++;
  }
  fclose(fp);

 
  
  return 1;
}
//清空LISTBOX
void CTesting_Warning_Value_Fun::Reset_List(int id_list)
{
	CListBox *pwn;
  
   pwn=(CListBox *) GetDlgItem(id_list);
   if(pwn!=NULL){
    pwn->ResetContent();
   }

}
