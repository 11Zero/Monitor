// Browse_History_Data.cpp : implementation file
//

#include "stdafx.h"
#include "Bridge_485.h"
#include "Bridge_485Dlg.h"
#include "Browse_History_Data.h"
#include <math.h>
#include <stdlib.h>
#include "ChartCtrl\ChartStandardAxis.h"
#include "ChartCtrl\ChartDateTimeAxis.h"
#include "ChartCtrl\ChartCtrl.h"
#include "ChartCtrl\ChartLineSerie.h"
#include "ChartCtrl\ChartBarSerie.h"
#include "ChartCtrl\ChartAxisLabel.h"
#include "ChartCtrl\ChartScrollBar.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define POINTNUM 10
/////////////////////////////////////////////////////////////////////////////
// Browse_History_Data dialog
int mCountOfTable;
int Count_Points;
double XValues[20],YValues[20];
int callback(void* pData,int nCount,char** pValue,char** pName);
int callback1(void* pData,int nCount,char** pValue,char** pName);
Browse_History_Data::Browse_History_Data(CWnd* pParent /*=NULL*/)
	: CDialog(Browse_History_Data::IDD, pParent)
{
	//{{AFX_DATA_INIT(Browse_History_Data)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Browse_History_Data::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Browse_History_Data)
	//DDX_Control(pDX, IDC_CHARTCTRL, m_ChartCtrl);
	DDX_Control(pDX, IDC_CHART_HISTROY, m_Chart_Histroy);
	DDX_Control(pDX, IDC_SCROLLBAR_HIST, m_ScrollBar);
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Browse_History_Data, CDialog)
	//{{AFX_MSG_MAP(Browse_History_Data)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BROWSE_BUTTON, OnBrowseButton)
	ON_WM_HSCROLL()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_CLOSE_HIST, OnCloseHist)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Browse_History_Data message handlers

BOOL Browse_History_Data::OnInitDialog() 
{
	CDialog::OnInitDialog();
	ModifyStyleEx(0, WS_EX_APPWINDOW);
	CurX = 0;
	//DrawCurFrame();
	DrawHistFrame();
	//XValues[0] = 0;
	//YValues[0] = 0;
	// TODO: Add extra initialization here
	fptr=fopen(His_Data_File,"r");
	//AfxMessageBox(His_Data_File);
    Load_File_Data();//调入数据
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//调入历史数据
void Browse_History_Data::Load_File_Data()
{
	int val(0),len;
	int set_val(10);//显示的条目数
	char tmp[200];
	if(fptr!=NULL) {
        while(fgets(tmp,100,fptr)!=NULL){
			len=strlen(tmp);tmp[len-1]='\0';
			Insert_File_Item(IDC_LIST2,tmp);
        val++;
		if(val>=set_val) break;
		}
	}
}

void Browse_History_Data::OnOK() 
{
	// TODO: Add extra validation here
	if(fptr!=NULL) fclose(fptr);
	//SetTimer(1,1000,NULL);
	
	
}
//插入文件条目
void Browse_History_Data::Insert_File_Item(int List_id, char *str)
{
	CListBox *ptr;
    ptr=(CListBox *) GetDlgItem(List_id);
	if(ptr!=NULL){
      ptr->AddString(str);
   
	}

}
//向后显示10行数据

void Browse_History_Data::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CDialog::OnPaint();
//	int pos = m_pScrollBar->GetScrollPos();
//	CString str = "";
//	str.Format("pos = %d",pos);
	//AfxMessageBox(str);
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
}

void Browse_History_Data::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
	case 1:
		{
			//DrawData();
			break;
		}
	}
	
	CDialog::OnTimer(nIDEvent);
}



//DEL void Browse_History_Data::AddCurPoint(CChartLineSerie* pSeries,double X, double Y)
//DEL {
//DEL //	CChartLineSerie* pSeries = m_ChartCtrl.CreateLineSerie();
//DEL 	pSeries->AddPoint(X,Y);
//DEL 
//DEL }

void Browse_History_Data::OnCancel() 
{
	// TODO: Add extra cleanup here
	KillTimer(1);
	DestroyWindow();
}

void Browse_History_Data::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDialog::PostNcDestroy();
	delete this;//非模态对话框需要销毁gdi
}

