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
	DDX_Control(pDX, IDC_CHART, m_wndChart);
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Brow_Cur_Data, CDialog)
	//{{AFX_MSG_MAP(Brow_Cur_Data)
	ON_BN_CLICKED(IDC_BUTTON_TESTMSG, OnButtonTestmsg)
	ON_MESSAGE(WM_RECEIVEMSG,OnReceivemsg)
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
	// 判断路径是否存在 
	if (!PathIsDirectory(m_strFolderPath) ) 
	{ 
		CString strMsg; 
		strMsg.Format ("指定路径\"%s\"不存在，是否创建?", m_strFolderPath); 
		if (AfxMessageBox(strMsg, MB_YESNO) == IDYES) 
		{ 
			if (!CreateDirectory(m_strFolderPath, NULL)) 
			{ 
				strMsg.Format ("创建路径\"%s\"失败！将存储在根目录下", m_strFolderPath); 
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
	long StartTime=GetTickCount();
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
	long EndTime=GetTickCount();
	CString RunTime = "";
	RunTime.Format("操作成功,用时%.2fs",(EndTime-StartTime)/1000.0);
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



void Brow_Cur_Data::CreateChart()
{
	CBCGPChartVisualObject* pChart = m_wndChart.GetChart();
	ASSERT_VALID(pChart);

	pChart->ShowAxisIntervalInterlacing(BCGP_CHART_X_PRIMARY_AXIS, FALSE);

	pChart->SetChartType (BCGPChartHistoricalLine, BCGP_CT_SIMPLE, FALSE);
	pChart->SetLegendPosition(BCGPChartLayout::LP_TOPRIGHT);

	CBCGPChartAxis* pXAxis = pChart->GetChartAxis(BCGP_CHART_X_PRIMARY_AXIS);
	ASSERT_VALID(pXAxis);

	pXAxis->m_axisLabelType = CBCGPChartAxis::ALT_NO_LABELS;
	pXAxis->m_majorTickMarkType = CBCGPChartAxis::TMT_NO_TICKS;
	pXAxis->SetFixedIntervalWidth(20, 1);

	CBCGPChartAxis* pYAxis = pChart->GetChartAxis(BCGP_CHART_Y_PRIMARY_AXIS);
	ASSERT_VALID(pYAxis);

	pYAxis->SetFixedDisplayRange(0., 4, 20.);

	pYAxis->m_bDisplayAxisName = FALSE;

	pChart->SetChartTitle(_T("Chart Title"));
	pChart->ShowChartTitle(1,0);
	pChart->ShowAxisIntervalInterlacing(BCGP_CHART_Y_PRIMARY_AXIS);
	pChart->SetLegendPosition(BCGPChartLayout::LP_LEFT,FALSE);
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
		//const double d = MAX_VAL / 25;
		double dblVal = rand()%20;//min(MAX - 1, max(0., m_arLastVal[i] + dblDelta));
		CString strXAxis=_T("");
		strXAxis.Format("坐标");
		pSerie->AddDataPoint(strXAxis,dblVal);
	}


}

BOOL Brow_Cur_Data::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CreateChart();	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
