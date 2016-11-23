// Sg_Step_Selectiong.cpp : implementation file
//

#include "stdafx.h"
#include "Bridge_485.h"
#include "Sg_Step_Selectiong.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSg_Step_Selectiong dialog


CSg_Step_Selectiong::CSg_Step_Selectiong(CWnd* pParent /*=NULL*/)
	: CDialog(CSg_Step_Selectiong::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSg_Step_Selectiong)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSg_Step_Selectiong::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSg_Step_Selectiong)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSg_Step_Selectiong, CDialog)
	//{{AFX_MSG_MAP(CSg_Step_Selectiong)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_RADIO5, OnRadio5)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSg_Step_Selectiong message handlers

BOOL CSg_Step_Selectiong::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
switch(Step_flag) {
	case 0:{Set_Radio(IDC_RADIO1);break;}
	case 1:{Set_Radio(IDC_RADIO2);break;}
	case 2:{Set_Radio(IDC_RADIO3);break;}
	case 3:{Set_Radio(IDC_RADIO4);break;}
	case 4:{Set_Radio(IDC_RADIO5);break;}
		
}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSg_Step_Selectiong::Set_Radio(int idc)
{
 CButton *ptr;
 ptr=(CButton*) GetDlgItem(idc);
 if(ptr!=NULL){
     ptr->SetCheck(1);

 }
}

void CSg_Step_Selectiong::OnRadio1() 
{
	// TODO: Add your control notification handler code here
	Step_flag=0;
}

void CSg_Step_Selectiong::OnRadio2() 
{
	// TODO: Add your control notification handler code here
	Step_flag=1;
}

void CSg_Step_Selectiong::OnRadio3() 
{
	// TODO: Add your control notification handler code here
	Step_flag=2;
}

void CSg_Step_Selectiong::OnRadio4() 
{
	// TODO: Add your control notification handler code here
	Step_flag=3;
}

void CSg_Step_Selectiong::OnRadio5() 
{
	// TODO: Add your control notification handler code here
	Step_flag=4;
}
