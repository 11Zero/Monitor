// Brow_Cur_Data.cpp : implementation file
//

#include "stdafx.h"
#include "Bridge_485.h"
#include "Bridge_485Dlg.h"
#include "Brow_Cur_Data.h"
#include "CChart.h"
#include "Forecast.h"
#include <afxtempl.h>//使用CArray
//#include <math.h>
//#include <stdlib.h>
//#include <time.h>

#define input_col 1 
#define input_row 20 
#define output_col 1 
#define output_row 20 
#define n 2  //隐形节点个数
#define inputtest_row 3
#define outputtest_row 3 
#define maxgen 10 //迭代次数

double Input[input_row][input_col];
double Output[inputtest_row][input_col];
double PreOutput[outputtest_row][output_col];
double PreInput[output_row][output_col];
double PreXPoints[outputtest_row+1];//缓存个预测图点
double PreYPoints[outputtest_row+1];//缓存个预测图点

static const int AXIS_GAP = 10;
static const int ADDITIONAL_GAP = 30;

//************************************************************
// Custom axis to handle label formatting
//************************************************************
class CCustomYAxisBase : public CBCGPChartAxisY
{
	DECLARE_DYNCREATE(CCustomYAxisBase)

public:
	CCustomYAxisBase()
	{
	}

	CCustomYAxisBase(int nAxisID, CBCGPChartAxis::AxisDefaultPosition position, CBCGPChartVisualObject* pChartCtrl) :
				CBCGPChartAxisY(nAxisID, position, pChartCtrl)
	{
	}

	virtual void GetDisplayedLabel(double dblValue, CString& strLabel);
};

IMPLEMENT_DYNCREATE(CCustomYAxisBase, CBCGPChartAxisY)

//------------------------------------------------------
// Displays label in format n,nnn.nn
//------------------------------------------------------
void CCustomYAxisBase::GetDisplayedLabel(double dblValue, CString& strLabel)
{
	strLabel.Format(_T("%.2f"), dblValue);
	
	int nPointIndex = strLabel.Find('.');
	
	for (int nIndex = nPointIndex - 3; nIndex > 0; nIndex -= 3)
	{
		if (nPointIndex <= 0)
		{
			break;
		}
		
		strLabel.Insert(nIndex, _T(","));
	}
}

//************************************************************
// Custom axis to be displayed outside of the Plot Area
//************************************************************
class CCustomAxisY : public CCustomYAxisBase
{
public:
	CCustomAxisY(int nAxisID, CBCGPChartAxis::AxisDefaultPosition position, CBCGPChartVisualObject* pChartCtrl) :
		CCustomYAxisBase(nAxisID, position, pChartCtrl)
	{

	}

	virtual void CalcAxisPos(const CBCGPRect& rectDiagram, BOOL bStoreAxisPos);
};

//------------------------------------------------------
// Calculates custom axis X offset based on the legend position
//------------------------------------------------------
void CCustomAxisY::CalcAxisPos(const CBCGPRect& rectDiagram, BOOL bStoreAxisPos)
{
	if (m_pChart == NULL)
	{
		return;
	}

	CBCGPChartAxisY::CalcAxisPos(rectDiagram, bStoreAxisPos);

	// assume we align axis relative to legend, which is located at the right
	// if the legend position doesn't matter use rectDiagram
	CBCGPRect rectLegend;
	//m_pChart->OnGetLegendAreaRect(rectLegend);

	// assumes the axis is vertical
	if ((m_pChart->m_chartLayout.m_legendPosition == BCGPChartLayout::LP_RIGHT || 
		m_pChart->m_chartLayout.m_legendPosition == BCGPChartLayout::LP_TOPRIGHT) && 
		!m_pChart->m_chartLayout.m_bLegendOverlapsChart)
	{
		m_ptAxisStart.x = m_ptAxisEnd.x = rectLegend.left - ADDITIONAL_GAP - m_szMaxLabelSize.cx;
	}
	else
	{
		// rectDiagram contains current plot area rect
		CBCGPChartAxis* pSecondaryAxis = m_pChart->GetChartAxis(BCGP_CHART_Y_SECONDARY_AXIS);
		m_ptAxisStart.x = m_ptAxisEnd.x = rectDiagram.right + ADDITIONAL_GAP + 
			AXIS_GAP + pSecondaryAxis->m_szMaxLabelSize.cx;
	}
}

//************************************************************
// Custom chart that adjusts plot area to accommodate space for third custom axis
//************************************************************
class CCustomChart : public CBCGPChartVisualObject
{
	DECLARE_DYNCREATE(CCustomChart)

public:
	CCustomChart()
	{
		m_nCustomAxisID = -1;
		m_bInsideAdjustLayout = FALSE;
		m_bFirstAdjust = TRUE;
	}

	CBCGPChartAxis* AddCustomAxis();
	virtual BOOL OnGetPlotAreaRect(CBCGPRect& rectPlotArea) const;
	
	virtual void AdjustLayout(CBCGPGraphicsManager* pGM);

protected:
	int m_nCustomAxisID;
	BOOL m_bInsideAdjustLayout;
	CBCGPRect m_rectCustomPlotArea;
	BOOL m_bFirstAdjust;
};

IMPLEMENT_DYNCREATE(CCustomChart, CBCGPChartVisualObject)

