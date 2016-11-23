// RS_485_Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Bridge_485.h"
#include "RS_485_Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// RS_485_Dlg dialog


RS_485_Dlg::RS_485_Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(RS_485_Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(RS_485_Dlg)
 
	//}}AFX_DATA_INIT
}


void RS_485_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(RS_485_Dlg)
	DDX_Control(pDX, IDC_COMBO1, m_port_num);
	//}}AFX_DATA_MAP
}
//获得当前下拉列表框的索引值
int RS_485_Dlg::Get_Com_Cur_Sel_Index(int icd_com)
{
	int index(0);
  CComboBox * ptr;
  ptr=(CComboBox *) GetDlgItem(icd_com);
  if(ptr!=NULL) {
     index=ptr->GetCurSel();
  }
  return index;
}
//获得串行口
void RS_485_Dlg::Get_Serial_Com_Port(int List_IDC)
{
CComboBox *ptr_list;
 ptr_list=(CComboBox*) GetDlgItem(List_IDC);
 if(ptr_list!=NULL) {
//获得串行口名称等参数
	 ptr_list->ResetContent();
   HKEY hKey;
    int nretval;
	nretval = RegOpenKeyEx(HKEY_LOCAL_MACHINE, 
		           "Hardware\\DeviceMap\\SerialComm",
					NULL, KEY_READ, &hKey);

	int i = 0;
	if(nretval == ERROR_SUCCESS)  
	{
		char szPortName[MAX_PATH], szCommName[MAX_PATH];
		DWORD dwLong, dwSize;
		while(1)
		{
			dwLong = MAX_PATH;
			dwSize = MAX_PATH;
			nretval = RegEnumValueA(hKey, i, szPortName, &dwLong,
                                    NULL, NULL, (PUCHAR)szCommName, &dwSize);
			if(nretval == ERROR_NO_MORE_ITEMS ) break;
			
			//CString strText =szCommName;
				/*"NAME:";
			strText += 
			//strText += "    PORT:";
			strText += szPortName;
			//m_ListComm.AddString(strText);
			*/
			 //ptr_list->AddString(strText);
			ptr_list->AddString(szCommName);
			
            i++;
		}
		RegCloseKey(hKey);
	}

 }
}

 
int RS_485_Dlg::Get_Sel_Port_Num()
{
CString str;
	char cs[50];
	int i,j;
	j=0;
	int m_Port;
	int nselect=m_port_num.GetCurSel();				//获取当前组合框选项的索引
	port_index=nselect;
	m_port_num.GetLBText(nselect,str);
	int len;
	len=strlen(str);
	for(i=0;i<len;i++) {
		if(isdigit((int) str[i])!=0) {
         cs[j]=str[i];j++;
		}
	}
	//m_Port=atoi(LPCTSTR(str));
	cs[j]='\0';
	m_Port=atoi(cs);
 //	sprintf(cs,"%d %d",m_Port,len);
	 //MessageBox(cs);
	m_PPort=m_Port;
	return m_PPort;
}
void RS_485_Dlg::Set_ComBo_Select(int Combo_ID, int sel_index)
{
 CComboBox *ptr_list;
 ptr_list=(CComboBox *) GetDlgItem(Combo_ID);
 if(ptr_list!=NULL) {
    ptr_list->SetCurSel(sel_index);

 }
}
BOOL RS_485_Dlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	Get_Serial_Com_Port(IDC_COMBO1);
	Set_ComBo_Select(IDC_COMBO1,0);
	Set_ComBo_Select(IDC_COMBO2,0);
	Set_ComBo_Select(IDC_COMBO3,3);
	Set_ComBo_Select(IDC_COMBO4,0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
//串行口号码
void RS_485_Dlg::OnEditchangeCombo1() 
{
	// TODO: Add your control notification handler code here

}
//波特率
void RS_485_Dlg::OnEditchangeCombo2() 
{
	// TODO: Add your control notification handler code here
	
}
 
void RS_485_Dlg::Get_Cur_Com_Str(int idc_com,int sel_index)
{
 CComboBox *ptr;
 ptr=(CComboBox *) GetDlgItem(idc_com);
 if(ptr!=NULL) {
   ptr->GetLBText(sel_index,baud_str);
 }
}
BEGIN_MESSAGE_MAP(RS_485_Dlg, CDialog)
	//{{AFX_MSG_MAP(RS_485_Dlg)
	ON_CBN_EDITCHANGE(IDC_COMBO1, OnEditchangeCombo1)
	ON_CBN_EDITCHANGE(IDC_COMBO2, OnEditchangeCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, OnSelchangeCombo2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// RS_485_Dlg message handlers

void RS_485_Dlg::OnSelchangeCombo1() 
{
	// TODO: Add your control notification handler code here
		Get_Sel_Port_Num();
}

void RS_485_Dlg::OnSelchangeCombo2() 
{
	// TODO: Add your control notification handler code here
	Baud_index=Get_Com_Cur_Sel_Index(IDC_COMBO2);
	Get_Cur_Com_Str(IDC_COMBO2,Baud_index);
}

void RS_485_Dlg::OnOK() 
{
	// TODO: Add extra validation here
		Get_Sel_Port_Num();
        Baud_index=Get_Com_Cur_Sel_Index(IDC_COMBO2);
	    Get_Cur_Com_Str(IDC_COMBO2,Baud_index);
	/*	char spc[100],tmp[100];
		strcpy(spc,baud_str);strcat(spc,"__");
		sprintf(tmp,"%d",m_PPort);strcat(spc,tmp);
		MessageBox(spc);
		*/
	CDialog::OnOK();
}