//DEL void Browse_History_Data::DrawData()
//DEL {
//DEL 	//CurX=CurX+1;
//DEL 	COleDateTime TimeVal = COleDateTime::GetCurrentTime();
//DEL 	CBridge_485Dlg* pDlg = (CBridge_485Dlg*)GetParent();
//DEL 	double* temp = 	pDlg->Send_To_History();
//DEL 	CurY = *temp;
//DEL 
//DEL 	for(int i = 0;i < POINTNUM-1 ;i++)
//DEL 	{
//DEL 		Yvalues[i] = Yvalues[i+1];
//DEL 		Xvalues[i] = Xvalues[i+1];
//DEL 	}
//DEL 	
//DEL 	Xvalues[POINTNUM-1] = CChartCtrl::DateToValue(TimeVal);
//DEL 	if(Xvalues[POINTNUM-1] != Xvalues[POINTNUM-2])
//DEL 	{
//DEL 		Yvalues[POINTNUM-1] = *temp;
//DEL 	}
//DEL 	pCurSeries->SetPoints(Xvalues,Yvalues,POINTNUM);
//DEL 	ScrollBarinfo.cbSize = sizeof(SCROLLINFO);  //固定！  本结构的大小      
//DEL 	ScrollBarinfo.fMask = SIF_ALL;  //一些属性    
//DEL 	ScrollBarinfo.nMin = 20;   //滑块所能到达的最小范围  
//DEL 	ScrollBarinfo.nMax = 1000;//滑块所能到达的最大范围 假如是一个图像 则为图像的高度  
//DEL 	ScrollBarinfo.nPage = 10;//滑块的大小  
//DEL 	//ScrollBarinfo.nPos = m_pScrollBar->GetScrollPos();//滑块的位置  
//DEL 	//pScrollBar->SetScrollRange(1,100);
//DEL 	//m_pScrollBar->SetScrollInfo(&ScrollBarinfo);
//DEL 
//DEL }

//DEL void Browse_History_Data::DrawAxisFrame()
//DEL {
//DEL 	//DrawCurFrame();
//DEL 	//DrawHistFrame();
//DEL 
//DEL 
//DEL 	//
//DEL 	//m_pScrollBar->Refresh();
//DEL 
//DEL 
//DEL 
//DEL }


BOOL Browse_History_Data::BrowseDat() 
{
	CString FileName = "";
	CString FilePathName = "";
	CString sqlcmd = "";
    CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"数据库文件 (*.dat)|*.dat|所有文件 (*.*)|*.*||",NULL);
	if(dlg.DoModal()==IDOK)
    {
        FileName = dlg.GetFileName(); //文件名保存在了FilePathName里
		FilePathName = dlg.GetPathName();
    }
    else
    {
		AfxMessageBox("无法浏览文件");
         return false;
    }
    int rc;
    rc = sqlite3_open(FileName, &db);
	if(rc == SQLITE_OK)
	{
		AfxMessageBox("打开成功");
		SetWindowText(_T(FilePathName.Left(25)) + _T("...\\...") + FileName);
	}
	else
	{	
		CString OpenErrorMsg = "";
		OpenErrorMsg.Format("数据库打开出错.\n错误原因:%s\n", sqlite3_errmsg(db));
		AfxMessageBox(OpenErrorMsg);
		return false;
	}
	char* ExeErrorMsg = "";
	//rc = sqlite3_exec( db, "drop table MyTable_4", NULL, NULL, &ExeErrorMsg);
	sqlcmd = "create table MyTable_4(ID integer primary key autoincrement, Xval integer(15),Yval integer(15))";
	rc = sqlite3_exec( db, sqlcmd, NULL, NULL, &ExeErrorMsg);
	if(rc != SQLITE_OK)
		AfxMessageBox(ExeErrorMsg);
	else
		AfxMessageBox("操作成功");
	int tempint = 1;
	for (int i = 1;i < 200 ; i++)
	{	
		sqlcmd.Format("INSERT INTO MyTable_4(ID,Xval,Yval) values (%d,%d,%d)",i,i,rand()%100);
		//sqlite3_exec(db,sqlcmd,NULL,NULL,&ExeErrorMsg);
	}
	mCountOfTable = 0;
	sqlite3_exec(db,"select * from MyTable_4",callback1,NULL,&ExeErrorMsg);//callback1为回调函数
	CString MsgStr = "";
	MsgStr.Format("表MyTable_4共有%d条数据",mCountOfTable);
	ScrollBarinfo.nMax = mCountOfTable;
	ScrollBarinfo.nPos = mCountOfTable;
	m_ScrollBar.SetScrollInfo(&ScrollBarinfo);
	if(mCountOfTable > 20)
	{
		sqlcmd.Format("select * from MyTable_4 where ID > %d and ID <= %d",mCountOfTable-20,mCountOfTable);
		Count_Points = 0;
		sqlite3_exec(db,sqlcmd,callback,NULL,&ExeErrorMsg);
	}
	else
	{
		sqlcmd.Format("select * from MyTable_4 where ID <= %d",mCountOfTable);
		Count_Points = 0;
		sqlite3_exec(db,sqlcmd,callback,NULL,&ExeErrorMsg);
	}
	pHistSeries->SetPoints(XValues,YValues,20);
	return TRUE;


	//AfxMessageBox(MsgStr);
	//if(tempint == 1)
	//{
	//	char* GetErrorMsg = 0;
		//sqlite3_exec(db,"",callback,NULL,&GetErrorMsg);
		//此处根据历史记录滚轴的位置来做20次查询，刷新画面显示的20个点，通过callback函数实现数据刷新；
	//}

	//for(int count = 0;count <20;count++)
	//{
	//	sqlcmd.Format("select * from MyTable_4 where ID = '%d'",); 
	//}
	//sqlite3_close(db);

}
int callback1(void* pData,int nCount,char** pValue,char** pName)
{
	mCountOfTable++;
	//CString str = "";
	//str.Format("nCount = %d",nCount);
	//AfxMessageBox(str);
	return 0;
}