//------------------------------------------------------
// Adds custom Y axis and stores its index
//------------------------------------------------------
CBCGPChartAxis* CCustomChart::AddCustomAxis()
{
	// we could store a pointer to custom axis, but storing ID will gracefully handle removing (just in case)
	// in OnGetPlotAreaRect
	// CBCGPChartAxis::ADP_RIGHT tells the axis show labels at the right side by default
	CBCGPChartAxis* pAxis = new CCustomAxisY(GetNextCustomAxisID(), CBCGPChartAxis::ADP_RIGHT, this);
	m_nCustomAxisID = pAxis->m_nAxisID;

	// add the custom axis to collection
	AddAxis(pAxis);

	return pAxis;
}

//------------------------------------------------------
// Adjust layout must be called 2 times when the chart is displayed for the first time,
// because plot area rectangle is based on other elements
//------------------------------------------------------
void CCustomChart::AdjustLayout(CBCGPGraphicsManager* pGM)
{
	m_bInsideAdjustLayout = TRUE;
	CBCGPChartVisualObject::AdjustLayout(pGM);

	if (m_bFirstAdjust)
	{
		m_bFirstAdjust = FALSE;
		CBCGPChartVisualObject::AdjustLayout(pGM);
	}
	m_bInsideAdjustLayout = FALSE;

	// store the plot area rect to return it without additional calculations
	// when the rect is requested from methods other than AdjustLayout
	m_rectCustomPlotArea = m_rectPlotArea;
}

//------------------------------------------------------
// Returns plot area rectangle adjusted to make additional space for third axis
//------------------------------------------------------
BOOL CCustomChart::OnGetPlotAreaRect(CBCGPRect& rectPlotArea) const
{
	if (!m_bInsideAdjustLayout && !m_rectCustomPlotArea.IsRectEmpty())
	{
		rectPlotArea = m_rectCustomPlotArea;
		return TRUE; 
	}

	CBCGPRect rectLegend;
	//OnGetLegendAreaRect(rectLegend);

	if (m_bFirstAdjust || m_rectTitleArea.IsRectEmpty() || m_nCustomAxisID == -1 || m_rect.IsRectEmpty())
	{
		// AdjustLayout has not been called or custom axis has not been created
		return FALSE;
	}

	CBCGPChartAxis* pCustomAxis = GetChartAxis(m_nCustomAxisID);
	if (pCustomAxis == NULL || pCustomAxis->m_szMaxLabelSize.cx == 0)
	{
		return FALSE;
	}

	CBCGPRect rectPlot = m_rect;
	rectPlot.DeflateRect(m_chartAreaFormat.GetContentPadding(TRUE));

	if (!m_chartLayout.m_bTitleOverlapsChart)
	{
		rectPlot.top = m_rectTitleArea.bottom;
	}

	// if the legend is at right or top right and does not overlaps chart!
	if (!m_chartLayout.m_bLegendOverlapsChart)
	{
		CBCGPSize szLegendAreaPadding = GetLegendAreaPadding(TRUE);

		if (m_chartLayout.m_legendPosition == BCGPChartLayout::LP_RIGHT || 
			m_chartLayout.m_legendPosition == BCGPChartLayout::LP_TOPRIGHT)
		{
			rectPlot.right = m_rect.right - szLegendAreaPadding.cx - rectLegend.Width();
		}
		else if (m_chartLayout.m_legendPosition == BCGPChartLayout::LP_LEFT)
		{
			rectPlot.left = rectLegend.right + szLegendAreaPadding.cx;  
		}
		else if (m_chartLayout.m_legendPosition == BCGPChartLayout::LP_TOP)
		{
			rectPlot.top = rectLegend.bottom + szLegendAreaPadding.cy;  
		}
		else if (m_chartLayout.m_legendPosition == BCGPChartLayout::LP_BOTTOM)
		{
			rectPlot.bottom = rectLegend.top - szLegendAreaPadding.cy; 
		}
	}
	
	rectPlot.right -= pCustomAxis->m_szMaxLabelSize.cx + AXIS_GAP + ADDITIONAL_GAP;
	rectPlotArea = rectPlot;

	return TRUE;
}



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*grid_item g_gi[] = {
	gi_hdr("标题"),
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
};*/


/////////////////////////////////////////////////////////////////////////////
// Brow_Cur_Data dialog


