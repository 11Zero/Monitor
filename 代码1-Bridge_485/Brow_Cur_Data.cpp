// Brow_Cur_Data.cpp : implementation file
//

#include "stdafx.h"
#include "Bridge_485.h"
#include "Brow_Cur_Data.h"
#include "CChart.h"
#include "Forecast.h"
#include <afxtempl.h>//ʹ��CArray
//#include <math.h>
//#include <stdlib.h>
//#include <time.h>

#define input_col 4
#define input_row 100
#define output_col 1
#define output_row 100
#define n 6 //���νڵ����
#define inputtest_row 50
#define outputtest_row 50
#define maxgen 100//��������


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

grid_item g_gi[] = {
	gi_hdr("����"),
		gi_edit("Edit"),
		gi_combo("Combo drop down",GCS_DRDN),
		gi_edit("Edit (NC)",GLS_NC),
		gi_edit("Edit with custom",GCSS_CSBT),
		gi_combo("Combo"),
		
		gi_hdr("Header (NC)",GLS_NC),	
		gi_edit("Edit with custom",GCSS_CSBT),
		gi_edit("Edit read only",GSS_RDNL),
		gi_edit("Edit number",GES_NUMB),
		gi_combo("Combo (NC)",GLS_NC),
		gi_edit("Edit password",GES_PASS),
		gi_combo("Combo with custom",GCSS_CSBT),	
};


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
	DDX_Control(pDX, IDC_COMBO_NODE, m_Com_Node);
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_Com_Channel);
	DDX_Control(pDX, IDC_CHART, m_Chart);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Brow_Cur_Data, CDialog)