int callback(void* pData,int nCount,char** pValue,char** pName)
{
	CString str = "";
    for(int i=0;i<nCount;i++)//计数器表示第几列
    {
		str.Format("%s",pName[i]);
        if(strcmp(pName[i],"Xval") == 0)
			XValues[Count_Points] = atof(pValue[i]);
		if(strcmp(pName[i],"Yval") == 0)
			YValues[Count_Points] = atof(pValue[i]);

    }
		Count_Points++;
    return 0;
}



void Browse_History_Data::OnBrowseButton() 
{
	BrowseDat();
	
}

void Browse_History_Data::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if(pScrollBar == (CScrollBar*)GetDlgItem(IDC_SCROLLBAR_HIST))
	{
			//AfxMessageBox("pos+1");
		int pos = pScrollBar->GetScrollPos();    // 获取水平滚动条当前位置   
		switch (nSBCode)    
		{    
			// 如果向左滚动一列，则pos减1   
        case SB_LINEUP:    
            pos -= 1; 
            break;    
			// 如果向右滚动一列，则pos加1   
        case SB_LINEDOWN:    
            pos  += 1;    
            break;    
			// 如果向左滚动一页，则pos减10   
        case SB_PAGEUP:    
            pos -= ScrollBarinfo.nPage;    
            break;    
			// 如果向右滚动一页，则pos加10   
        case SB_PAGEDOWN:    
            pos  += ScrollBarinfo.nPage;    
            break;    
			// 如果滚动到最左端，则pos为1   
        case SB_TOP:    
            pos = 1;    
            break;    
			// 如果滚动到最右端，则pos为100   
        case SB_BOTTOM:    
            pos = ScrollBarinfo.nMax;    
            break;      
			// 如果拖动滚动块滚动到指定位置，则pos赋值为nPos的值   
        case SB_THUMBPOSITION:    
            pos = nPos;    
            break;    
        default:    
            return;    
		}    
		pScrollBar->SetScrollPos(pos); 
		CString sqlcmd = "";
		char* ExeErrorMsg = "";
		if(mCountOfTable > 20)
		{
			sqlcmd.Format("select * from MyTable_4 where ID > %d and ID <= %d",pos-20,pos);
			Count_Points = 0;
			sqlite3_exec(db,sqlcmd,callback,NULL,&ExeErrorMsg);
		}
		else
		{
			sqlcmd.Format("select * from MyTable_4 where ID <= %d",pos);
			Count_Points = 0;
			sqlite3_exec(db,sqlcmd,callback,NULL,&ExeErrorMsg);
		}
		pHistSeries->SetPoints(XValues,YValues,20);
		
	}
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

/*void Browse_History_Data::OnMouseMove(UINT nFlags, CPoint point) 
{
	CRect PlotRec;
//	m_pScrollBar->GetWindowRect(&PlotRec);
/*	if(PlotRec.PtInRect(point))
		m_pScrollBar->ShowWindow(SW_SHOW);
	else
	{
		m_pScrollBar->ShowWindow(SW_HIDE);
		CString str = "";
		str.Format("point.x = %d,point.y = %d",point.x,point.y);
		SetWindowText(str);
	}
	Invalidate(false);
	
	CDialog::OnMouseMove(nFlags, point);
}*/