Brow_Cur_Data::Brow_Cur_Data(CWnd* pParent /*=NULL*/)
: CDialog(Brow_Cur_Data::IDD, pParent)
{
	m_wndChart.CreateCustomChart(RUNTIME_CLASS(CCustomChart));
	//{{AFX_DATA_INIT(Brow_Cur_Data)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Brow_Cur_Data::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Brow_Cur_Data)
	DDX_Control(pDX, IDC_BCGCHART, m_wndChart);
	DDX_Control(pDX, IDC_FRAME_MESSAGE, m_MsgPicture);
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
	nCount = 0;
	m_StrArray.SetSize(8);
	pBottomAxis = NULL;
	CBridge_485Dlg* pd=(CBridge_485Dlg*)GetParent();
	TimeDelay = (pd->Delay_Time)/1000;
	pSeries = NULL;
	pPreSeries = NULL;
	GetDataCount=0;
	InitAxis();
	CreateChart();
//	memset(PreXPoints,0,sizeof(PreXPoints)/sizeof(PreXPoints[0])*sizeof(double));
//	memset(PreYPoints,5,sizeof(PreYPoints)/sizeof(PreYPoints[0])*sizeof(double));
	memset(XPoints,0,sizeof(XPoints)/sizeof(XPoints[0])*sizeof(double));
	memset(YPoints,0,sizeof(YPoints)/sizeof(YPoints[0])*sizeof(double));
	memset(Output,0,sizeof(Output)/sizeof(Output[0][0])*sizeof(double));
	memset(Input,0,sizeof(Input)/sizeof(Input[0][0])*sizeof(double));
	memset(PreOutput,0,sizeof(PreOutput)/sizeof(PreOutput[0][0])*sizeof(double));
	memset(PreInput,0,sizeof(PreInput)/sizeof(PreInput[0][0])*sizeof(double));
	memset(PreXPoints,0,sizeof(PreXPoints)/sizeof(PreXPoints[0])*sizeof(double));
	memset(PreYPoints,0,sizeof(PreYPoints)/sizeof(PreYPoints[0])*sizeof(double));

/*	for(int i =0;i < sizeof(PreXPoints)/sizeof(PreXPoints[0]);i++)
	{
		PreXPoints[i] = 0.0;
		PreYPoints[i] = 0.0;
	}
	for(int j =0;j < sizeof(XPoints)/sizeof(XPoints[0]);j++)
	{
		XPoints[j] = 0.0;
		YPoints[j] = 0.0;
	}*/
	
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
	// 判断路径是否存在 
	if (!PathIsDirectory(m_strFolderPath) ) 
	{ 
		CString strMsg; 
		strMsg.Format ("指定路径\\%s\\不存在，是否创建?", m_strFolderPath); 
		if (AfxMessageBox(strMsg, MB_YESNO) == IDYES) 
		{ 
			if (!CreateDirectory(m_strFolderPath, NULL)) 
			{ 
				strMsg.Format ("创建路径\\%s\\失败！将存储在根目录下", m_strFolderPath); 
				AfxMessageBox(strMsg);
			} 
		} 
	}
	sqlite3* db;
	int rc = sqlite3_open(m_strFolderPath+"\\"+"data.dat",&db);
	ASSERT(rc == SQLITE_OK);
	if(rc == SQLITE_OK)
	{
		AfxMessageBox("打开成功");
		SetWindowText("正在写入文件:"+ss);
	}
	else
	{	
		CString OpenErrorMsg = "";
		OpenErrorMsg.Format("数据库打开出错.\n错误原因:%s\n", sqlite3_errmsg(db));
		AfxMessageBox(OpenErrorMsg);
		return;
	}
	CString TableName = "";
	CString sqlcmd = "";
	char* ExeErrorMsg = "";
	for(int i = 1;i <=5;i++)//Node号码
	{
		for(int j = 1;j <=7;j++)//Channel号码
		{
			TableName.Format("Node_%d_Ch_%d",i,j);
			sqlcmd = "create table if not exists "+TableName+
				"(NUM integer primary key autoincrement, DataTime varchar(30),SensorVal integer(15))";
			rc = sqlite3_exec(db, sqlcmd, NULL, NULL, &ExeErrorMsg);
			if(rc != SQLITE_OK)
				AfxMessageBox(ExeErrorMsg);
			//else
			//AfxMessageBox("操作成功");			
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
	AfxMessageBox("写入成功");
	
	
}


void Brow_Cur_Data::WriteToSQL(CString *pDataStr, int Node, int Ch, sqlite3 *pdb)
{
/*CString m_strFolderPath="DataFolder" ;
// 判断路径是否存在 
if (!PathIsDirectory(m_strFolderPath) ) 
{ 
CString strMsg; 
strMsg.Format ("指定路径\"%s\"不存在，是否创建?", m_strFolderPath); 
if (AfxMessageBox(strMsg, MB_YESNO) == IDYES) 
{ 
if (!CreateDirectory(m_strFolderPath, NULL ) ) 
{ 
strMsg.Format ("创建路径\"%s\"失败！将存储在根目录下", m_strFolderPath); 
AfxMessageBox(strMsg);
} 
} 
}

  sqlite3* db;
  int rc = sqlite3_open(m_strFolderPath + "\\data1.dat",&db);
  ASSERT(rc == SQLITE_OK);
  if(rc == SQLITE_OK)
  {
		//AfxMessageBox("打开成功");
		//SetWindowText("正在写入文件");
		}
		else
		{	
		CString OpenErrorMsg = "";
		OpenErrorMsg.Format("数据库打开出错.\n错误原因:%s\n", sqlite3_errmsg(db));
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
	CBCGPChartVisualObject* pChart = m_wndChart.GetChart();
	ASSERT_VALID(pChart);
	CBCGPChartSeries*	pSerie= pChart->GetSeries(0);

	int count=pSerie->GetDataPointCount();
	CString tempstr="";
	if(count>=5)
	{
		pSerie->RemoveDataPoints(0);
		tempstr.Format("点%d",rand()%100);
		pSerie->SetDataPointCategoryName(tempstr,4);
	}
	for (int i = 0; i < 1; i++)
	{
		const double dblVal = rand()%20;
		
		tempstr.Format("点%d",rand()%100);
		pSerie->AddDataPoint(tempstr,dblVal);
	}
	
	pChart->SetDirty();
	pChart->Redraw();

	return 0;
	//GetWindowText(WndText);
	CString str = _T("");
	str.Format("%d号实时监测窗口",(int)wParam);
	SetWindowText(str);
	m_StrArray.Copy(*(CStringArray*)lParam);//需要补充检查数组元素是否有空值
	int nIndexNode = m_Com_Node.GetCurSel();
	int nIndexChannel = m_Com_Channel.GetCurSel();
	if((nIndexNode ==-1)||(nIndexChannel) ==-1)
	{
		SetWindowText(str+_T(" - 请确认节点和通道"));
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
		SetWindowText(str +" - 暂无数据");
		return 0;
	}
	/*CString str = "";
	str.Format("1-%s 2-%s 3-%s 4-%s 5-%s 6-%s 7-%s 8-%s",
	m_StrArray.GetAt(0),m_StrArray.GetAt(1),m_StrArray.GetAt(2),m_StrArray.GetAt(3),
	m_StrArray.GetAt(4),m_StrArray.GetAt(5),m_StrArray.GetAt(6),m_StrArray.GetAt(7));*/
	SetWindowText(str+" - 获取数据中...");

	CBridge_485Dlg* pd=(CBridge_485Dlg*)GetParent();
	TimeDelay = (pd->Delay_Time)/1000;

	COleDateTime Time;
	Time.ParseDateTime(m_StrArray.GetAt(0));
	COleDateTime begin_date(1970, 1, 1, 0, 0, 0);
	COleDateTime pre_end_date(1970, 1, 1, 0, 0, sizeof(PreXPoints)/sizeof(PreXPoints[0]));
	COleDateTime end_date(1970, 1, 1, 0, 0, sizeof(XPoints)/sizeof(XPoints[0]));
	COleDateTime minValue = Time - end_date + begin_date;
	COleDateTime maxValue = Time + pre_end_date - begin_date;
	//pBottomAxis->SetMinMax(CChartCtrl::DateToValue(minValue),CChartCtrl::DateToValue(maxValue));
	double Y = _ttol(m_StrArray.GetAt(5));
	double X = (DATE)Time;
	DrawData(pSeries,&X,&Y);
	DrawPreData(pPreSeries);
	

	return 0;
}

void Brow_Cur_Data::InitAxis()
{
	m_Chart.GetTitle()->AddString("实时监测图谱");
	pBottomAxis = m_Chart.CreateDateTimeAxis(CChartCtrl::BottomAxis);
	//Sets the tick increment to 4 months (disable automatic tick increment)
	pBottomAxis->SetTickIncrement(false, CChartDateTimeAxis::tiSecond, 2*TimeDelay);
	//Sets the tick label format for instance "Jan 2006"
	pBottomAxis->SetTickLabelFormat(false, _T("%H:%M:%S"));
	
	pBottomAxis->SetAutomatic(true); 
	pBottomAxis->GetLabel()->SetText("下轴");
	CChartStandardAxis* pLeftAxis = m_Chart.CreateStandardAxis(CChartCtrl::LeftAxis);
	pLeftAxis->SetAutomatic(true);
	//pLeftAxis->SetMinMax(0,20);
	pLeftAxis->SetTickIncrement(true,5.0);
	pLeftAxis->GetLabel()->SetText("左轴");
	pSeries = m_Chart.CreateLineSerie();
	pPreSeries = m_Chart.CreateLineSerie();
	pSeries->SetSmooth(false);
	pPreSeries->SetSmooth(false);
	m_Chart.EnableRefresh(false);
	m_Chart.SetBorderColor(RGB(0,0,255));
	m_Chart.SetBackColor(RGB(255,255,255));
	m_Chart.EnableRefresh(true);
	
}

void Brow_Cur_Data::DrawData(CChartLineSerie* pSerie,double* X,double* Y)
{
	int count = sizeof(XPoints)/sizeof(XPoints[0]);
	int Inputcount = sizeof(Input)/sizeof(Input[0]);
	if(IsFirstTime)
	{
		COleDateTime begin_date(1970, 1, 1, 0, 0, 0),begin1_date(1970, 1, 1, 0, TimeDelay/60, TimeDelay%60);
		COleDateTime end_date(1970, 1, 1, 0, count*TimeDelay/60, (count*TimeDelay)%60);
		COleDateTime temp_date;
		COleDateTime CurTime = COleDateTime::GetCurrentTime();
		double CurTimeDouble = (DATE)CurTime;//时间转换为double型
		//double YValue = rand()%100/100.0+1;
		temp_date =CurTime - end_date + begin_date;
		for(int i =0;i <count; i++)
		{
			YPoints[i] = 0.0;
			temp_date = temp_date + begin1_date - begin_date;//
			XPoints[i] = (DATE)temp_date;
		}
		IsFirstTime = FALSE;
	}
	
	int i=0,j = 0;
	for(j=0;j <count-1;j++)
	{
		XPoints[j] = XPoints[j+1];
		YPoints[j] = YPoints[j+1];
	}
	XPoints[j] = *X;
	YPoints[j] = *Y;
	pSerie->SetPoints(XPoints,YPoints,count);
	for(i=0;i <output_col;i++)
	{
		for(j=0;j <output_row-1;j++)
		{
			PreInput[j][i] = PreInput[j+1][i];
		}
		PreInput[j][i] = *Y;
	}
	for(i=0;i <input_col;i++)
	{
		if(i!=nCount)
			break;
		for(j=0;j <input_row-1;j++)
		{
			Input[j][i] = Input[j+1][i];
		}
		Input[j][i]=Output[0][i];
		for(j=0;j <outputtest_row-1;j++)
		{
			Output[j][i] = Output[j+1][i];
		}
		Output[j][i]=*Y;
	}
	nCount++;
	if(nCount==input_col)
		nCount=0;
	CString MsgText=_T("");
	if(GetDataCount<input_row*input_col+outputtest_row*output_col)
	{
		GetDataCount++;
		MsgText.Format("测量时间较短，采集样本不够，请等待...");
		SetBottomMessage(&MsgText);
	}
	else
	{
		Forecast();
		MsgText.Format("预测算法运行中...");
		SetBottomMessage(&MsgText);
	}
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
	COleDateTime begin_date(1970, 1, 1, 0, 0, 0),end_date(1970, 1, 1, 0, 0, TimeDelay);
	COleDateTime NextDate(PreXPoints[0]);
	for(int i = 1;i < Precount;i++)
	{
		NextDate = NextDate + end_date - begin_date;
		PreXPoints[i] = (DATE)NextDate;//rand()%10+rand()%150/100.0;
		PreYPoints[i] = PreOutput[i-1][output_col-1];//最终填放预测值
	}
	pSerie->SetPoints(PreXPoints,PreYPoints,Precount);
}

void Brow_Cur_Data::InitGrid()
{
/*	RECT rctW,rctC,rct;
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
	//m_Grid->Index[0] = gi_hdr("标题");
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
	
	m_Grid->Index[11]->Text="Password";*/
}



void Brow_Cur_Data::Forecast()//double input[][],double input_test[][],double output[][],double output_test[][]
{
	//clc
	//clear
	
	//%% 网络参数配置
	//load traffic_flux input output input_test output_test
/*	double Input[input_row][input_col]={{66,64,60,58},

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
	double Output[inputtest_row][input_col]={{28,71,21,69},

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
	double PreInput[output_row][output_col]={{17},

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
/*	double PreOutput[outputtest_row][output_col]={{34},

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

};*/
	int M=input_col;//sizeof(input[0])/sizeof(input[0][0]);//M=size(input,2); %输入节点个数
	int N=output_col;//sizeof(output[0])/sizeof(output[0][0]);//N=size(output,2); %输出节点个数
	//Forecast forecast;
	//int n=6; //%隐形节点个数
	double lr1=0.01; //%学习概率
	double lr2=0.001; //%学习概率
	//int maxgen=100; //%迭代次数
	
	//%权值初始化
	//Wjk=randn(n,M);
	//n=20;
	//M=20;
	int i,j,k,kk,kkk;
	/*CArray <double,double&> m_Wjk;
	typedef CArray <double,double&> DArray;
	//DArray m_Wjk;
	m_Wjk.SetSize(M);//相当于数组的列数
	CArray <DArray*,DArray*> Wjk;
	Wjk.SetSize(n);//相当于数组的行数
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
	m_Wjk.SetSize(n);//相当于数组的列数
	CArray <DArray*,DArray*> Wij;
	Wij.SetSize(N);//相当于数组的行数
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
	m_Wjk.SetSize(n);//相当于数组的列数
	CArray <DArray*,DArray*> a;
	a.SetSize(1);//相当于数组的行数
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
	m_Wjk.SetSize(n);//相当于数组的列数
	CArray <DArray*,DArray*> b;
	b.SetSize(1);//相当于数组的行数
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
	
	  
		
		  
			//%节点初始化
			m_Wjk.RemoveAll();
			m_Wjk.SetSize(N);//相当于数组的列数
			CArray <DArray*,DArray*> y;
			y.SetSize(1);//相当于数组的行数
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
			m_Wjk.SetSize(n);//相当于数组的列数
			CArray <DArray*,DArray*> net;
			net.SetSize(1);//相当于数组的行数
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
			m_Wjk.SetSize(n);//相当于数组的列数
			CArray <DArray*,DArray*> net_ab;
			net_ab.SetSize(1);//相当于数组的行数
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
			
			  
				//%权值学习增量初始化
				m_Wjk.RemoveAll();
				m_Wjk.SetSize(M);//相当于数组的列数
				CArray <DArray*,DArray*> d_Wjk;
				d_Wjk.SetSize(n);//相当于数组的行数
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
				m_Wjk.SetSize(n);//相当于数组的列数
				CArray <DArray*,DArray*> d_Wij;
				d_Wij.SetSize(N);//相当于数组的行数
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
				m_Wjk.SetSize(n);//相当于数组的列数
				CArray <DArray*,DArray*> d_a;
				d_a.SetSize(1);//相当于数组的行数
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
				m_Wjk.SetSize(n);//相当于数组的列数
				CArray <DArray*,DArray*> d_b;
				d_b.SetSize(1);//相当于数组的行数
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
	int M=input_col;//sizeof(input[0])/sizeof(input[0][0]);//M=size(input,2); %输入节点个数
	int N=output_col;//sizeof(output[0])/sizeof(output[0][0]);//N=size(output,2); %输出节点个数
	//Forecast forecast;
	//int n=6; //%隐形节点个数
	double lr1=0.01; //%学习概率
	double lr2=0.001; //%学习概率
int maxgen=100; //%迭代次数*/

//%权值初始化
//Wjk=randn(n,M);
//	int M=input_col;//sizeof(input[0])/sizeof(input[0][0]);//M=size(input,2); %输入节点个数
//	int N=output_col;//sizeof(output[0])/sizeof(output[0][0]);//N=size(output,2); %输出节点个数
//n=20;
//M=20;
//int i,j,k;
//CArray <double,double&> m_Wjk;
//typedef CArray <double,double&> DArray;
//DArray m_Wjk;
//m_Wjk.SetSize(M);//相当于数组的列数
//Wjk.SetSize(n);//相当于数组的行数
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
//m_Wjk.SetSize(n);//相当于数组的列数
//CArray <DArray*,DArray*> Wij;
//Wij.SetSize(N);//相当于数组的行数
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





//%节点初始化
//	m_Wjk.RemoveAll();
//	m_Wjk.SetSize(N);//相当于数组的列数
//	CArray <DArray*,DArray*> y;
//	y.SetSize(1);//相当于数组的行数
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
m_Wjk.SetSize(n);//相当于数组的列数
CArray <DArray*,DArray*> net;
net.SetSize(1);//相当于数组的行数
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
m_Wjk.SetSize(n);//相当于数组的列数
CArray <DArray*,DArray*> net_ab;
net_ab.SetSize(1);//相当于数组的行数
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

//%权值学习增量初始化
/*	m_Wjk.RemoveAll();
m_Wjk.SetSize(M);//相当于数组的列数
CArray <DArray*,DArray*> d_Wjk;
d_Wjk.SetSize(n);//相当于数组的行数
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
m_Wjk.SetSize(n);//相当于数组的列数
CArray <DArray*,DArray*> d_Wij;
d_Wij.SetSize(N);//相当于数组的行数
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
m_Wjk.SetSize(n);//相当于数组的列数
CArray <DArray*,DArray*> d_a;
d_a.SetSize(1);//相当于数组的行数
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
m_Wjk.SetSize(n);//相当于数组的列数
CArray <DArray*,DArray*> d_b;
d_b.SetSize(1);//相当于数组的行数
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


//%% 输入输出数据归一化
double tempmax = 0.0,tempmin = 0.0;
double input_max[input_col];// = {{0.0}};
memset(input_max,0,sizeof(input_max)/sizeof(input_max[0])*sizeof(double));
double input_min[input_col];// = {{0.0}};
memset(input_min,0,sizeof(input_min)/sizeof(input_min[0])*sizeof(double));
for(i = 0;i <input_col;i++)//[inputn,inputps]=mapminmax(Input');
{
	tempmax=Input[0][i];
	tempmin=Input[0][i];
	//m_Wjk.RemoveAll();
	for(j = 0;j < input_row;j++)
	{
		if(Input[j][i] > tempmax)
			tempmax = Input[j][i];
		if(Input[j][i] < tempmin)
			tempmin = Input[j][i];
	}
	input_max[i] = tempmax;
	input_min[i] = tempmin;
	for(j = 0;j < input_row;j++)
	{
		Input[j][i] = 2*(Input[j][i] - input_min[i])/(input_max[i] - input_min[i])-1;
	}
}


double output_max[output_col] = {{0.0}};
double output_min[output_col] = {{0.0}};
for(i = 0;i <output_col;i++)//[outputn,outputps]=mapminmax(PreInput');
{
	tempmax=PreInput[0][i];
	tempmin=PreInput[0][i];
	//m_Wjk.RemoveAll();
	for(j = 0;j < output_row;j++)
	{
		if(PreInput[j][i] > tempmax)
			tempmax = PreInput[j][i];
		if(PreInput[j][i] < tempmin)
			tempmin = PreInput[j][i];
	}
	output_max[i] = tempmax;
	output_min[i] = tempmin;
	for(j = 0;j < output_row;j++)
	{
		PreInput[j][i] = 2*(PreInput[j][i] - output_min[i])/(output_max[i] - output_min[i])-1;
	}
}


/*double input_max[input_col] = {{0.0}};
int tempmax=0,tempmin = 0;
for(i = 0;i <input_col;i++)//[inputn,inputps]=mapminmax(Input');
{
tempmax=0;
//m_Wjk.RemoveAll();
for(j = 0;j < input_row;j++)
{
if(abs(Input[i][j] > abs(tempmax)))
tempmax = Input[i][j];
//m_Wjk.SetAt(j,0.0);
//str.Format("%5.3f ",m_Wjk.GetAt(j));
//pf.Write(str,str.GetLength());
}
input_max[i] = tempmax;
for(j = 0;j < input_row;j++)
{
Input[i][j] = Input[i][j]/input_max[i];
//m_Wjk.SetAt(j,0.0);
//str.Format("%5.3f ",m_Wjk.GetAt(j));
//pf.Write(str,str.GetLength());
}
//pf.Write("\r\n",4);
//d_b.SetAt(i,&m_Wjk);
}
double output_max[output_col] = {{0.0}};
for(i = 0;i <output_col;i++)//[outputn,outputps]=mapminmax(PreInput'); 
{
tempmax=0;
//m_Wjk.RemoveAll();
for(j = 0;j < output_row;j++)
{
if(abs(PreInput[i][j] > abs(tempmax)))
tempmax = PreInput[i][j];
//m_Wjk.SetAt(j,0.0);
//str.Format("%5.3f ",m_Wjk.GetAt(j));
//pf.Write(str,str.GetLength());
}
output_max[i] = tempmax;
for(j = 0;j < output_row;j++)
{
PreInput[i][j] = PreInput[i][j]/output_max[i];
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

//%% 网络训练
//for i=1:maxgen
double x[input_col] = {{0.0}};
double yqw[output_col] = {{0.0}};
double error[maxgen] = {{0.0}};
double temp = 0.0;
for(i = 0; i < maxgen; i++)
{
	//%误差累计
	error[i]=0.0;
	for(kk = 0;kk <input_row;kk++)
	{
		for(kkk = 0;kkk <input_col ; kkk++)//x=inputn(kk,:);
		{
			x[kkk] = Input[kk][kkk];
		}
		for(kkk = 0;kkk <output_col ; kkk++)//yqw=outputn(kk,:);
			
		{
			yqw[kkk] = PreInput[kk][kkk];
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
		
		
		///权值参数更新
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
	//y=y+Wij(k,j)*temp;   %小波函数
}//end


////// 网络预测
//////预测输入归一化
double inputtest_max[input_col] = {{0.0}};
double inputtest_min[input_col] = {{0.0}};
for(i = 0;i <input_col;i++)//[inputn,inputps]=mapminmax(Input');
{
	tempmax=PreInput[0][i];
	tempmin=PreInput[0][i];
	//m_Wjk.RemoveAll();
	for(j = 0;j < inputtest_row;j++)
	{
		if(PreInput[j][i] > tempmax)
			tempmax = PreInput[j][i];
		if(PreInput[j][i] < tempmin)
			tempmin = PreInput[j][i];
	}
	inputtest_max[i] = tempmax;
	inputtest_min[i] = tempmin;
	for(j = 0;j < inputtest_row;j++)
	{
		PreInput[j][i] = 2*(PreInput[j][i] - inputtest_min[i])/(inputtest_max[i] - inputtest_min[i])-1;
	}
}//x=mapminmax('apply',PreInput',inputps);
//x=x';

/////网络预测
double x_test[input_col] = {{0.0}};
double yuce[1][inputtest_row] = {{0.0}};
for(i = 0; i <inputtest_row; i++)
{
	for(j = 0; j <input_col; j++)
	{
		x_test[j] = PreInput[i][j];
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
	PreOutput[i][output_col-1]=yun[i];
}

COleDateTime begin_date(1970, 1, 1, 0, 0, 0),end_date(1970, 1, 1, 0, 0, 1);
COleDateTime temp_date;
COleDateTime CurTime = COleDateTime::GetCurrentTime();
double CurTimeDouble = (DATE)CurTime;//时间转换为double型
double Time[outputtest_row] = {{0.0}};
//double output_test_[outputtest_row] = {{0.0}};
for(i = 0; i <outputtest_row; i++)
{
	//int count = sizeof(XPoints)/sizeof(XPoints[0]);
	//double YValue = rand()%100/100.0+1;
	//if(IsFirstTime)
	//{
	CurTime =CurTime + end_date - begin_date;
	Time[i] = (DATE)CurTime;
	//output_test_[i] = PreOutput[i][0];
	//pSeries->SetPoints(&yun[0][i],&CurTimeDouble,1);
	//Invalidate();
}
//pBottomAxis->SetMinMax(CChartCtrl::DateToValue(Time[0]),CChartCtrl::DateToValue(Time[outputtest_row-1]));
//pBottomAxis->SetTickIncrement(false, CChartDateTimeAxis::tiSecond, 10);
//CChartLineSerie *tempSeries = m_Chart.CreateLineSerie();
//pPreSeries->SetPoints(Time,output_test_,outputtest_row);
//pSeries->SetPoints(Time,yun,outputtest_row);
}

void Brow_Cur_Data::SetBottomMessage(CString* str)
{

		CDC* pDC = m_MsgPicture.GetDC();
		CRect rc;
		m_MsgPicture.GetClientRect(&rc);
		CBrush br;
		br.CreateSolidBrush(RGB(200,200,200));// 白色
		pDC->FillRect(&rc,&br);
		pDC->SetBkMode(TRANSPARENT);
		CFont font;
		font.CreatePointFont(100, "宋体");
		pDC->SelectObject(&font);
		//CString MsgText = _T("");
		//MsgText.Format("扫描时间间已修改为%dms",Delay_Time);//修复提醒消息刷新问题
		pDC->SetTextColor(RGB(rand()%180,rand()%180,rand()%180));
		pDC->TextOut(3,3,*str);
		ReleaseDC(pDC);
}


void Brow_Cur_Data::CreateChart()
{
	CCustomChart* pChart = DYNAMIC_DOWNCAST(CCustomChart, m_wndChart.GetChart());
	ASSERT_VALID(pChart);
	CBCGPChartSeries* pSeries1 = pChart->CreateSeries(_T("Line 1"), CBCGPColor(), BCGP_CT_DEFAULT, BCGPChartLine);

	//pChart->ShowAxisIntervalInterlacing(BCGP_CHART_X_PRIMARY_AXIS, FALSE);

	//pChart->SetChartType (BCGPChartHistoricalLine, BCGP_CT_SIMPLE, FALSE);
	//pChart->SetLegendPosition(BCGPChartLayout::LP_TOPRIGHT);


	CBCGPChartAxis* pPrimaryXAxis = pChart->GetChartAxis(BCGP_CHART_X_PRIMARY_AXIS);
	CBCGPChartAxis* pPrimaryYAxis = pChart->GetChartAxis(BCGP_CHART_Y_PRIMARY_AXIS);

	// replace default Y axis to handle custom labels
	CBCGPChartAxis* pSecondaryYAxis = pChart->ReplaceDefaultAxis(BCGP_CHART_Y_SECONDARY_AXIS, RUNTIME_CLASS(CCustomYAxisBase));

	// create custom third Y axis
	CBCGPChartAxis* pCustomAxis = pChart->AddCustomAxis();

	pPrimaryXAxis->m_axisLineFormat.m_dblWidth = 2.;
	pPrimaryYAxis->m_axisLineFormat.m_dblWidth = 2.;
	pSecondaryYAxis->m_axisLineFormat.m_dblWidth = 2.;
	pCustomAxis->m_axisLineFormat.m_dblWidth = 2.;

	pSeries1->AddDataPoint(_T("坐标1"), rand()%20);
	pSeries1->AddDataPoint(_T("Item 2"), rand()%20);
	pSeries1->AddDataPoint(_T("Item 3"), rand()%20);
	pSeries1->AddDataPoint(_T("Item 4"), rand()%20);
	pSeries1->AddDataPoint(_T("Item 5"), rand()%20);
	pSeries1->AddDataPoint(_T("Item 6"), rand()%20);


	// display second series on the secondary Y axis
	//pSeries2->SetRelatedAxis(pSecondaryYAxis, CBCGPChartSeries::AI_Y);

	// display third series on the custom third axis
	//pSeries3->SetRelatedAxis(pCustomAxis, CBCGPChartSeries::AI_Y);

	// set fixed display ranges with fixed major unit, because automatic ranges 
	// will look a bit different
	pPrimaryYAxis->SetFixedDisplayRange(0., 20., 2.);
	pSecondaryYAxis->SetFixedDisplayRange(0., 30000., 10000.);
	pCustomAxis->SetFixedDisplayRange(0., 90000000, 10000000.);

	// setup marker visibility
	//pSeries1->ShowMarker(FALSE);
	pSeries1->ShowMarker(TRUE);
	pSeries1->SetMarkerShape(BCGPChartMarkerOptions::MS_CIRCLE);
	//pSeries3->ShowMarker(TRUE);
	//pSeries3->SetMarkerShape(BCGPChartMarkerOptions::MS_RECTANGLE);

	// set second series to be SPLINE with width 2.
	BCGPChartFormatSeries style = pSeries1->GetSeriesFormat();

	style.m_curveType = BCGPChartFormatSeries::CCT_SPLINE;
	style.SetSeriesLineWidth(2.);
	pSeries1->SetSeriesFormat(style);

	// set width for the third series
	pSeries1->SetSeriesLineWidth(2.);

	// relocate the legend at the top
	pChart->SetLegendPosition(BCGPChartLayout::LP_TOPRIGHT);

	// set title font to be smaller
	pChart->GetTitleLabelFormat().m_textFormat.SetFontSize(18.);

	// do not display vertical interlaces
	pChart->ShowAxisIntervalInterlacing(BCGP_CHART_X_PRIMARY_AXIS, FALSE);

	// Sync series and axis colors
	//OnColorThemeUpdated();
	/*	pXAxis->m_axisLabelType = CBCGPChartAxis::ALT_LOW;
	pXAxis->m_majorTickMarkType = CBCGPChartAxis::TMT_INSIDE ;
	pXAxis->SetFixedIntervalWidth(20, 1);
	pXAxis->SetInterlaceStep(4);
	pXAxis->ShowScrollBar();

	CBCGPChartAxis* pYAxis = pChart->GetChartAxis(BCGP_CHART_Y_PRIMARY_AXIS);
	ASSERT_VALID(pYAxis);

	pYAxis->SetFixedDisplayRange(0., 4, 20.);

	pYAxis->m_bDisplayAxisName = FALSE;
	pChart->SetChartTitle(_T("Chart Title"));
	pChart->ShowChartTitle(1,0);
	pChart->ShowAxisIntervalInterlacing(BCGP_CHART_Y_PRIMARY_AXIS);
	pChart->SetLegendPosition(BCGPChartLayout::LP_NONE,FALSE);
	pChart->ShowDataMarkers(0);
	pChart->ShowDataLabels(0);
	pChart->SetAxisName(BCGP_CHART_X_PRIMARY_AXIS, _T("X Axis"));
	pChart->ShowAxisName(BCGP_CHART_X_PRIMARY_AXIS, 1);
	pChart->ShowAxisIntervalInterlacing(BCGP_CHART_X_PRIMARY_AXIS, 1);
	pChart->ShowAxisGridLines(BCGP_CHART_X_PRIMARY_AXIS, 1, FALSE);

	pChart->SetAxisName(BCGP_CHART_Y_PRIMARY_AXIS, _T("Y Axis"));
	pChart->ShowAxisName(BCGP_CHART_Y_PRIMARY_AXIS, 1);
	pChart->ShowAxisIntervalInterlacing(BCGP_CHART_Y_PRIMARY_AXIS, 1);
	pChart->ShowAxisGridLines(BCGP_CHART_Y_PRIMARY_AXIS, 1, FALSE);
	CString strLabel;
	strLabel.Format(_T("Series %d"), 1);
	CBCGPChartSeries*	pSerie = pChart->CreateSeries(strLabel);
	for (int i = 0; i < 20; i++)
	{
		break;
		//const double d = MAX_VAL / 25;
		double dblVal = rand()%20;//min(MAX - 1, max(0., m_arLastVal[i] + dblDelta));
		CString strXAxis=_T("");
		strXAxis.Format("坐标");
		pSerie->AddDataPoint(strXAxis,dblVal);
	}*/
}