//{{AFX_MSG_MAP(Brow_Cur_Data)
ON_BN_CLICKED(IDC_TEMPBUTTON, OnTempbutton)
ON_MESSAGE(WM_RECEIVEDATA,OnReceiveData)
ON_BN_CLICKED(IDC_BUTTON_DRAW, OnButtonDraw)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Brow_Cur_Data message handlers
BOOL Brow_Cur_Data::OnInitDialog() 
{
	CDialog::OnInitDialog();
	ModifyStyleEx(0, WS_EX_APPWINDOW);
	IsFirstTime = TRUE;
	m_StrArray.SetSize(8);
	pBottomAxis = NULL;
	pSeries = NULL;
	pPreSeries = NULL;
	InitAxis();
	//InitGrid();
	for(int i =0;i < sizeof(PreXPoints)/sizeof(PreXPoints[0]);i++)
	{
		PreXPoints[i] = 0.0;
		PreYPoints[i] = 0.0;
	}
	for(int j =0;j < sizeof(XPoints)/sizeof(XPoints[0]);j++)
	{
		XPoints[j] = 0.0;
		YPoints[j] = 0.0;
	}
	
	for(int k = 0;k<10;k++)
	{
		CString str = "";
		str.Format("%d",k+1);
		m_Com_Channel.AddString(str);
		m_Com_Node.AddString(str);
	}
	
	
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
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
		strMsg.Format ("ָ��·��\\%s\\�����ڣ��Ƿ񴴽�?", m_strFolderPath); 
		if (AfxMessageBox(strMsg, MB_YESNO) == IDYES) 
		{ 
			if (!CreateDirectory(m_strFolderPath, NULL)) 
			{ 
				strMsg.Format ("����·��\\%s\\ʧ�ܣ����洢�ڸ�Ŀ¼��", m_strFolderPath); 
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
	//AfxMessageBox("");
	sqlite3_close(db);
}

void Brow_Cur_Data::OnTempbutton() 
{
	for(int i = 1; i < 3 ; i++)
	{
		for(int j = 1; j < 10 ; j++)
		{
			int temp1 = rand()%100;
			int temp2 = rand()%10;
			double temp3 = temp1/100.0+temp2;
			CString str = "";
			str.Format("%.2f",temp3);
			WriteToSQL(&str,i,j,NULL);
		}
	}
	AfxMessageBox("д��ɹ�");
	
	
}


void Brow_Cur_Data::WriteToSQL(CString *pDataStr, int Node, int Ch, sqlite3 *pdb)
{
/*CString m_strFolderPath="DataFolder" ;
// �ж�·���Ƿ���� 
if (!PathIsDirectory(m_strFolderPath) ) 
{ 
CString strMsg; 
strMsg.Format ("ָ��·��\"%s\"�����ڣ��Ƿ񴴽�?", m_strFolderPath); 
if (AfxMessageBox(strMsg, MB_YESNO) == IDYES) 
{ 
if (!CreateDirectory(m_strFolderPath, NULL ) ) 
{ 
strMsg.Format ("����·��\"%s\"ʧ�ܣ����洢�ڸ�Ŀ¼��", m_strFolderPath); 
AfxMessageBox(strMsg);
} 
} 
}

  sqlite3* db;
  int rc = sqlite3_open(m_strFolderPath + "\\data1.dat",&db);
  ASSERT(rc == SQLITE_OK);
  if(rc == SQLITE_OK)
  {
		//AfxMessageBox("�򿪳ɹ�");
		//SetWindowText("����д���ļ�");
		}
		else
		{	
		CString OpenErrorMsg = "";
		OpenErrorMsg.Format("���ݿ�򿪳���.\n����ԭ��:%s\n", sqlite3_errmsg(db));
		AfxMessageBox(OpenErrorMsg);
		return;
		}
		CString TableName = "";
		CString sqlcmd = "";
		char* ExeErrorMsg = "";
		TableName.Format("Node_%d_Ch_%d",Node,Ch);
		sqlcmd = "create table if not exists "+TableName+
		"(NUM integer primary key autoincrement, DataTime varchar(50),SensorVal real(15))";
		rc = sqlite3_exec(db, sqlcmd, NULL, NULL, &ExeErrorMsg);
		if(rc != SQLITE_OK)
		AfxMessageBox(ExeErrorMsg);
		CTime time = CTime::GetCurrentTime();
		CString Timestr = time.Format("%Y-%m-%d-%H-%M-%S");
		sqlcmd.Format("insert into '%s' (DataTime,SensorVal) values ('%s','%s')",TableName,Timestr,*pDataStr);
		rc = sqlite3_exec(db, sqlcmd, NULL, NULL, &ExeErrorMsg);
		if(rc != SQLITE_OK)
		AfxMessageBox(ExeErrorMsg);
		
		  //AfxMessageBox("");
	sqlite3_close(db);*/
	
	
}


LRESULT Brow_Cur_Data::OnReceiveData(WPARAM wParam,LPARAM lParam)
{
	//GetWindowText(WndText);
	CString str = _T("");
	str.Format("%d��ʵʱ��ⴰ��",(int)wParam);
	SetWindowText(str);
	m_StrArray.Copy(*(CStringArray*)lParam);//��Ҫ����������Ԫ���Ƿ��п�ֵ
	int nIndexNode = m_Com_Node.GetCurSel();
	int nIndexChannel = m_Com_Channel.GetCurSel();
	if((nIndexNode ==-1)||(nIndexChannel) ==-1)
	{
		SetWindowText(str+_T(" - ��ȷ�Ͻڵ��ͨ��"));
		Sleep(500);
		SetWindowText(str+_T(""));
		return 0;
	}
	CString m_Node = _T("");
	CString m_Channel = _T("");
	m_Com_Node.GetLBText( nIndexNode, m_Node);
	m_Com_Channel.GetLBText( nIndexChannel, m_Channel);
	if((m_Node.Compare(m_StrArray.GetAt(1))!=0)||(m_Channel.Compare(m_StrArray.GetAt(2))!=0))
	{
		SetWindowText(str +" - ��������");
		return 0;
	}
	/*CString str = "";
	str.Format("1-%s 2-%s 3-%s 4-%s 5-%s 6-%s 7-%s 8-%s",
	m_StrArray.GetAt(0),m_StrArray.GetAt(1),m_StrArray.GetAt(2),m_StrArray.GetAt(3),
	m_StrArray.GetAt(4),m_StrArray.GetAt(5),m_StrArray.GetAt(6),m_StrArray.GetAt(7));*/
	SetWindowText(str+" - ��ȡ������...");
	
	
	COleDateTime Time;
	Time.ParseDateTime(m_StrArray.GetAt(0));
	COleDateTime begin_date(1970, 1, 1, 0, 0, 0);
	COleDateTime pre_end_date(1970, 1, 1, 0, 0, sizeof(PreXPoints)/sizeof(PreXPoints[0]));
	COleDateTime end_date(1970, 1, 1, 0, 0, sizeof(XPoints)/sizeof(XPoints[0]));
	COleDateTime minValue = Time - end_date + begin_date;
	COleDateTime maxValue = Time + pre_end_date - begin_date;
	pBottomAxis->SetMinMax(CChartCtrl::DateToValue(minValue),CChartCtrl::DateToValue(maxValue));
	double Y = _ttol(m_StrArray.GetAt(5));
	double X = (DATE)Time;
	DrawData(pSeries,&X,&Y);
	DrawPreData(pPreSeries);
	return 0;
}

void Brow_Cur_Data::InitAxis()
{
	m_Chart.GetTitle()->AddString("ʵʱ���ͼ��");
	pBottomAxis = m_Chart.CreateDateTimeAxis(CChartCtrl::BottomAxis);
	//Sets the tick increment to 4 months (disable automatic tick increment)
	pBottomAxis->SetTickIncrement(false, CChartDateTimeAxis::tiSecond, 3);
	//Sets the tick label format for instance "Jan 2006"
	pBottomAxis->SetTickLabelFormat(false, _T("%H:%M:%S"));
	
	pBottomAxis->SetAutomatic(false); 
	pBottomAxis->GetLabel()->SetText("����");
	CChartStandardAxis* pLeftAxis = m_Chart.CreateStandardAxis(CChartCtrl::LeftAxis);
	pLeftAxis->SetAutomatic(true);
	//pLeftAxis->SetMinMax(0,20);
	pLeftAxis->SetTickIncrement(true,5.0);
	pLeftAxis->GetLabel()->SetText("����");
	pSeries = m_Chart.CreateLineSerie();
	pPreSeries = m_Chart.CreateLineSerie();
	pSeries->SetSmooth(false);
	m_Chart.EnableRefresh(false);
	m_Chart.SetBorderColor(RGB(0,0,255));
	m_Chart.SetBackColor(RGB(255,255,255));
	m_Chart.EnableRefresh(true);
	
}

void Brow_Cur_Data::DrawData(CChartLineSerie* pSerie,double* X,double* Y)
{
	COleDateTime begin_date(1970, 1, 1, 0, 0, 0),begin1_date(1970, 1, 1, 0, 0, 1);
	COleDateTime end_date(1970, 1, 1, 0, 0, sizeof(XPoints)/sizeof(XPoints[0]));
	COleDateTime temp_date;
	COleDateTime CurTime = COleDateTime::GetCurrentTime();
	int count = sizeof(XPoints)/sizeof(XPoints[0]);
	double CurTimeDouble = (DATE)CurTime;//ʱ��ת��Ϊdouble��
	double YValue = rand()%100/100.0+1;
	if(IsFirstTime)
	{
		temp_date =CurTime - end_date + begin_date;
		for(int i =0;i <count; i++)
		{
			YPoints[i] = 0.0;
			temp_date = temp_date + begin1_date - begin_date;//
			XPoints[i] = (DATE)temp_date;
		}
		IsFirstTime = FALSE;
	}
	
	int j = 0;
	for(;j <count-1;j++)
	{
		XPoints[j] = XPoints[j+1];
		YPoints[j] = YPoints[j+1];
	}
	XPoints[j] = *X;
	YPoints[j] = *Y;
	pSerie->SetPoints(XPoints,YPoints,count);
	//pSeries->AddPoints(&CurTimeDouble,&YValue,1);
	
	
}

void Brow_Cur_Data::OnButtonDraw() 
{
	// TODO: Add your control notification handler code here
	//DrawData(pSeries);
	Forecast();
}

void Brow_Cur_Data::DrawPreData(CChartLineSerie* pSerie)
{
	int count = sizeof(XPoints)/sizeof(XPoints[0]);
	int Precount = sizeof(PreXPoints)/sizeof(PreXPoints[0]);
	PreXPoints[0] = XPoints[count-1];
	PreYPoints[0] = YPoints[count-1];
	COleDateTime begin_date(1970, 1, 1, 0, 0, 0),end_date(1970, 1, 1, 0, 0, 1);
	COleDateTime NextDate(PreXPoints[0]);
	for(int i = 1;i < Precount;i++)
	{
		NextDate = NextDate + end_date - begin_date;
		PreXPoints[i] = (DATE)NextDate;
		PreYPoints[i] = rand()%10+rand()%150/100.0;//�������Ԥ��ֵ
	}
	pSerie->SetPoints(PreXPoints,PreYPoints,Precount);
}

void Brow_Cur_Data::InitGrid()
{
	RECT rctW,rctC,rct;
	CWnd* FieldImage = (CWnd*)GetDlgItem(IDC_FIELD_GRID);
	GetClientRect(&rctC);
	ClientToScreen(&rctC);
	GetWindowRect(&rctW);
	FieldImage->GetWindowRect(&rct);
	rct.right = rct.right - rctC.left + rctW.left;
	rct.bottom = rct.bottom - rctC.top + rctW.top;
	rct.left = rct.left - rctC.left + rctW.left;
	rct.top = rct.top - rctC.top + rctW.top;
	//GetClientRect(&rct);
	//rct.top = rct.top - 40;
	m_Grid.Create(0,rct,this);
	
	for(int l=0;l<sizeof(g_gi)/sizeof(grid_item);l++){
		m_Grid<<g_gi[l];
	}
	//m_Grid->Index[0] = gi_hdr("����");
	m_Grid->Index[1]->Text="Edit item";
	m_Grid->Index[2]->Text="Combo item";
	m_Grid->Index[3]->Text="Edit item";
	m_Grid->Index[4]->Text="Edit with custom";
	
	m_Grid->Index[5]->SubItem->Insert("Text1");
	m_Grid->Index[5]->SubItem->Insert("Text2");
	m_Grid->Index[5]->SubItem->Insert("Text3");
	m_Grid->Index[5]->SubItem->Select=0;
	
	m_Grid->Index[7]->Text="Edit item";
	m_Grid->Index[8]->Text="Edit readonly";
	m_Grid->Index[9]->Text="Edit number";
	
	m_Grid->Index[10]->SubItem->Insert("Text");
	m_Grid->Index[10]->SubItem->Select=0;
	
	m_Grid->Index[11]->Text="Password";
}



void Brow_Cur_Data::Forecast()
{
	//clc
	//clear
	
	//%% �����������
	//load traffic_flux input output input_test output_test
	double input[input_row][input_col]={{66,64,60,58},

{64,60,58,17},

{60,58,17,49},

{58,17,49,34},

{17,49,34,17},

{49,34,17,8},

{34,17,8,53},

{17,8,53,15},

{8,53,15,15},

{53,15,15,45},

{15,15,45,57},

{15,45,57,33},

{45,57,33,42},

{57,33,42,8},

{33,42,8,52},

{42,8,52,24},

{8,52,24,29},

{52,24,29,-13},

{24,29,-13,37},

{29,-13,37,37},

{-13,37,37,4},

{37,37,4,32},

{37,4,32,38},

{4,32,38,68},

{32,38,68,77},

{38,68,77,95},

{68,77,95,119},

{77,95,119,161},

{95,119,161,184},

{119,161,184,276},

{161,184,276,247},

{184,276,247,251},

{276,247,251,193},

{247,251,193,226},

{251,193,226,213},

{193,226,213,195},

{226,213,195,182},

{213,195,182,166},

{195,182,166,188},

{182,166,188,149},

{166,188,149,132},

{188,149,132,167},

{149,132,167,181},

{132,167,181,203},

{167,181,203,219},

{181,203,219,226},

{203,219,226,216},

{219,226,216,234},

{226,216,234,197},

{216,234,197,219},

{234,197,219,230},

{197,219,230,247},

{219,230,247,238},

{230,247,238,259},

{247,238,259,270},

{238,259,270,232},

{259,270,232,202},

{270,232,202,243},

{232,202,243,223},

{202,243,223,202},

{243,223,202,235},

{223,202,235,184},

{202,235,184,215},

{235,184,215,217},

{184,215,217,209},

{215,217,209,199},

{217,209,199,197},

{209,199,197,226},

{199,197,226,217},

{197,226,217,254},

{226,217,254,243},

{217,254,243,281},

{254,243,281,285},

{243,281,285,285},

{281,285,285,251},

{285,285,251,288},

{285,251,288,236},

{251,288,236,266},

{288,236,266,214},

{236,266,214,213},

{266,214,213,186},

{214,213,186,209},

{213,186,209,176},

{186,209,176,163},

{209,176,163,199},

{176,163,199,171},

{163,199,171,170},

{199,171,170,134},

{171,170,134,128},

{170,134,128,72},

{134,128,72,113},

{128,72,113,94},

{69,41,53,48},

{41,53,48,42},

{53,48,42,25},

{48,42,25,21},

{42,25,21,32},

{25,21,32,16},

{21,32,16,52},

{32,16,52,63}

};
	double input_test[inputtest_row][input_col]={{28,71,21,69},

{71,21,69,34},

{21,69,34,11},

{69,34,11,27},

{34,11,27,49},

{11,27,49,50},

{27,49,50,36},

{49,50,36,45},

{50,36,45,58},

{36,45,58,9},

{45,58,9,22},

{58,9,22,5},

{9,22,5,12},

{22,5,12,42},

{5,12,42,38},

{12,42,38,44},

{42,38,44,23},

{38,44,23,-11},

{44,23,-11,44},

{23,-11,44,41},

{-11,44,41,14},

{44,41,14,33},

{41,14,33,77},

{14,33,77,78},

{33,77,78,103},

{77,78,103,96},

{78,103,96,136},

{103,96,136,179},

{96,136,179,199},

{136,179,199,265},

{179,199,265,238},

{199,265,238,234},

{265,238,234,201},

{238,234,201,179},

{234,201,179,194},

{201,179,194,182},

{179,194,182,203},

{194,182,203,197},

{182,203,197,183},

{203,197,183,144},

{197,183,144,129},

{183,144,129,154},

{144,129,154,159},

{129,154,159,217},

{154,159,217,239},

{159,217,239,218},

{217,239,218,241},

{239,218,241,239},

{218,241,239,214},

{241,239,214,224}

};
	double output[output_row][output_col]={{17},

{49},

{34},

{17},

{8},

{53},

{15},

{15},

{45},

{57},

{33},

{42},

{8},

{52},

{24},

{29},

{-13},

{37},

{37},

{4},

{32},

{38},

{68},

{77},

{95},

{119},

{161},

{184},

{276},

{247},

{251},

{193},

{226},

{213},

{195},

{182},

{166},

{188},

{149},

{132},

{167},

{181},

{203},

{219},

{226},

{216},

{234},

{197},

{219},

{230},

{247},

{238},

{259},

{270},

{232},

{202},

{243},

{223},

{202},

{235},

{184},

{215},

{217},

{209},

{199},

{197},

{226},

{217},

{254},

{243},

{281},

{285},

{285},

{251},

{288},

{236},

{266},

{214},

{213},

{186},

{209},

{176},

{163},

{199},

{171},

{170},

{134},

{128},

{72},

{113},

{94},

{78},

{42},

{25},

{21},

{32},

{16},

{52},

{63},

{7}

};
	double output_test[outputtest_row][output_col]={{34},

{11},

{27},

{49},

{50},

{36},

{45},

{58},

{9},

{22},

{5},

{12},

{42},

{38},

{44},

{23},

{-11},

{44},

{41},

{14},

{33},

{77},

{78},

{103},

{96},

{136},

{179},

{199},

{265},

{238},

{234},

{201},

{179},

{194},

{182},

{203},

{197},

{183},

{144},

{129},

{154},

{159},

{217},

{239},

{218},

{241},

{239},

{214},

{224},

{240}

};
	int M=input_col;//sizeof(input[0])/sizeof(input[0][0]);//M=size(input,2); %����ڵ����
	int N=output_col;//sizeof(output[0])/sizeof(output[0][0]);//N=size(output,2); %����ڵ����
	//Forecast forecast;
	//int n=6; //%���νڵ����
	double lr1=0.01; //%ѧϰ����
	double lr2=0.001; //%ѧϰ����
	//int maxgen=100; //%��������
	
	//%Ȩֵ��ʼ��
	//Wjk=randn(n,M);
	//n=20;
	//M=20;
	int i,j,k,kk,kkk;
	/*CArray <double,double&> m_Wjk;
	typedef CArray <double,double&> DArray;
	//DArray m_Wjk;
	m_Wjk.SetSize(M);//�൱�����������
	CArray <DArray*,DArray*> Wjk;
	Wjk.SetSize(n);//�൱�����������
	srand((unsigned)time( NULL ));
	double value=0.0;
	//double &arg_value = value;
	CString str = "";
	CFile pf;
	pf.Open("CArry.txt",CFile::modeCreate|CFile::modeWrite);
	for(i = 0;i <n;i++)
	{
	m_Wjk.RemoveAll();
	for(j = 0;j < M;j++)
	{
	value=gaussrand(0,1);//randn(0,1,-2,2);
	m_Wjk.SetAt(j,value);
	//str.Format("%5.3f ",m_Wjk.GetAt(j));
	//pf.Write(str,str.GetLength());
	}
	//pf.Write("\r\n",4);
	Wjk.SetAt(i,&m_Wjk);
	}
	pf.Close();
	CArray <DArray*,DArray*> Wjk_1;
	Wjk_1.SetSize(n);
	CArray <DArray*,DArray*> Wjk_2;
	Wjk_2.SetSize(n);
	Wjk_1.Copy(Wjk);//Wjk_1=Wjk;
	Wjk_2.Copy(Wjk_1);//Wjk_2=Wjk_1;
	m_Wjk.RemoveAll();
	m_Wjk.SetSize(n);//�൱�����������
	CArray <DArray*,DArray*> Wij;
	Wij.SetSize(N);//�൱�����������
	for(i = 0;i <N;i++)//Wij=randn(N,n);		
	{
	m_Wjk.RemoveAll();
	for(j = 0;j < n;j++)
	{
	value=gaussrand(0,1);//randn(0,1,-2,2);
	m_Wjk.SetAt(j,value);
	//str.Format("%5.3f ",m_Wjk.GetAt(j));
	//pf.Write(str,str.GetLength());
	}
	//pf.Write("\r\n",4);
	Wij.SetAt(i,&m_Wjk);
	}	
	CArray <DArray*,DArray*> Wij_1;
	Wij_1.SetSize(n);
	CArray <DArray*,DArray*> Wij_2;
	Wij_2.SetSize(n);
	Wij_1.Copy(Wij);//Wij_1=Wij;
	Wij_2.Copy(Wij_1);//Wij_2=Wij_1;
	m_Wjk.RemoveAll();
	m_Wjk.SetSize(n);//�൱�����������
	CArray <DArray*,DArray*> a;
	a.SetSize(1);//�൱�����������
	for(i = 0;i <1;i++)//a=randn(1,n);		
	{
	m_Wjk.RemoveAll();
	for(j = 0;j < n;j++)
	{
	value=gaussrand(0,1);
	m_Wjk.SetAt(j,value);
	//str.Format("%5.3f ",m_Wjk.GetAt(j));
	//pf.Write(str,str.GetLength());
	}
	//pf.Write("\r\n",4);
	a.SetAt(i,&m_Wjk);
	}	
	CArray <DArray*,DArray*> a_1;
	a_1.SetSize(n);
	CArray <DArray*,DArray*> a_2;
	a_2.SetSize(n);
	a_1.Copy(a);//a_1=a;
	a_2.Copy(a_1);//a_2=a_1;
	m_Wjk.RemoveAll();
	m_Wjk.SetSize(n);//�൱�����������
	CArray <DArray*,DArray*> b;
	b.SetSize(1);//�൱�����������
	for(i = 0;i <1;i++)//b=randn(1,n);
	{
	m_Wjk.RemoveAll();
	for(j = 0;j < n;j++)
	{
	value=gaussrand(0,1);
	m_Wjk.SetAt(j,value);
	//str.Format("%5.3f ",m_Wjk.GetAt(j));
	//pf.Write(str,str.GetLength());
	}
	//pf.Write("\r\n",4);
	b.SetAt(i,&m_Wjk);
	}
	CArray <DArray*,DArray*> b_1;
	b_1.SetSize(n);
	CArray <DArray*,DArray*> b_2;
	b_2.SetSize(n);
	b_1.Copy(b);//b_1=b;
	b_2.Copy(b_1);//b_2=b_1;
	
	  
		
		  
			//%�ڵ��ʼ��
			m_Wjk.RemoveAll();
			m_Wjk.SetSize(N);//�൱�����������
			CArray <DArray*,DArray*> y;
			y.SetSize(1);//�൱�����������
			value = 0.0;
			for(i = 0;i <1;i++)//y=zeros(1,N);
			{
			m_Wjk.RemoveAll();
			for(j = 0;j < N;j++)
			{
			m_Wjk.SetAt(j,value);
			//str.Format("%5.3f ",m_Wjk.GetAt(j));
			//pf.Write(str,str.GetLength());
			}
			//pf.Write("\r\n",4);
			y.SetAt(i,&m_Wjk);
			}
			m_Wjk.RemoveAll();
			m_Wjk.SetSize(n);//�൱�����������
			CArray <DArray*,DArray*> net;
			net.SetSize(1);//�൱�����������
			for(i = 0;i <1;i++)//net=zeros(1,n);
			{
			m_Wjk.RemoveAll();
			for(j = 0;j < n;j++)
			{
			m_Wjk.SetAt(j,value);
			//str.Format("%5.3f ",m_Wjk.GetAt(j));
			//pf.Write(str,str.GetLength());
			}
			//pf.Write("\r\n",4);
			net.SetAt(i,&m_Wjk);
			}
			m_Wjk.RemoveAll();
			m_Wjk.SetSize(n);//�൱�����������
			CArray <DArray*,DArray*> net_ab;
			net_ab.SetSize(1);//�൱�����������
			for(i = 0;i <1;i++)//net_ab=zeros(1,n);
			{
			m_Wjk.RemoveAll();
			for(j = 0;j < n;j++)
			{
			m_Wjk.SetAt(j,value);
			//str.Format("%5.3f ",m_Wjk.GetAt(j));
			//pf.Write(str,str.GetLength());
			}
			//pf.Write("\r\n",4);
			net_ab.SetAt(i,&m_Wjk);
			}
			
			  
				//%Ȩֵѧϰ������ʼ��
				m_Wjk.RemoveAll();
				m_Wjk.SetSize(M);//�൱�����������
				CArray <DArray*,DArray*> d_Wjk;
				d_Wjk.SetSize(n);//�൱�����������
				for(i = 0;i <n;i++)//d_Wjk=zeros(n,M);
				{
				m_Wjk.RemoveAll();
				for(j = 0;j < M;j++)
				{
				m_Wjk.SetAt(j,value);
				//str.Format("%5.3f ",m_Wjk.GetAt(j));
				//pf.Write(str,str.GetLength());
				}
				//pf.Write("\r\n",4);
				d_Wjk.SetAt(i,&m_Wjk);
				}
				m_Wjk.RemoveAll();
				m_Wjk.SetSize(n);//�൱�����������
				CArray <DArray*,DArray*> d_Wij;
				d_Wij.SetSize(N);//�൱�����������
				for(i = 0;i <N;i++)//d_Wij=zeros(N,n);
				{
				m_Wjk.RemoveAll();
				for(j = 0;j < n;j++)
				{
				m_Wjk.SetAt(j,value);
				//str.Format("%5.3f ",m_Wjk.GetAt(j));
				//pf.Write(str,str.GetLength());
				}
				//pf.Write("\r\n",4);
				d_Wij.SetAt(i,&m_Wjk);
				}
				m_Wjk.RemoveAll();
				m_Wjk.SetSize(n);//�൱�����������
				CArray <DArray*,DArray*> d_a;
				d_a.SetSize(1);//�൱�����������
				for(i = 0;i <1;i++)//d_a=zeros(1,n);
				{
				m_Wjk.RemoveAll();
				for(j = 0;j < n;j++)
				{
				m_Wjk.SetAt(j,value);
				//str.Format("%5.3f ",m_Wjk.GetAt(j));
				//pf.Write(str,str.GetLength());
				}
				//pf.Write("\r\n",4);
				d_a.SetAt(i,&m_Wjk);
				}
				m_Wjk.RemoveAll();
				m_Wjk.SetSize(n);//�൱�����������
				CArray <DArray*,DArray*> d_b;
				d_b.SetSize(1);//�൱�����������
				for(i = 0;i <1;i++)//d_b=zeros(1,n);
				{
				m_Wjk.RemoveAll();
				for(j = 0;j < n;j++)
				{
				m_Wjk.SetAt(j,value);
				//str.Format("%5.3f ",m_Wjk.GetAt(j));
				//pf.Write(str,str.GetLength());
				}
				//pf.Write("\r\n",4);
				d_b.SetAt(i,&m_Wjk);
	}*/

	/*	double input[input_row][input_col]={0.0};
	double output[output_row][output_col]={0.0};
	double input_test[92][input_col]={0.0};
	double output_test[92][output_col]={0.0};
	int M=input_col;//sizeof(input[0])/sizeof(input[0][0]);//M=size(input,2); %����ڵ����
	int N=output_col;//sizeof(output[0])/sizeof(output[0][0]);//N=size(output,2); %����ڵ����
	//Forecast forecast;
	//int n=6; //%���νڵ����
	double lr1=0.01; //%ѧϰ����
	double lr2=0.001; //%ѧϰ����
int maxgen=100; //%��������*/

//%Ȩֵ��ʼ��
//Wjk=randn(n,M);
//	int M=input_col;//sizeof(input[0])/sizeof(input[0][0]);//M=size(input,2); %����ڵ����
//	int N=output_col;//sizeof(output[0])/sizeof(output[0][0]);//N=size(output,2); %����ڵ����
//n=20;
//M=20;
//int i,j,k;
//CArray <double,double&> m_Wjk;
//typedef CArray <double,double&> DArray;
//DArray m_Wjk;
//m_Wjk.SetSize(M);//�൱�����������
//Wjk.SetSize(n);//�൱�����������
srand((unsigned)time( NULL ));
double value=0.0;
//double &arg_value = value;
CString str = "";
//CFile pf;
//pf.Open("CArry.txt",CFile::modeCreate|CFile::modeWrite);
double Wjk[n][input_col] = {{0.0}};//CArray <DArray*,DArray*> Wjk;
double Wjk_1[n][input_col] = {{0.0}};
double Wjk_2[n][input_col] = {{0.0}};
for(i = 0;i <n;i++)
{
	//m_Wjk.RemoveAll();
	for(j = 0;j < input_col;j++)
	{
		//value=gaussrand(0,1);//randn(0,1,-2,2);
		Wjk[i][j] = randn(2);//gaussrand();//value;
		Wjk_1[i][j] = Wjk[i][j];
		Wjk_2[i][j] = Wjk_1[i][j];
		//m_Wjk.SetAt(j,value);
		//str.Format("%5.3f ",m_Wjk.GetAt(j));
		//pf.Write(str,str.GetLength());
	}
	//pf.Write("\r\n",4);
	//Wjk.SetAt(i,&m_Wjk);
}
//pf.Close();
//CArray <DArray*,DArray*> Wjk_1;
//Wjk_1.SetSize(n);
//CArray <DArray*,DArray*> Wjk_2;
//Wjk_2.SetSize(n);
//Wjk_1.Copy(Wjk);//Wjk_1=Wjk;
//Wjk_2.Copy(Wjk_1);//Wjk_2=Wjk_1;
//m_Wjk.RemoveAll();
//m_Wjk.SetSize(n);//�൱�����������
//CArray <DArray*,DArray*> Wij;
//Wij.SetSize(N);//�൱�����������
double Wij[output_col][n] = {{0.0}};//CArray <DArray*,DArray*> Wjk;
double Wij_1[output_col][n] = {{0.0}};
double Wij_2[output_col][n] = {{0.0}};
for(i = 0;i <output_col;i++)
{
	//m_Wjk.RemoveAll();
	for(j = 0;j < n;j++)
	{
		//value=gaussrand(0,1);//randn(0,1,-2,2);
		Wij[i][j] = randn(2);//gaussrand();//value;
		Wij_1[i][j] = Wij[i][j];
		Wij_2[i][j] = Wij_1[i][j];
		//m_Wjk.SetAt(j,value);
		//str.Format("%5.3f ",m_Wjk.GetAt(j));
		//pf.Write(str,str.GetLength());
	}
	//pf.Write("\r\n",4);
	//Wjk.SetAt(i,&m_Wjk);
}

double a[1][n] = {{0.0}};//CArray <DArray*,DArray*> Wjk;
double a_1[1][n] = {{0.0}};
double a_2[1][n] = {{0.0}};
for(i = 0;i <1;i++)
{
	//m_Wjk.RemoveAll();
	for(j = 0;j < n;j++)
	{
		//value=gaussrand(0,1);//randn(0,1,-2,2);
		a[i][j] = randn(2);//gaussrand();//value;
		a_1[i][j] = a[i][j];
		a_2[i][j] = a_1[i][j];
		//m_Wjk.SetAt(j,value);
		//str.Format("%5.3f ",m_Wjk.GetAt(j));
		//pf.Write(str,str.GetLength());
	}
	//pf.Write("\r\n",4);
	//Wjk.SetAt(i,&m_Wjk);
}

double b[1][n] = {{0.0}};//CArray <DArray*,DArray*> Wjk;
double b_1[1][n] = {{0.0}};
double b_2[1][n] = {{0.0}};
for(i = 0;i <1;i++)
{
	//m_Wjk.RemoveAll();
	for(j = 0;j < n;j++)
	{
		//value=gaussrand(0,1);//randn(0,1,-2,2);
		b[i][j] = randn(2);//gaussrand();//value;
		b_1[i][j] = b[i][j];
		b_2[i][j] = b_1[i][j];
		//m_Wjk.SetAt(j,value);
		//str.Format("%5.3f ",m_Wjk.GetAt(j));
		//pf.Write(str,str.GetLength());
	}
	//pf.Write("\r\n",4);
	//Wjk.SetAt(i,&m_Wjk);
}





//%�ڵ��ʼ��
//	m_Wjk.RemoveAll();
//	m_Wjk.SetSize(N);//�൱�����������
//	CArray <DArray*,DArray*> y;
//	y.SetSize(1);//�൱�����������
//	value = 0.0;
double y[1][output_col] = {{0.0}};
double net[1][n]={{0.0}};
double net_ab[1][n] = {{0.0}};

/*	for(i = 0;i <1;i++)//y=zeros(1,N);
{
//m_Wjk.RemoveAll();
for(j = 0;j < output_col;j++)
{
//m_Wjk.SetAt(j,value);
//str.Format("%5.3f ",m_Wjk.GetAt(j));
//pf.Write(str,str.GetLength());
}
//pf.Write("\r\n",4);
//y.SetAt(i,&m_Wjk);
}
m_Wjk.RemoveAll();
m_Wjk.SetSize(n);//�൱�����������
CArray <DArray*,DArray*> net;
net.SetSize(1);//�൱�����������
for(i = 0;i <1;i++)//net=zeros(1,n);
{
m_Wjk.RemoveAll();
for(j = 0;j < n;j++)
{
m_Wjk.SetAt(j,value);
//str.Format("%5.3f ",m_Wjk.GetAt(j));
//pf.Write(str,str.GetLength());
}
//pf.Write("\r\n",4);
net.SetAt(i,&m_Wjk);
}
m_Wjk.RemoveAll();
m_Wjk.SetSize(n);//�൱�����������
CArray <DArray*,DArray*> net_ab;
net_ab.SetSize(1);//�൱�����������
for(i = 0;i <1;i++)//net_ab=zeros(1,n);
{
m_Wjk.RemoveAll();
for(j = 0;j < n;j++)
{
m_Wjk.SetAt(j,value);
//str.Format("%5.3f ",m_Wjk.GetAt(j));
//pf.Write(str,str.GetLength());
}
//pf.Write("\r\n",4);
net_ab.SetAt(i,&m_Wjk);
}
*/
double d_Wjk[n][input_col] = {{0.0}};
double d_Wij[output_col][n] = {{0.0}};
double d_a[1][n] = {{0.0}};
double d_b[1][n] = {{0.0}};

//%Ȩֵѧϰ������ʼ��
/*	m_Wjk.RemoveAll();
m_Wjk.SetSize(M);//�൱�����������
CArray <DArray*,DArray*> d_Wjk;
d_Wjk.SetSize(n);//�൱�����������
for(i = 0;i <n;i++)//d_Wjk=zeros(n,M);
{
m_Wjk.RemoveAll();
for(j = 0;j < M;j++)
{
m_Wjk.SetAt(j,value);
//str.Format("%5.3f ",m_Wjk.GetAt(j));
//pf.Write(str,str.GetLength());
}
//pf.Write("\r\n",4);
d_Wjk.SetAt(i,&m_Wjk);
}
m_Wjk.RemoveAll();
m_Wjk.SetSize(n);//�൱�����������
CArray <DArray*,DArray*> d_Wij;
d_Wij.SetSize(N);//�൱�����������
for(i = 0;i <N;i++)//d_Wij=zeros(N,n);
{
m_Wjk.RemoveAll();
for(j = 0;j < n;j++)
{
m_Wjk.SetAt(j,value);
//str.Format("%5.3f ",m_Wjk.GetAt(j));
//pf.Write(str,str.GetLength());
}
//pf.Write("\r\n",4);
d_Wij.SetAt(i,&m_Wjk);
}
m_Wjk.RemoveAll();
m_Wjk.SetSize(n);//�൱�����������
CArray <DArray*,DArray*> d_a;
d_a.SetSize(1);//�൱�����������
for(i = 0;i <1;i++)//d_a=zeros(1,n);
{
m_Wjk.RemoveAll();
for(j = 0;j < n;j++)
{
m_Wjk.SetAt(j,value);
//str.Format("%5.3f ",m_Wjk.GetAt(j));
//pf.Write(str,str.GetLength());
}
//pf.Write("\r\n",4);
d_a.SetAt(i,&m_Wjk);
}
m_Wjk.RemoveAll();
m_Wjk.SetSize(n);//�൱�����������
CArray <DArray*,DArray*> d_b;
d_b.SetSize(1);//�൱�����������
for(i = 0;i <1;i++)//d_b=zeros(1,n);
{
m_Wjk.RemoveAll();
for(j = 0;j < n;j++)
{
m_Wjk.SetAt(j,value);
//str.Format("%5.3f ",m_Wjk.GetAt(j));
//pf.Write(str,str.GetLength());
}
//pf.Write("\r\n",4);
d_b.SetAt(i,&m_Wjk);
}
*/


//%% ����������ݹ�һ��
double tempmax = 0.0,tempmin = 0.0;
double input_max[input_col] = {{0.0}};
double input_min[input_col] = {{0.0}};
for(i = 0;i <input_col;i++)//[inputn,inputps]=mapminmax(input');
{
	tempmax=input[0][i];
	tempmin=input[0][i];
	//m_Wjk.RemoveAll();
	for(j = 0;j < input_row;j++)
	{
		if(input[j][i] > tempmax)
			tempmax = input[j][i];
		if(input[j][i] < tempmin)
			tempmin = input[j][i];
	}
	input_max[i] = tempmax;
	input_min[i] = tempmin;
	for(j = 0;j < input_row;j++)
	{
		input[j][i] = 2*(input[j][i] - input_min[i])/(input_max[i] - input_min[i])-1;
	}
}


double output_max[output_col] = {{0.0}};
double output_min[output_col] = {{0.0}};
for(i = 0;i <output_col;i++)//[outputn,outputps]=mapminmax(output');
{
	tempmax=output[0][i];
	tempmin=output[0][i];
	//m_Wjk.RemoveAll();
	for(j = 0;j < output_row;j++)
	{
		if(output[j][i] > tempmax)
			tempmax = output[j][i];
		if(output[j][i] < tempmin)
			tempmin = output[j][i];
	}
	output_max[i] = tempmax;
	output_min[i] = tempmin;
	for(j = 0;j < output_row;j++)
	{
		output[j][i] = 2*(output[j][i] - output_min[i])/(output_max[i] - output_min[i])-1;
	}
}


/*double input_max[input_col] = {{0.0}};
int tempmax=0,tempmin = 0;
for(i = 0;i <input_col;i++)//[inputn,inputps]=mapminmax(input');
{
tempmax=0;
//m_Wjk.RemoveAll();
for(j = 0;j < input_row;j++)
{
if(abs(input[i][j] > abs(tempmax)))
tempmax = input[i][j];
//m_Wjk.SetAt(j,0.0);
//str.Format("%5.3f ",m_Wjk.GetAt(j));
//pf.Write(str,str.GetLength());
}
input_max[i] = tempmax;
for(j = 0;j < input_row;j++)
{
input[i][j] = input[i][j]/input_max[i];
//m_Wjk.SetAt(j,0.0);
//str.Format("%5.3f ",m_Wjk.GetAt(j));
//pf.Write(str,str.GetLength());
}
//pf.Write("\r\n",4);
//d_b.SetAt(i,&m_Wjk);
}
double output_max[output_col] = {{0.0}};
for(i = 0;i <output_col;i++)//[outputn,outputps]=mapminmax(output'); 
{
tempmax=0;
//m_Wjk.RemoveAll();
for(j = 0;j < output_row;j++)
{
if(abs(output[i][j] > abs(tempmax)))
tempmax = output[i][j];
//m_Wjk.SetAt(j,0.0);
//str.Format("%5.3f ",m_Wjk.GetAt(j));
//pf.Write(str,str.GetLength());
}
output_max[i] = tempmax;
for(j = 0;j < output_row;j++)
{
output[i][j] = output[i][j]/output_max[i];
//m_Wjk.SetAt(j,0.0);
//str.Format("%5.3f ",m_Wjk.GetAt(j));
//pf.Write(str,str.GetLength());
}
//pf.Write("\r\n",4);
//d_b.SetAt(i,&m_Wjk);
}
*/
//inputn=inputn';
//outputn=outputn';

//%% ����ѵ��
//for i=1:maxgen
double x[input_col] = {{0.0}};
double yqw[output_col] = {{0.0}};
double error[maxgen] = {{0.0}};
double temp = 0.0;
for(i = 0; i < maxgen; i++)
{
	//%����ۼ�
	error[i]=0.0;
	for(kk = 0;kk <input_row;kk++)
	{
		for(kkk = 0;kkk <input_col ; kkk++)//x=inputn(kk,:);
		{
			x[kkk] = input[kk][kkk];
		}
		for(kkk = 0;kkk <output_col ; kkk++)//yqw=outputn(kk,:);
			
		{
			yqw[kkk] = output[kk][kkk];
		}
		
		for(j = 0;j <n; j++ )
		{
			for(k = 0;k<input_col ; k++)
			{
				net[0][j]=net[0][j]+Wjk[j][k]*x[k];
				net_ab[0][j]=(net[0][j]-b[0][j])/a[0][j];
			}
			temp = mymorlet(net_ab[0][j]);
			for(k = 0;k<output_col ; k++)
			{
				y[0][k] = y[0][k] + Wij[k][j]*temp;
			}
		}
		for(j = 0;j <output_col ;j++)
		{
			temp = temp+abs(yqw[j] - y[0][j]);
		}
		error[i] = error[i]+temp;
		for(j = 0;j < n;j++)
		{
			temp = mymorlet(net_ab[0][j]);
			for(k = 0;k < output_col;k++)
			{
				d_Wij[k][j] = d_Wij[k][j] - (yqw[k] - y[0][k])*temp;
			}
			temp = d_mymorlet(net_ab[0][j]);
			for(k = 0;k< input_col ;k++)
			{
				for(kkk = 0; kkk< output_col ;kkk++)
				{
					d_Wjk[j][k] = d_Wjk[j][k] + (yqw[kkk] - y[0][kkk])*Wij[kkk][j];
				}
				d_Wjk[j][k] = -d_Wjk[j][k]*temp*x[k]/a[0][j];
			}
			for(k = 0;k <output_col ;k++)
			{
				d_b[0][j] = d_b[0][j] + (yqw[k] - y[0][k])*Wij[k][j];
			}
			d_b[0][j] = d_b[0][j]*temp/a[0][j];
			for(k = 0; k <output_col; k++)
			{
				d_a[0][j] = d_a[0][j] + (yqw[k] - y[0][k])*Wij[k][j];
			}
			d_a[0][j] = d_a[0][j]*temp*((net[0][j] - b[0][j])/b[0][j])/a[0][j];
		}
		
		
		///Ȩֵ��������
		for(j = 0;j <n;j++)
		{
			for(k = 0;k < input_col;k++)
			{
				Wjk[j][k] = Wjk[j][k] - lr1*d_Wjk[j][k];//
				d_Wjk[j][k] = 0.0;
				Wjk_1[j][k] =Wjk[j][k];
				Wjk_2[j][k] =Wjk_1[j][k];
			}
			b[0][j] = b[0][j] - lr2*d_b[0][j];
			a[0][j] = a[0][j] - lr2*d_a[0][j];
			d_a[0][j] = 0.0;
			d_b[0][j] = 0.0;
			net[0][j] = 0.0;
			net_ab[0][j] = 0.0;
			a_1[0][j] = a[0][j];
			a_2[0][j] = a_1[0][j];
			b_1[0][j] = b[0][j];
			b_1[0][j] = b_1[0][j];
		}
		for(j = 0;j <output_col;j++)
		{
			for(k = 0;k < n;k++)
			{
				Wij[j][k] = Wij[j][k] - lr1*d_Wij[j][k];//value;
				d_Wij[j][k] = 0.0;
				Wij_1[j][k] =Wij[j][k];
				Wij_2[j][k] =Wij_1[j][k];
			}
			y[0][j] = 0.0;		
		}	
	}//end
	//temp=mymorlet(net_ab(j));
	//for k=1:N
	//y=y+Wij(k,j)*temp;   %С������
}//end


////// ����Ԥ��
//////Ԥ�������һ��
double inputtest_max[input_col] = {{0.0}};
double inputtest_min[input_col] = {{0.0}};
for(i = 0;i <input_col;i++)//[inputn,inputps]=mapminmax(input');
{
	tempmax=input_test[0][i];
	tempmin=input_test[0][i];
	//m_Wjk.RemoveAll();
	for(j = 0;j < inputtest_row;j++)
	{
		if(input_test[j][i] > tempmax)
			tempmax = input_test[j][i];
		if(input_test[j][i] < tempmin)
			tempmin = input_test[j][i];
	}
	inputtest_max[i] = tempmax;
	inputtest_min[i] = tempmin;
	for(j = 0;j < inputtest_row;j++)
	{
		input_test[j][i] = 2*(input_test[j][i] - inputtest_min[i])/(inputtest_max[i] - inputtest_min[i])-1;
	}
}//x=mapminmax('apply',input_test',inputps);
//x=x';

/////����Ԥ��
double x_test[input_col] = {{0.0}};
double yuce[1][inputtest_row] = {{0.0}};
for(i = 0; i <inputtest_row; i++)
{
	for(j = 0; j <input_col; j++)
	{
		x_test[j] = input_test[i][j];
	}
	for(j = 0; j <n; j++)
	{
		for(k = 0; k < input_col; k++)
		{
			net[0][j] = net[0][j] + Wjk[j][k]*x_test[k];
			net_ab[0][j] = (net[0][j] - b[0][j])/a[0][j];
		}
		temp = mymorlet(net_ab[0][j]);
		for(k = 0; k < output_col; k++)
		{
			y[0][k] = y[0][k] + Wij[k][j]*temp;
		}
	}
	yuce[0][i] = y[0][k-1];/////////////////////////
	for(j = 0;j <output_col;j++)
	{
		y[0][j] = 0.0;
	}
	for(j = 0;j < n;j++)
	{
		net[0][j] = 0.0;
		net_ab[0][j] = 0.0;
	}
}

double yun[outputtest_row] = {{0.0}};
for(i = 0; i < outputtest_row; i ++)
{
	yun[i] = (yuce[0][i]+1)/2*(output_max[0] - output_min[0]) + output_min[0];
}

COleDateTime begin_date(1970, 1, 1, 0, 0, 0),end_date(1970, 1, 1, 0, 0, 1);
COleDateTime temp_date;
COleDateTime CurTime = COleDateTime::GetCurrentTime();
double CurTimeDouble = (DATE)CurTime;//ʱ��ת��Ϊdouble��
double Time[outputtest_row] = {{0.0}};
double output_test_[outputtest_row] = {{0.0}};
for(i = 0; i <outputtest_row; i++)
{
	//int count = sizeof(XPoints)/sizeof(XPoints[0]);
	//double YValue = rand()%100/100.0+1;
	//if(IsFirstTime)
	//{
	CurTime =CurTime + end_date - begin_date;
	Time[i] = (DATE)CurTime;
	output_test_[i] = output_test[i][0];
	//pSeries->SetPoints(&yun[0][i],&CurTimeDouble,1);
	//Invalidate();
}
pBottomAxis->SetMinMax(CChartCtrl::DateToValue(Time[0]),CChartCtrl::DateToValue(Time[outputtest_row-1]));
pBottomAxis->SetTickIncrement(false, CChartDateTimeAxis::tiSecond, 10);
//CChartLineSerie *tempSeries = m_Chart.CreateLineSerie();
pPreSeries->SetPoints(Time,output_test_,outputtest_row);
pSeries->SetPoints(Time,yun,outputtest_row);
}