void Browse_History_Data::DrawHistFrame()
{
	m_Chart_Histroy.GetTitle()->AddString("监测图谱");
	//CChartAxis* 
	CChartStandardAxis* pHistBottomAxis = m_Chart_Histroy.CreateStandardAxis(CChartCtrl::BottomAxis);
	pHistBottomAxis->SetAutomatic(true); 
	//pDateAxis->EnableScrollBar(true);
	//pDateAxis->SetAutoHideScrollBar(false);
	//m_pScrollBar = pHistBottomAxis->GetScrollBarP();
	m_Chart_Histroy.GetBottomAxis()->GetLabel()->SetText("下轴");
	//pHistBottomAxis->SetMinMax(0, 100);
	CChartStandardAxis* pLeftAxis = m_Chart_Histroy.CreateStandardAxis(CChartCtrl::LeftAxis);
	pLeftAxis->SetAutomatic(true);
	pLeftAxis->SetMinMax(0, 100);
	m_Chart_Histroy.GetLeftAxis()->GetLabel()->SetText("左轴");
	pHistSeries = m_Chart_Histroy.CreateLineSerie();
	pHistSeries->SetSmooth(false);
	m_Chart_Histroy.EnableRefresh(false);
	m_Chart_Histroy.SetBorderColor(RGB(0,0,255));
	m_Chart_Histroy.SetBackColor(RGB(255,255,255));
	//m_Chart_Histroy.GetLegend()->DockLegend(CChartLegend::dsDockBottom);
	//m_Chart_Histroy.GetLegend()->SetHorizontalMode(true);
	m_Chart_Histroy.EnableRefresh(true);


	ScrollBarinfo.cbSize = sizeof(SCROLLINFO);  //固定！  本结构的大小      
	ScrollBarinfo.fMask = SIF_ALL;  //一些属性    
	ScrollBarinfo.nMin = 0;   //滑块所能到达的最小范围  
	ScrollBarinfo.nMax = 200;//滑块所能到达的最大范围 假如是一个图像 则为图像的高度  
	ScrollBarinfo.nPage = 10;//滑块的大小  
	ScrollBarinfo.nPos = 0;//滑块的位置
	m_ScrollBar.SetScrollInfo(&ScrollBarinfo);
	//pScrollBar->SetScrollRange(1,100);
	//m_pScrollBar->SetScrollInfo(&ScrollBarinfo);

/*	m_pScrollBar = new CChartScrollBar(pDateAxis);
	CRect temp = m_ChartCtrl.GetPlottingRect();
	CRect tempRec(0,100,400,100);
	m_pScrollBar->CreateScrollBar(temp);
	m_pScrollBar->SetEnabled(true);
	m_pScrollBar->SetScrollInfo(&ScrollBarinfo);
	m_pScrollBar->ShowWindow(SW_SHOW);
	m_pScrollBar->SetAutoHide(true);
	*/

}

//DEL void Browse_History_Data::DrawCurFrame()
//DEL {
//DEL 	m_ChartCtrl.GetTitle()->AddString("监测图谱");
//DEL 	//CChartAxis* 
//DEL 	CChartDateTimeAxis* pDateAxis = m_ChartCtrl.CreateDateTimeAxis(CChartCtrl::BottomAxis);
//DEL 	pDateAxis->SetAutomatic(true); 
//DEL 	//pDateAxis->EnableScrollBar(true);
//DEL 	//pDateAxis->SetAutoHideScrollBar(false);
//DEL 	m_pScrollBar = pDateAxis->GetScrollBarP();
//DEL 	m_ChartCtrl.GetBottomAxis()->GetLabel()->SetText("下轴");
//DEL 	pDateAxis->SetReferenceTick(COleDateTime::GetCurrentTime());
//DEL 	pDateAxis->SetTickIncrement(true,CChartDateTimeAxis::tiSecond,1);
//DEL 	pDateAxis->SetTickLabelFormat(false,_T("%M分%S秒"));
//DEL 	CChartStandardAxis* pLeftAxis = m_ChartCtrl.CreateStandardAxis(CChartCtrl::LeftAxis);
//DEL 	pLeftAxis->SetMinMax(0, 100);
//DEL 	pLeftAxis->SetAutomatic(true);
//DEL 	m_ChartCtrl.GetLeftAxis()->GetLabel()->SetText("左轴");
//DEL 	pCurSeries = m_ChartCtrl.CreateLineSerie();
//DEL 	pCurSeries->SetSmooth(true);
//DEL 	m_ChartCtrl.EnableRefresh(false);
//DEL 	m_ChartCtrl.SetBorderColor(RGB(0,0,255));
//DEL 	m_ChartCtrl.SetBackColor(RGB(255,255,255));
//DEL 	m_ChartCtrl.GetLegend()->DockLegend(CChartLegend::dsDockBottom);
//DEL 	m_ChartCtrl.GetLegend()->SetHorizontalMode(true);
//DEL 	m_ChartCtrl.EnableRefresh(true);
//DEL 	for(int i = 0;i < POINTNUM;)//初始化缓存数组
//DEL 	{
//DEL 		COleDateTime TimeVal = COleDateTime::GetCurrentTime();	
//DEL 		Xvalues[i] = CChartCtrl::DateToValue(TimeVal);
//DEL 		Yvalues[i] = 1;
//DEL 		i++;
//DEL 	}
//DEL 
//DEL 	pCurSeries->SetPoints(Xvalues,Yvalues,POINTNUM);
//DEL }

void Browse_History_Data::OnCloseHist() 
{
	// TODO: Add your control notification handler code here
	if(db != NULL)
		sqlite3_close(db);
	//pHistSeries->RemoveAllPoints();
}



