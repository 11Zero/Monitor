// Bridge_485Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Bridge_485.h"
#include "Bridge_485Dlg.h"
#include "RS_232_Para.h"
#include "RS_485_Dlg.h"
#include "Mobile_Dlg.h"
#include "fg_485_Net_Node_dlg.h"
#include "Browse_History_Data.h"
#include "Sg_Step_Selectiong.h"
#include "Set_Sensor_Warning_Value.h"
#include "Testing_Warning_Value_Fun.h"
#include "Bridge_Dll.h"//报警动态库头文件
#include "Brow_Cur_Data.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	
	// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA
	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
//{{AFX_MSG_MAP(CAboutDlg)
// No message handlers
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBridge_485Dlg dialog

CBridge_485Dlg::CBridge_485Dlg(CWnd* pParent /*=NULL*/)
: CDialog(CBridge_485Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBridge_485Dlg)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBridge_485Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBridge_485Dlg)
	DDX_Control(pDX, IDC_MSCOMM1, m_comm1);
	DDX_Control(pDX, IDC_MSCOMM2, m_comm2);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBridge_485Dlg, CDialog)
//{{AFX_MSG_MAP(CBridge_485Dlg)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_COMMAND(ID1_232_CFG, On232Cfg)
ON_COMMAND(IDD2_485_CFG, On485Cfg)
ON_COMMAND(IDD_OPEN_S232, OnOpenS232)
ON_COMMAND(IDD_OPEN_S485, OnOpenS485)
ON_COMMAND(ID1_232_SEND, On232_Send)
ON_COMMAND(ID1_RECEIVE_232, OnReceive_232)
ON_COMMAND(ID2_SEND_485, OnSend_485)
ON_COMMAND(ID2_RECEIVE_485, OnReceive_485)
ON_COMMAND(WARNING_CONFIG, On_BaoJing_Config)
ON_COMMAND(NODE_CONFIG, OnConfig_para)
ON_COMMAND(IDD_CLEAR_LIB, OnClearLib)
ON_COMMAND(IDD_SHOUJI_COM, OnShoujiCom)
ON_COMMAND(IDD_485_COM, On485Com_ch)
ON_COMMAND(IDD_INIT_VAL, OnInitVal)
ON_COMMAND(IDD_FETCH_485_DATA, OnFetch485Data)
ON_WM_TIMER()
ON_COMMAND(IDD_TIMER_MEAS, OnTimerMeas)
ON_COMMAND(MENU_SG_STEP, OnSgStep)
ON_COMMAND(MENU_WARNING_PARA, OnWarningPara)
ON_COMMAND(IDD_WARNING_TEST, OnWarningTest)
ON_COMMAND(IDD_TEST_WIRELESS_DATA, OnTestWirelessData)
ON_COMMAND(IDD_GET_PHONE_NUM, OnGetPhoneNum)
ON_COMMAND(IDD_TIMER_STOP, OnTimerStop)
ON_COMMAND(IDC_HIST_LIB_BROW, OnHistLibBrow)
ON_COMMAND(IDC_CUR_DATA_BROW, OnCurDataBrow)
ON_BN_CLICKED(IDC_BUTTON_TEST, OnButtonTest)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBridge_485Dlg message handlers

BOOL CBridge_485Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetWindowPos(&wndNoTopMost,0,0,0,0, SWP_NOMOVE | SWP_NOSIZE);
	Brow_Cur_Data_Count = 0;//初始化检测窗口计数器
	DataToCurView.SetSize(8);//定义传输数据串为八个数据
	for(int i= 0 ;i < sizeof(phdlg)/sizeof(phdlg[0]);i++)
		phdlg[i] = NULL;//初始化监测窗口为空；
	// Add "About..." menu item to system menu.
	
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	flag_232=flag_485=0;//未配置参数
	SetWindowText(_T("公路桥梁碗扣式满堂支架施工安全预警系统"));
	// TODO: Add extra initialization here
	//获得执行文件当前所在目录
	::GetCurrentDirectory(199,(LPTSTR) Cur_Path_Dir);
	strcpy(Config_Path_Dir,Cur_Path_Dir);strcat(Config_Path_Dir,"\\Config");//配置文件目录
	   Bridge_DLL_Set_Cfg_Path(Config_Path_Dir);//设置配置文件目录
	   //  AfxMessageBox(Config_Path_Dir);
	   strcpy(Meas_Path_Dir,Cur_Path_Dir);strcat(Meas_Path_Dir,"\\Mdata");//测量文件和数据库文件目录
	   strcpy(Meas_Lib_File_Name,Meas_Path_Dir);strcat(Meas_Lib_File_Name,"\\MeasData.txt");
	   //文件测试
	   //Add_Dtat_To_Lib(Meas_Lib_File_Name,"2001;Node1;Ch1;10.5mm\n");
	   //AfxMessageBox(Meas_Path_Dir);
	   //AfxMessageBox(Cur_Path_Dir);
	   //调入配置信息__测量控制网络
	   Load_Node_Info();//
	   Control_Command_ID=0;Cmd_Buffer[0]='\0';
	   //设置运行模式
	   Set_Run_Mode();
	   
	   return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBridge_485Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBridge_485Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBridge_485Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BEGIN_EVENTSINK_MAP(CBridge_485Dlg, CDialog)
//{{AFX_EVENTSINK_MAP(CBridge_485Dlg)
ON_EVENT(CBridge_485Dlg, IDC_MSCOMM1, 1 /* OnComm */, OnOnCommMscomm1, VTS_NONE)
ON_EVENT(CBridge_485Dlg, IDC_MSCOMM2, 1 /* OnComm */, OnOnCommMscomm2, VTS_NONE)
//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CBridge_485Dlg::OnOnCommMscomm1() 
{
	// TODO: Add your control notification handler code here
	
}

void CBridge_485Dlg::OnOnCommMscomm2() 
{
	// TODO: Add your control notification handler code here
	
}
//无线通讯口参数配置
void CBridge_485Dlg::On232Cfg() 
{
	// TODO: Add your command handler code here
	RS_232_Para Rs232_Dlg;
	if(Rs232_Dlg.DoModal()==IDOK){
		flag_232=1;
		m_PPort_232=Rs232_Dlg.m_PPort;
		strcpy(baud_str_232,Rs232_Dlg.baud_str);
		/*char spp[100];
		sprintf(spp,"232__%d",m_PPort_232);
		MessageBox(spp,baud_str_232);
		*/
	}
}
//测控网络通讯参数配置
void CBridge_485Dlg::On485Cfg() 
{
	// TODO: Add your command handler code here
	RS_485_Dlg Rs485_Dlg;
	if(Rs485_Dlg.DoModal()==IDOK) {
		flag_485=1;
		m_PPort_485=Rs485_Dlg.m_PPort;
		strcpy(baud_str_485,Rs485_Dlg.baud_str);
		/*char spp[100];
		sprintf(spp,"485__%d",m_PPort_485);
		MessageBox(spp,baud_str_485);
		*/
	}
}
//打开232口配置对话框
void CBridge_485Dlg::Open_232_Port()
{
	// TODO: Add your control notification handler code here
	//	char spc[100];
	//sprintf(spc,"port=%d",m_PPort);
	//AfxMessageBox(spc);
	char tmp_str[30];
    
	if(flag_232==0) return;
    //MessageBox("23222");
	m_comm1.SetCommPort(m_PPort_232);//m_Port);//设置串口
	m_comm1.SetInputMode(1);//设置数据读取格式为二进制
	strcpy(tmp_str,baud_str_232);strcat(tmp_str,",n,8,1");
	//MessageBox(tmp_str);
	m_comm1.SetSettings(tmp_str);//传输参数
	//m_Comm.SetSettings("115200,n,8,1");//传输参数
	m_comm1.SetRThreshold(1);//缓冲区内有一个字符就可以接收
	m_comm1.SetInBufferSize(2048);//接收缓冲区的大小
	m_comm1.SetOutBufferSize(2048);//发送缓冲区大小
	m_comm1.SetInBufferCount(0);//清空接收缓冲区
	if(!m_comm1.GetPortOpen())
	{
		m_comm1.SetPortOpen(true);//打开串口
		//	Dis_Button(IDC_BUTTON1,0);
		//	Dis_Button(IDC_BUTTON2,1);
		//Dis_Button(IDC_BUTTON3,1);
		//	com_open_flag=1;//串行口已打开
		//	char ss1[100];
		//sprintf(ss1,"Serial_Num=%d",m_PPort_232);
		//MessageBox(tmp_str,ss1);
	}	
}
//打开485口配置对话框
void CBridge_485Dlg::Open_485_Port()
{
	// TODO: Add your control notification handler code here
	//	char spc[100];
	//sprintf(spc,"port=%d",m_PPort);
	//AfxMessageBox(spc);
	char tmp_str[30];
	if(flag_485==0) return;
	m_comm2.SetCommPort(m_PPort_485);//m_Port);//设置串口
	m_comm2.SetInputMode(1);//设置数据读取格式为二进制
	strcpy(tmp_str,baud_str_485);strcat(tmp_str,",n,8,1");
	//MessageBox(tmp_str);
	m_comm2.SetSettings(tmp_str);//传输参数
	//m_Comm.SetSettings("115200,n,8,1");//传输参数
	m_comm2.SetRThreshold(1);//缓冲区内有一个字符就可以接收
	m_comm2.SetInBufferSize(2048);//接收缓冲区的大小
	m_comm2.SetOutBufferSize(2048);//发送缓冲区大小
	m_comm2.SetInBufferCount(0);//清空接收缓冲区
	if(!m_comm2.GetPortOpen())
	{
		m_comm2.SetPortOpen(true);//打开串口
		//	Dis_Button(IDC_BUTTON1,0);
		//	Dis_Button(IDC_BUTTON2,1);
		//	Dis_Button(IDC_BUTTON3,1);
		//com_open_flag=1;//串行口已打开
		//MessageBox("485 opened");
		//char tmp[100];
		//	sprintf(tmp,"serial_num=%d",m_PPort_485);
		//	MessageBox(tmp,(char *) tmp_str);
	}	
}
//打开无线串行口
void CBridge_485Dlg::OnOpenS232() 
{
	// TODO: Add your command handler code here
	if(m_comm1.GetPortOpen())
	{
		m_comm1.SetPortOpen(false);//关闭串口
		Open_232_Port();
	}
	else {
		Open_232_Port();
	}
}
//打开测量串行口
void CBridge_485Dlg::OnOpenS485() 
{
	// TODO: Add your command handler code here
	if(m_comm2.GetPortOpen())
	{
		m_comm2.SetPortOpen(false);//关闭串口
		Open_485_Port(); 
	}
	else {
		Open_485_Port(); 
		
	}
}
//从串行口发送数据
void CBridge_485Dlg::TDR_Send_Data_To_Com(unsigned char *send_buf, int data_len,int which_channel)
{
	//which_channel=1,手机口;=2,485口
	CByteArray m_Array;//二进制数组
	m_Array.SetSize(data_len);
	for(int i=0;i<data_len;i++)//为数组赋值
	{
		m_Array.SetAt(i,send_buf[i]); 
		
	}
	switch(which_channel) {
	case 1://手机口
		{
			if(m_comm1.GetPortOpen()){
				// MessageBox("从手机发送数据");
				m_comm1.SetOutput(COleVariant(m_Array));//发送数据
			}
		}
		break;
	case 2://测量口
		{
			if(m_comm2.GetPortOpen()){
				//MessageBox("从485发送数据");
				m_comm2.SetOutput(COleVariant(m_Array));//发送数据
			}
		}
		break;
	}
	
}
//从手机发送数据
void CBridge_485Dlg::On232_Send() 
{
	// TODO: Add your command handler code here
	unsigned char pkt[1024];
    unsigned char tmp[100];
	//for(int i=0;i<5;i++) { sprintf((char *) tmp,"%d",i);pkt[i]=tmp[0];}
	strcpy((char *) pkt,"AT+CISMSSEND=13866120701,3,中国科学技术大学234");
	int test_data(200);
	sprintf((char *) tmp,"_%d",test_data);
	strcat((char *) pkt,(char *) tmp);
	
	
	int len=strlen((char *) pkt);
	pkt[len]=0x0d;len++;
	//	pkt[len]=0x0a;len++;
	//	pkt[0]='0';pkt[1]='1';pkt[2]='2';
	TDR_Send_Data_To_Com(pkt,len,1);
	//Sleep(1000);
    //TDR_Send_Data_To_Com(pkt,len,1);
	
}
//从手机接收数据
void CBridge_485Dlg::OnReceive_232() 
{
	// TODO: Add your command handler code here
	unsigned char pkt[2048];
	char tmp_file_name[200];
	FILE *fp;
	strcpy(tmp_file_name,Cur_Path_Dir);strcat(tmp_file_name,"\\Phonemsg.txt");
	int k=TDR_Get_Cur_Buffer_Data(pkt,1);
	if(k>0){
		pkt[k]='\0';
		/*
		char tmp[20];
		for(int i=0;i<k;i++) {
		sprintf(tmp,"i=%d val=%d len=%d",i,pkt[i],k);
		MessageBox(tmp);
		*/
		MessageBox((char *) pkt);
		fp=fopen(tmp_file_name,"w");
		if(fp!=NULL){
			fputs((char *) pkt,fp);
			fclose(fp);
		}
		//ff
		
		
	}
}
//想测控节点发送数据
void CBridge_485Dlg::OnSend_485() 
{
	// TODO: Add your command handler code here
	//	unsigned char pkt[20];
	//	for(int i=0;i<5;i++) pkt[i]=i*5;
	//TDR_Send_Data_To_Com(pkt,5,2);
	Fill_485_data_Pkt();//发送RTU 数据包
}
//从测量控制节点接收数据
void CBridge_485Dlg::OnReceive_485() 
{
	// TODO: Add your command handler code here
	unsigned char pkt[2048];
	int k=TDR_Get_Cur_Buffer_Data(pkt,2);
	if(k>0){
		char tmp[20];
		for(int i=0;i<k;i++) {
			sprintf(tmp,"i=%d val=%x len=%d",i,pkt[i],k);
			MessageBox(tmp);
			
		}
	}
}
//获得当前缓冲区的数据,返回值为当前的数据长度
int CBridge_485Dlg::TDR_Get_Cur_Buffer_Data(unsigned char *buf,int which_channel)
{
	int k(0);
	VARIANT m_input;
	switch(which_channel) {
	case 1:
		{
			k=m_comm1.GetInBufferCount();//接收缓冲区字符数
			if(k>0) {
				m_input=m_comm1.GetInput();
				memmove(buf, (unsigned char*)m_input.parray->pvData,k);
			}
			
		}
		break;
	case 2:
		{
			k=m_comm2.GetInBufferCount();//接收缓冲区字符数
			if(k>0) {
				m_input=m_comm2.GetInput();
				memmove(buf, (unsigned char*)m_input.parray->pvData,k);
			}
		}
		break;
	}
	
	return k;
}
//报警设置
void CBridge_485Dlg::On_BaoJing_Config() 
{
	// TODO: Add your command handler code here
	char cfg_name[200];
    Mobile_Dlg mobile_dlg;
	//产生报警文件
	strcpy(cfg_name,Config_Path_Dir);strcat(cfg_name,"\\Bconfig.txt");
	strcpy(mobile_dlg.Cfg_File_name,cfg_name);
	
	mobile_dlg.DoModal();
}
//生成485数据封包并发送
void CBridge_485Dlg::Fill_485_data_Pkt()
{
    unsigned char Send_Pkt_Data[100];//发送数据包
	int pkt_len(0);//数据包长度
    unsigned short int CRC_val;
	
	pkt_len=0;
    Send_Pkt_Data[pkt_len]=1;pkt_len++;
    Send_Pkt_Data[pkt_len]=4;pkt_len++;
	
	
	
	Send_Pkt_Data[pkt_len]=0;pkt_len++;
    Send_Pkt_Data[pkt_len]=0;pkt_len++;
	Send_Pkt_Data[pkt_len]=0;pkt_len++;
	Send_Pkt_Data[pkt_len]=8;pkt_len++;
	   
	//______________end_______________//
	CRC_val=Com_CRC_16_Code(Send_Pkt_Data,pkt_len);
	Send_Pkt_Data[pkt_len]=(CRC_val&0x0ff);pkt_len++;
	Send_Pkt_Data[pkt_len]=(CRC_val>>8)&0x0ff;pkt_len++;
	
	char spp[100];
	sprintf(spp,"%x %x %x %x %x %x %x %x %d", Send_Pkt_Data[0],
		Send_Pkt_Data[1],Send_Pkt_Data[2],Send_Pkt_Data[3],Send_Pkt_Data[4],Send_Pkt_Data[5],
		Send_Pkt_Data[6],Send_Pkt_Data[7],pkt_len);
	MessageBox(spp);
	//发送数据
   	TDR_Send_Data_To_Com(Send_Pkt_Data,pkt_len,2);
	
}
//计算CRC-16校验代码
unsigned short int CBridge_485Dlg::Com_CRC_16_Code(unsigned char *buf,int buf_len)
{
	
	unsigned short int reg_tmp;
	int i,j;
	reg_tmp=0x0ffff;
	unsigned short int tmpx;
	for(i=0;i<buf_len;i++) {
		tmpx=(unsigned short int) buf[i];
		reg_tmp=reg_tmp^tmpx;
		for(j=0;j<8;j++) {
			if((reg_tmp&0x1)==1) {
				reg_tmp=reg_tmp>>1;
				reg_tmp=reg_tmp^0x0a001;
			}
			else reg_tmp=reg_tmp>>1;
			
		}
		
	}
	return reg_tmp;
}
//485测量网络控制节点参数配置
void CBridge_485Dlg::OnConfig_para() 
{
	// TODO: Add your command handler code here
	Cfg_485_Net_Node_dlg r485_para_dlg;
	char para_file_name[200];
	//生成文件名
	strcpy(para_file_name,Config_Path_Dir);strcat(para_file_name,"\\Bpara.txt");
	// MessageBox(para_file_name);
	strcpy(r485_para_dlg.Cfg_File_Name,para_file_name);
	r485_para_dlg.DoModal();
}
//将测量数据添加到数据库文件
void CBridge_485Dlg::Add_Dtat_To_Lib(char *file_name, char *str)
{
	FILE *fp;
	fp=fopen(file_name,"a+");
	if(fp!=NULL){
		fputs(str,fp);
		//	MessageBox("open ok");
		fclose(fp);
	}
}
//浏览测量数据文件内容
void CBridge_485Dlg::OnLibBrow() 
{
	// TODO: Add your command handler code here
	
}

void CBridge_485Dlg::OnClearLib() 
{
	// TODO: Add your command handler code here
	if(MessageBox("清理数据文件?","请选择.......",MB_YESNO)==IDYES){
		FILE *fpt;
		fpt=fopen(Meas_Lib_File_Name,"w");
		if(fpt!=NULL) fclose(fpt);
	} 
}
//检查手机通讯
int CBridge_485Dlg::Check_ShouJi_Comm()
{
	int ret(0);
	// TODO: Add your command handler code here
	
    unsigned char pkt[2048]; //unsigned char tmp[100];
	int k=TDR_Get_Cur_Buffer_Data(pkt,1);
	
	
	
	
	//for(int i=0;i<5;i++) { sprintf((char *) tmp,"%d",i);pkt[i]=tmp[0];}
	strcpy((char *) pkt,"AT");//+CISMSSEND=13866120701,3,中国科学技术大学234");
	
	
	int len=strlen((char *) pkt);
	pkt[len]=0x0d;len++;
	//	pkt[len]=0x0a;len++;
	//	pkt[0]='0';pkt[1]='1';pkt[2]='2';
	TDR_Send_Data_To_Com(pkt,len,1);
	Sleep(2000);
	k=TDR_Get_Cur_Buffer_Data(pkt,1);
	if(k>0){
		pkt[k]='\0';
		
		unsigned char  tmp[20];
		tmp[0]=0x0d;tmp[1]=0x0a;tmp[2]='O';tmp[3]='K';
		tmp[4]=0x0d;tmp[5]=0x0a;tmp[6]='\0';
		if(strcmp((char *) pkt,(char *) tmp)==0) return 1;
	}
	return ret;
}
//检查485通讯网络
int CBridge_485Dlg::Check_485_Comm()
{
	int ret(0);
	unsigned char pkt[2048];
	TDR_Get_Cur_Buffer_Data(pkt,2);
	Fill_485_Connect_Pkt(1);
   	Sleep(2000);//延续时间
	int k=TDR_Get_Cur_Buffer_Data(pkt,2);
	if(k>0) {
		unsigned short int crc_val;
		crc_val=Com_CRC_16_Code(pkt,k-2);//,int buf_len)
		unsigned short int  ret_crc;
		ret_crc=pkt[k-1];ret_crc=(unsigned short int) (ret_crc<<8)&0x0ff00;
		ret_crc+=(unsigned short int) pkt[k-2];
		/*
		char tmp[200];
		sprintf(tmp,"%x %x",crc_val,ret_crc);
		MessageBox(tmp);
		*/
		if(ret_crc==crc_val) return 1;
		
		
	}
	return ret;
}
//手机模块通讯检查
void CBridge_485Dlg::OnShoujiCom() 
{
	// TODO: Add your command handler code here
	int ret_val;
	ret_val=Check_ShouJi_Comm();
	if(ret_val==0)MessageBox("无线网络异常");
	else MessageBox("无线网络正常____OK_______");
}
//485通讯网络检查
void CBridge_485Dlg::On485Com_ch() 
{
	// TODO: Add your command handler code here
	int ret_val;
	ret_val=Check_485_Comm();
	if(ret_val==0)MessageBox("测控网络异常");
	else MessageBox("测控网络正常______OK_______");
}
//测量传感器器初始值
void CBridge_485Dlg::OnInitVal() 
{
	// TODO: Add your command handler code here
	MessageBox("传感器初始值");
}
//从配置文件中获得测量网络各节点的配置信息
void CBridge_485Dlg::Load_Node_Info()
{
	FILE *fp;
	char para_file_name[200];
	char tmp[100] ;//,tmp1[100];
	int i,j,len;
	//生成文件名
	strcpy(para_file_name,Config_Path_Dir);strcat(para_file_name,"\\Bpara.txt");
	fp=fopen(para_file_name,"r");
	if(fp!=NULL){
		fgets(Test_Position,100,fp);len=strlen(Test_Position);Test_Position[len-1]='\0';
		fgets(tmp,100,fp);
		Total_Node_Num=atoi(tmp);
		// sprintf(tmp1,"%d",Total_Node_Num);MessageBox(tmp1);
		for(i=0;i<Total_Node_Num;i++) {
            fgets(tmp,100,fp);Node_Ch_num[i]=atoi(tmp);
			for(j=0;j<Node_Ch_num[i];j++){
				fgets(tmp,100,fp);len=strlen(tmp);tmp[len-1]='\0';
				//传感器名称
				strcpy(Node_Ch_Sensor_Name[i][j],tmp);
				// MessageBox(Node_Ch_Sensor_Name[i][j]);
				//传感器灵敏度
				fgets(tmp,100,fp); Node_Ch_Sensor_Lmd[i][j]=atof(tmp);
				//sprintf(tmp1,"lmd=%5.3f",Node_Ch_Sensor_Lmd[i][j]);
				// MessageBox(tmp1);
				//传感器单位
				fgets(tmp,100,fp);len=strlen(tmp);tmp[len-1]='\0';
				strcpy(Node_Ch_Sensor_Unit[i][j],tmp);
				//MessageBox(Node_Ch_Sensor_Unit[i][j]);
				
			}
		}     
		
		/*
		//节点参数
		int Total_Node_Num;//节点总数
		int Node_Ch_num[32];//每个节点测量通道数
		char Node_Ch_Sensor_Name[32][8][20];//每个通道的传感器名称
		double Node_Ch_Sensor_Lmd[32][8];//每个节点通道传感器灵敏度
		char Node_Ch_Sensor_Unit[32][8][20];//每个节点测量通道的单位
		*/
		fclose(fp);
		//获得当前施工阶段信息
		strcpy(para_file_name,Config_Path_Dir);strcat(para_file_name,"\\Sgcfg.txt");
		fp=fopen(para_file_name,"r");
		if(fp!=NULL){
			char tm_chr[200];fgets(tm_chr,200,fp);Step_flag=atoi(tm_chr);
			fclose(fp);
		}else Step_flag=0;
		
		
	}
	else {
		MessageBox("无配置文件,程序将结束运行....");
		//exit(0);田海涛修改
		
	}
}
//发送联络数据包
void CBridge_485Dlg::Fill_485_Connect_Pkt(unsigned char dev_addr)
{
    unsigned char Send_Pkt_Data[100];//发送数据包
	int pkt_len(0);//数据包长度
    unsigned short int CRC_val;
	
	pkt_len=0;
    Send_Pkt_Data[pkt_len]=dev_addr;pkt_len++;//设备地址
    Send_Pkt_Data[pkt_len]=0x46;pkt_len++;
    Send_Pkt_Data[pkt_len]=0;pkt_len++;
	
	
	//______________end_______________//
	CRC_val=Com_CRC_16_Code(Send_Pkt_Data,pkt_len);
	Send_Pkt_Data[pkt_len]=(CRC_val&0x0ff);pkt_len++;
	Send_Pkt_Data[pkt_len]=(CRC_val>>8)&0x0ff;pkt_len++;
	
    char spp[100];
    sprintf(spp,"%x %x %x %x %x %d", Send_Pkt_Data[0],
		Send_Pkt_Data[1],Send_Pkt_Data[2],Send_Pkt_Data[3],Send_Pkt_Data[4],pkt_len);
    MessageBox(spp);
	//发送数据
	TDR_Send_Data_To_Com(Send_Pkt_Data,pkt_len,2);
	
}
//测控网络
void CBridge_485Dlg::Take_Meas_485_Net(unsigned char addr_id)
{
	//addr_id----A/D模块地址
	unsigned char Send_Pkt_Data[100];//发送数据包
	int pkt_len(0);//数据包长度
    unsigned short int CRC_val;
	
	pkt_len=0;
    Send_Pkt_Data[pkt_len]=addr_id;pkt_len++;
    Send_Pkt_Data[pkt_len]=4;pkt_len++;
	
	
	
	Send_Pkt_Data[pkt_len]=0;pkt_len++;
    Send_Pkt_Data[pkt_len]=0;pkt_len++;
	Send_Pkt_Data[pkt_len]=0;pkt_len++;
	Send_Pkt_Data[pkt_len]=8;pkt_len++;
	   
	//______________end_______________//
	CRC_val=Com_CRC_16_Code(Send_Pkt_Data,pkt_len);
	Send_Pkt_Data[pkt_len]=(CRC_val&0x0ff);pkt_len++;
	Send_Pkt_Data[pkt_len]=(CRC_val>>8)&0x0ff;pkt_len++;
	
	char spp[100];
	sprintf(spp,"%x %x %x %x %x %x %x %x %d", Send_Pkt_Data[0],
		Send_Pkt_Data[1],Send_Pkt_Data[2],Send_Pkt_Data[3],Send_Pkt_Data[4],Send_Pkt_Data[5],
		Send_Pkt_Data[6],Send_Pkt_Data[7],pkt_len);
	//MessageBox(spp);
    
	//发送数据
   	TDR_Send_Data_To_Com(Send_Pkt_Data,pkt_len,2);
	//Sleep(2000);//延续时间2
	
	
}
//从测量控制网络获得数据
int CBridge_485Dlg::Fetch_Meas_485_Data(unsigned char *pkt)
{
	int ret_val=TDR_Get_Cur_Buffer_Data(pkt,2);
	return ret_val;
}
//扫描网络节点数据并写入文件
void CBridge_485Dlg::OnFetch485Data() 
{
	// TODO: Add your command handler code here
	int i,j;
	char tmp1[300],tmp2[200],output[300];
	unsigned char pkt[1024];
	int len;
	CString temp = "";
	int Meas_cnt(0);//测量通道计数
					/*	//节点参数
					int Total_Node_Num;//节点总数
					int Node_Ch_num[32];//每个节点测量通道数
					char Node_Ch_Sensor_Name[32][8][20];//每个通道的传感器名称
					double Node_Ch_Sensor_Lmd[32][8];//每个节点通道传感器灵敏度
					char Node_Ch_Sensor_Unit[32][8][20];//每个节点测量通道的单位
	*/
	//测量时间
	CTime m_cur_time=CTime::GetCurrentTime();
	CString ss=m_cur_time.Format("%Y_%m_%d_%H_%M_%S;");
	strcpy(output,ss.operator LPCTSTR());
	CString strTime = m_cur_time.Format("%Y-%m-%d %H:%M:%S");
	DataToCurView.SetAt(0,strTime);
	//MessageBox(output);
	sprintf(tmp1,"%d",Total_Node_Num);//MessageBox(tmp1);
	
	
	
	
	
	
	for(i=0;i<Total_Node_Num;i++) {//测量节点循环
		//	for(j=0;j<Node_Ch_num[i];j++) {//测量通道循环
		Take_Meas_485_Net((unsigned char) (i+1));
		Sleep(1500);
		
		len=Fetch_Meas_485_Data(pkt);
		//sprintf(tmp2,"len=%d",len);
		// MessageBox(tmp2,"test");
		if(len==21) {
			unsigned short int crc_val;
			crc_val=Com_CRC_16_Code(pkt,len-2);//,int buf_len)
			unsigned short int  ret_crc;
			ret_crc=pkt[len-1];ret_crc=(unsigned short int) (ret_crc<<8)&0x0ff00;
			ret_crc+=(unsigned short int) pkt[len-2];
			if(ret_crc==crc_val) {
				for(j=0;j<Node_Ch_num[i];j++){
					
					temp.Format("%d",i+1);////
					DataToCurView.SetAt(1,temp);//计入节点
					temp.Format("%d",j+1);////
					DataToCurView.SetAt(2,temp);//计入通道
					temp.Format("%s",Node_Ch_Sensor_Name[i][j]);////
					DataToCurView.SetAt(3,temp);//计入感应器名称
					
					strcpy(tmp1,output);sprintf(tmp2,"节点%d;通道%d;",i+1,j+1);strcat(tmp1,tmp2);
					strcat(tmp1,Node_Ch_Sensor_Name[i][j]);strcat(tmp1,";");
					unsigned short int xx;short int yy;
					xx=pkt[j*2+3];xx=(xx<<8)&0x0ff00;xx=xx+pkt[j*2+4];
					yy=(short int ) xx;
					double s_val;
					s_val=Com_Sensor_Value(yy,Node_Ch_Sensor_Lmd[i][j]);
					
					temp.Format("%3.2f",Node_Ch_Sensor_Lmd[i][j]);////
					DataToCurView.SetAt(4,temp);//计入灵敏度
					
					Cur_Sensor_Meas_Val[Meas_cnt]=s_val;Meas_cnt++;//把测量参数放入道数组中.
					sprintf(tmp2,"%7.2f",s_val);
					
					temp.Format("%7.2f",s_val);////
					DataToCurView.SetAt(5,temp);//计入数值
					
					////////////////////////////////
					CString s_val_str = "";
					s_val_str.Format("%s",tmp2);
					//WriteToSQL(&s_val_str,i,j,NULL);
					////////////////////////////////
					
					strcat(tmp1,tmp2);
					//sprintf(tmp2,"%7.2f %7.2f",s_val,Cur_Sensor_Meas_Val[Meas_cnt-1]);strcat(tmp1,tmp2);
					strcat(tmp1,";");
					strcat(tmp1,Node_Ch_Sensor_Unit[i][j]);
					
					temp.Format("%s",Node_Ch_Sensor_Unit[i][j]);////
					DataToCurView.SetAt(6,temp);//计入单位
					
					strcat(tmp1,";");strcat(tmp1,Test_Position);
					Display_Meas_Res(IDC_LIST2, tmp1,j);
					
					temp.Format("%s",Test_Position);////
					DataToCurView.SetAt(7,temp);//计入位置
					ASSERT(&DataToCurView != NULL);
					SendData(&DataToCurView);
					
					
					strcat(tmp1,"\n");
					//MessageBox(tmp1);
					Add_Dtat_To_Lib(Meas_Lib_File_Name,tmp1);//测量数据写入文件
					
				}
				// MessageBox("crc ok");
			}
		}
		
		
		//	}
		
	}
	
}
//计算传感器的数据
double CBridge_485Dlg::Com_Sensor_Value(short int xx, double lmd)
{
	double yy(0.0);
	if(lmd<=0.0) return yy;
	yy=(double) xx;
	yy=yy/lmd;
	// char tmp[100];
	// sprintf(tmp,"%7.2f %7.2f %d",lmd,yy,xx);
	//MessageBox(tmp);
	return yy;
	
}
//显示测量结果
void CBridge_485Dlg::Display_Meas_Res(int idc_list, char *str,int flag)
{
	CListBox *ptr;
	ptr=(CListBox *) GetDlgItem(idc_list);
	if(ptr!=NULL) {
		if(flag==0) ptr->ResetContent();
		ptr->AddString(str);
	}
}
//定时测量
void CBridge_485Dlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	int ret(0);Test_fflag=0;
	char cur_state[200],temp_ch[20];
	strcpy(cur_state,"公路桥梁碗扣式满堂支架施工安全预警系统 - ");
	if(Run_Auto_Flag!=0) strcat(cur_state,"定时测量_");
	sprintf(temp_ch,"%d",Step_flag);
	strcat(cur_state,temp_ch);
	if(nIDEvent==10) {
		SetWindowText(cur_state);
		KillTimer(10);
		OnFetch485Data();//定时测量
		Test_Warning_Conditioan();//处理数据报警
		//Cmd_Buffer[0]='\0';
		//_____检查手机信息___
		ret=Fetch_Phone_Buffer_Interval();
		if(ret==1){
			// MessageBox(Cmd_Buffer);
			Resoulation_Cmd_Info();
		}
		//____处理相关命令_____
		Process_Phone_Cmd(1);
		
		
		//	MessageBox("10");
		if(Test_fflag==0) {
			if(Run_Auto_Flag==0) SetTimer(10,2000,NULL);//
			else SetTimer(10,Delay_Time,NULL);//
		}
	}
	if(nIDEvent==20) {//向手机发送数据
		KillTimer(20);
		// MessageBox("20");
		SetTimer(20,Send_Mobile_data_Time,NULL);
	}
	CDialog::OnTimer(nIDEvent);
}
//定时测量数据
void CBridge_485Dlg::OnTimerMeas() 
{
	// TODO: Add your command handler code here
	if(Run_Auto_Flag==0) SetTimer(10,2000,NULL);//
	else {
		SetTimer(10,Delay_Time,NULL);//
		SetTimer(20,Send_Mobile_data_Time,NULL);//定时向手机发送数据
	}
}
//设置运行模式
void CBridge_485Dlg::Set_Run_Mode()
{
	FILE *fp;
	char cfg_name[200];
	char tmp[100];
	int len;
	strcpy(cfg_name,Config_Path_Dir);strcat(cfg_name,"\\Bconfig.txt");
	Run_Auto_Flag=0;//手动运行模式
	fp=fopen(cfg_name,"r");
	if(fp!=NULL){
		fgets(tmp,100,fp);Run_Auto_Flag=atoi(tmp);
		fgets(tmp,100,fp);Delay_Time=atoi(tmp);
		if(Delay_Time<=0) Delay_Time=2000;
		else Delay_Time*=1000;
		//向手机发送数据的时间间隔
		fgets(tmp,100,fp);Send_Mobile_data_Time=atoi(tmp);
		if(Send_Mobile_data_Time<=0) Send_Mobile_data_Time=30*1000;
		else Send_Mobile_data_Time=Send_Mobile_data_Time*60000;
		//手机通讯口号码
		fgets(tmp,100,fp);m_PPort_232=atoi(tmp);
		fgets(baud_str_232,19,fp);len=strlen(baud_str_232);baud_str_232[len-1]='\0';
		//485网络通讯口参数
		fgets(tmp,100,fp);m_PPort_485=atoi(tmp);
		fgets(baud_str_485,19,fp);len=strlen(baud_str_485);baud_str_485[len-1]='\0';
		fclose(fp);
		//打开测控网络
		if(Run_Auto_Flag!=0) {
			flag_485=1;
			OnOpenS485(); 
			//打开232口
			flag_232=1;
			OnOpenS232();
			OnTimerMeas();//启动定时器
		}
		if(Run_Auto_Flag==0) Set_Button_Text(IDC_BUTTON1,"手动模式");
		else Set_Button_Text(IDC_BUTTON1,"定时模式");
	}
	
}
//设置运行模式
void CBridge_485Dlg::Set_Button_Text(int idc_bnt, char *str)
{
	CButton *ptr;
	ptr=(CButton *) GetDlgItem(idc_bnt);
	if(ptr!=NULL) ptr->SetWindowText(str);
}
//当前施工阶段设置
void CBridge_485Dlg::OnSgStep() 
{
	// TODO: Add your command handler code here
	CSg_Step_Selectiong dlg;
	int flag(0);
	//MessageBox(Config_Path_Dir);
	FILE *fp;
	char Step_file_name[200],buf[20];
	strcpy(Step_file_name,Config_Path_Dir);strcat(Step_file_name,"\\Sgcfg.txt");//施工配置文件
	fp=fopen(Step_file_name,"r");
	if(fp!=NULL){
		fgets(buf,10,fp);flag=atoi(buf);
		if((flag<0) || (flag>4)) flag=0;
		fclose(fp);
	}
	else {
		fp=fopen(Step_file_name,"w");
		if(fp!=NULL){
			flag=0;
			strcpy(buf,"0\n");fputs(buf,fp);
			fclose(fp);
		}
		
	}
	dlg.Step_flag=flag;
	if(dlg.DoModal()==IDOK){
		fp=fopen(Step_file_name,"w");
		if(fp!=NULL){
			sprintf(buf,"%d\n",dlg.Step_flag);Step_flag=dlg.Step_flag;
			fputs(buf,fp);fclose(fp);
		}
		
	};
}
//报警文件参数设置
void CBridge_485Dlg::OnWarningPara() 
{
	// TODO: Add your command handler code here
	CSet_Sensor_Warning_Value dlg;
	strcpy(dlg.Cfg_Path,Config_Path_Dir);
	dlg.DoModal();
}
//报警参数功能验证
void CBridge_485Dlg::OnWarningTest() 
{
	// TODO: Add your command handler code here
	CTesting_Warning_Value_Fun dlg;
	strcpy(dlg.Cfg_Path,Config_Path_Dir);
	dlg.DoModal();
}
//检查报警条件
void CBridge_485Dlg::Test_Warning_Conditioan()
{
	/// int Total_Node_Num;//节点总数
	//int Node_Ch_num[32];//每个节点测量通道数
	int ret,i,Warning_Sensor_Num(0),Sensor_Pos[320];
	double SG_Warning_Val[320],warn_info[320];
	
	//判断报警信息
	//获得不同阶段报警数据
	//根据施工阶段不同,获得每个传感器的报警值,成功,返回1,失败,返回0.
	ret=Bridge_Dll_Get_Sensor_Warning_Val(Step_flag,SG_Warning_Val);
	if(ret==0) {
        MessageBox("获得报警信息失败.....");return;
	}
	//显示预警告信息
	int val=Bridge_Dll_Get_Warning_flag(Total_Node_Num,Node_Ch_num,SG_Warning_Val,
		Cur_Sensor_Meas_Val,&Warning_Sensor_Num,Sensor_Pos,warn_info);
	if(val==0) return;
	//处理报警
	if(Warning_Sensor_Num==0) return;//无报警信息
	   
	//显示报警信息
	char warn_msg[200],tmp_chr[200];
	
	strcpy(warn_msg,"报警:\n");
	//strcpy(disp_msg,"warning:");
	for(i=0;i<Warning_Sensor_Num;i++){
		sprintf(tmp_chr,"阶段代码:%d__节点:%d__通道:%d_\n测量:%10.2f__设置:%10.2f\n",Step_flag,Sensor_Pos[i*2],Sensor_Pos[i*2+1],
			warn_info[i*2],warn_info[i*2+1]);strcat(warn_msg,tmp_chr);
		//sprintf(tmp_chr,"%d_%d_%d_%7.1f__%1.1f",Step_flag,Sensor_Pos[i*2],Sensor_Pos[i*2+1],warn_info[i*2],warn_info[i*2+1]);
		//strcat(disp_msg,tmp_chr);
	}
	// SetWindowText(disp_msg);
	MessageBox(warn_msg,warn_msg);
	int len=strlen(warn_msg);if(len>130) warn_msg[130]='\0';
	//发送报警信息
	Test_fflag=1;
	Send_Warning_Msg(warn_msg);
}
//通过收集发送报警信息
void CBridge_485Dlg::Send_Warning_Msg(char *msg)
{
	// TODO: Add your command handler code here
	
	unsigned char pkt[1024];
    unsigned char tmp[100];
	char tmp_file_name[200];
	FILE *fp;
	int i;
	strcpy(tmp_file_name,Config_Path_Dir);strcat(tmp_file_name,"\\Bconfig.txt");//获得配置文件
	fp=fopen(tmp_file_name,"r");
	if(fp==NULL) {
		MessageBox("open config file error",tmp_file_name,MB_OK);
		return;
	}
	for( i=0;i<7;i++) {
		fgets((char *) tmp,100,fp);
		//MessageBox((char *) tmp);
	}
	//取得需要通知的人数
	int Person_Num(0),len;
	fgets((char *) tmp,100,fp);Person_Num=atoi((char *) tmp);
	//sprintf((char *) tmp,"%d",Person_Num);
	//MessageBox((char *) tmp);
    for(i=0;i<Person_Num;i++){//发送短消息
		fgets((char *) tmp,100,fp);//获得接收报警信息的人员名字
		fgets((char *) tmp,100,fp);//获得接收信息手机号
        len=strlen((char *) tmp);tmp[len-1]='\0';
		//MessageBox((char *)tmp);
        strcpy((char *) pkt,"AT+CISMSSEND=");//13866120701,3,中");
		strcat((char *) pkt,(char *) tmp);strcat((char *) pkt,",3,");
		strcat((char *) pkt,msg);//形成完整发送信息
		//MessageBox((char *) pkt);
		//发送信息
		len=strlen((char *) pkt); pkt[len]=0x0d;len++;
		TDR_Send_Data_To_Com(pkt,len,1);
		Sleep(1000);
	}
	if(Person_Num!=0) MessageBox((char *) pkt,"报警信息!!!",MB_OK);
	fclose(fp);
	
}
//无线通讯数据发送
void CBridge_485Dlg::OnTestWirelessData() 
{
	// TODO: Add your command handler code here
	for(int i=0;i<4;i++) Cur_Sensor_Meas_Val[i]=0.0;
    Cur_Sensor_Meas_Val[2]=10.0;Cur_Sensor_Meas_Val[0]=10.0;
	Test_Warning_Conditioan();
}
//从短信息中提取电话号码和命令代码
void CBridge_485Dlg::OnGetPhoneNum() 
{
	// TODO: Add your command handler code here
	char phone_num[20],cmd_id[20],data_buf[20];
	strcpy(Cmd_Buffer,"+CISMS:+8613866120701,15-12-29-19:35,Cb15_1Ce");
	//MessageBox(smsg);
	int ret=Fetch_Phone_Data(Cmd_Buffer, phone_num, cmd_id,data_buf);
	if(ret==0) return;
	//MessageBox(phone_num,cmd_id);
	//	MessageBox(data_buf);
	Control_Command_ID=atoi(cmd_id);//命令代码
	cmd_Dat=atoi(data_buf);//命令数据
	strcpy(cur_phone_num,phone_num);//发送命令收据号码
	Process_Phone_Cmd(0);
	
}
//从命令缓冲区中提取手机号码,命令代码和命令数据
int CBridge_485Dlg::Fetch_Phone_Data(char *buf_ptr, char *phone_num, char *cmd_id, char *dat_ptr)
{
	//数据说明buf_ptr---从收据中接收的的数据
	//phone_num---存储发送短消息的手机号码;cmd_id---命令代码串;dat_ptr---命令携带的数据
	int pkt;int index1,index2,index3,i;
	char tmp_ch[1024];
	int len=strlen(buf_ptr);if(len<=1) return 0;
	for(i=0;i<len;i++) {
		if(buf_ptr[i]=='c') buf_ptr[i]='C';  if(buf_ptr[i]=='b') buf_ptr[i]='B';
		if(buf_ptr[i]=='e') buf_ptr[i]='E';
	}
	CString cs(buf_ptr);
	index1=cs.Find("CISMS:+86");
	if(index1==-1) return 0;
	index2=cs.Find("CB");
	if(index2==-1) return 0;
	index3=cs.Find("CE");
	if(index3==-1) return 0;
	//检验代码的合法性
	int xx[3],yy;
	xx[0]=index1;xx[1]=index2;xx[2]=index3;
	yy=xx[0];
	for(i=0;i<3;i++) if(xx[i]>=yy) yy=xx[i];
	if(yy!=index3){
		// MessageBox("error");
		len=strlen(buf_ptr)-yy;
		memmove(&buf_ptr[0],&buf_ptr[yy+1],len);buf_ptr[len]='\0';
		// MessageBox(buf_ptr);
		return 0;
	}
	//提取电话号码
	pkt=0;
	for(i=index1+9;i<index1+10+10;i++) {phone_num[pkt]=buf_ptr[i];pkt++;}
	phone_num[pkt]='\0';
	//MessageBox(phone_num);
	
	//提取命令代码和数据串
	pkt=0;
	for(i=index2+2;i<index3+2;i++) {tmp_ch[pkt]=buf_ptr[i];pkt++;}
	tmp_ch[pkt]='\0';
	//MessageBox(tmp_ch);
	//生成命令代码
	len=strlen(buf_ptr)-yy-1;
	memmove(&buf_ptr[0],&buf_ptr[yy+2],len);buf_ptr[len]='\0';
	//MessageBox(tmp_ch);   
	CString bs(tmp_ch);
	index1=bs.Find("CE");
	if(index1==-1) return 0;
	index2=bs.Find("_");
	if(index2==-1){
		strcpy(dat_ptr,"0");
		for(i=0;i<index1;i++) cmd_id[i]=tmp_ch[i];
		cmd_id[index1]='\0';
		// MessageBox(cmd_id);
		return 1;
	}
	for(i=0;i<index2;i++) cmd_id[i]=tmp_ch[i];
	cmd_id[i]='\0';
	//MessageBox(cmd_id);
	len=strlen(tmp_ch);
	pkt=0;
	for(i=index2+1;i<len;i++) {
		dat_ptr[pkt]=tmp_ch[i];pkt++;   
	}
	dat_ptr[pkt-2]='\0';
	// MessageBox(dat_ptr);
	
	//if(index1
	
	return 1;
}
//解析从手机接收到的数据
void CBridge_485Dlg::Resoulation_Cmd_Info()
{
	char phone_num[20],cmd_id[20],data_buf[20];
	//	strcpy(smsg,"+CISMS:+8613866120701,15-12-29-19:35,Cb15_1Ce");
	//MessageBox(smsg);
	int ret=Fetch_Phone_Data(Cmd_Buffer, phone_num, cmd_id,data_buf);
	if(ret==0) {Control_Command_ID=0;return;}
	//MessageBox(phone_num,cmd_id);
	//	MessageBox(data_buf);
	Control_Command_ID=atoi(cmd_id);//命令代码
	cmd_Dat=atoi(data_buf);//命令数据
	strcpy(cur_phone_num,phone_num);//发送命令手机号码
	
}
//定期获取手机数据
int CBridge_485Dlg::Fetch_Phone_Buffer_Interval()
{
	unsigned char pkt[2048];
	int index3,index1,index2,len,i;
	int k=TDR_Get_Cur_Buffer_Data(pkt,1);
	if(k>0){
		pkt[k]='\0';
		strcat(Cmd_Buffer,(char *) pkt);
		len=strlen(Cmd_Buffer);if(len<=1) return 0;
        for(i=0;i<len;i++) {
			if(Cmd_Buffer[i]=='c') Cmd_Buffer[i]='C';  if(Cmd_Buffer[i]=='b') Cmd_Buffer[i]='B';
			if(Cmd_Buffer[i]=='e') Cmd_Buffer[i]='E';
		}
		CString cs(Cmd_Buffer);
        index1=cs.Find("CISMS:+86");
        if(index1==-1) return 0;
		index2=cs.Find("CB");
		if(index2==-1) return 0;
		index3=cs.Find("CE");
		if(index3==-1) return 0;
		
		return 1;
	}
	return 0;
}
//处理手机相关的命令
void CBridge_485Dlg::Process_Phone_Cmd(int fflag)
{
	if(Control_Command_ID==0) return;
	switch(Control_Command_ID){
	case 10://查询当前数据
		{
			if(fflag==0) MessageBox("查询当前数据");
			else {
				Send_Cur_Testing_Data(cur_phone_num,1);
			}
		}
		break;
	case 15://设置工作施工阶段
		{
			if(fflag==0) MessageBox("设置工作施工阶段");
			
			else {
				if((cmd_Dat>0) && (cmd_Dat<5))Step_flag=cmd_Dat;
				else {Step_flag=0;cmd_Dat=0;}
				Keep_Step_Flag(Step_flag);//保存设置
				
				Send_Cur_Testing_Data(cur_phone_num,0);
			}
		}
		break;
	case 20://获取当前的工作状态
		{
			if(fflag==0) MessageBox("设置工作施工阶段");
			
			else {
				if((cmd_Dat>0) && (cmd_Dat<5))Step_flag=cmd_Dat;
				else {Step_flag=0;cmd_Dat=0;}
				Keep_Step_Flag(Step_flag);//保存设置
				
				Send_Cur_Testing_Data(cur_phone_num,2);
			}
		}
	default:
		{
			Send_Cur_Testing_Data(cur_phone_num,3);
		}
		break;
	}
	Control_Command_ID=0;
}
//发送当前数据
void CBridge_485Dlg::Send_Cur_Testing_Data(char *phone_num,int flag)
{
    unsigned char pkt[1024];
	char tmp_chr[1024],temp_str[40];
	int len(0),i,j;
	strcpy((char *) pkt,"AT+CISMSSEND=");strcat((char *)pkt,cur_phone_num);
	strcat((char *) pkt,",3,");
	tmp_chr[0]='\0';
	switch(flag){
	case 1://发送当前数据
		{   
			len=0;
			sprintf(temp_str,"%d %d",Total_Node_Num,Node_Ch_num[0]);
			//MessageBox(temp_str);
			for(i=0;i<Total_Node_Num;i++){//节点总数
				for(j=0;j<Node_Ch_num[i];j++){
					sprintf(temp_str,"%d_%d_%d_%10.2f\n",Step_flag,i,j,Cur_Sensor_Meas_Val[len]);
					len++;
					strcat(tmp_chr,temp_str);
					//MessageBox(tmp_chr);
				}
			}
			strcat((char *) pkt,tmp_chr);
		}
		break;
	case 0://回送施工阶段标志
		{
			sprintf(tmp_chr,"施工阶段:%d",Step_flag);
            strcat((char *) pkt,tmp_chr);
		}
		break;
    case 2://获取当前的工作状态---施工的第几阶段
		{
			if(Step_flag==0) strcpy(tmp_chr,"预压20%");
			if(Step_flag==1) strcpy(tmp_chr,"预压80%");
			if(Step_flag==2) strcpy(tmp_chr,"预压100%");
			if(Step_flag==3) strcpy(tmp_chr,"第1次浇铸");
			if(Step_flag==4) strcpy(tmp_chr,"第2次浇铸");
			//sprintf(tmp_chr,"_%d",Step_flag);
			strcat((char *) pkt,tmp_chr);
		}
		break;
	default://回送错误信息
		{
			strcpy(tmp_chr,"命令不支持!!");	strcat((char *) pkt,tmp_chr);
		}
		break;
		
	}
	//发送信息
	len=strlen((char *) pkt); pkt[len]=0x0d;len++;pkt[len]='\0';
	// MessageBox((char *) pkt);
	TDR_Send_Data_To_Com(pkt,len,1);
	// Test_fflag=1;
}


void CBridge_485Dlg::Keep_Step_Flag(int val)
{
	FILE *fp;
	char Step_file_name[200],buf[20];
	strcpy(Step_file_name,Config_Path_Dir);strcat(Step_file_name,"\\Sgcfg.txt");//施工配置文件
	fp=fopen(Step_file_name,"w");
	if(fp!=NULL){
		sprintf(buf,"%d\n",val);fputs(buf,fp);
		fclose(fp);
	}
}
//关闭顶事测量功能.
void CBridge_485Dlg::OnTimerStop() 
{
	// TODO: Add your command handler code here
	KillTimer(10);//
	KillTimer(20);//定时向手机发送数据
}

//DEL double* CBridge_485Dlg::Send_To_History()
//DEL {
//DEL 	Cur_Sensor_Meas_Val[0]=rand()%100 + 0.1;
//DEL 	return Cur_Sensor_Meas_Val;
//DEL }

void CBridge_485Dlg::OnHistLibBrow() 
{
	// TODO: Add your command handler code here
	Browse_History_Data* hdlg = new Browse_History_Data;
	strcpy(hdlg->His_Data_File,Meas_Lib_File_Name);
	hdlg->Create(IDD_HIST_BROW_DIALOG,GetDesktopWindow());
	hdlg->ShowWindow(SW_SHOW);
	
}

void CBridge_485Dlg::OnCurDataBrow() 
{
	// TODO: Add your command handler code here
	for(int i = 0;;)
	{
		if((phdlg[i]!= NULL)&&(IsWindow(phdlg[i]->m_hWnd)))
		{
			i++;
		}
		else
		{
			Brow_Cur_Data_Count = i;
			break;
		}
		if(i == 8)
		{
			AfxMessageBox("监测窗口达到8个,请关闭部分");
			return;
		}
		
	}
	phdlg[Brow_Cur_Data_Count] = new Brow_Cur_Data;
	phdlg[Brow_Cur_Data_Count]->Create(IDD_CUR_DATA_DIALOG,GetDesktopWindow());
	phdlg[Brow_Cur_Data_Count]->ShowWindow(SW_SHOW);
	CString str = "";
	str.Format("%d号实时监测窗口",Brow_Cur_Data_Count+1);
	phdlg[Brow_Cur_Data_Count]->SetWindowText(str);	
}

void CBridge_485Dlg::WriteToSQL(CString *pDataStr, int Node, int Ch, sqlite3 *pdb)
{
/*	CString m_strFolderPath="DataFolder" ;
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
		AfxMessageBox("打开成功");
		
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
		  "(NUM integer primary key autoincrement, DataTime varchar(50),SensorVal integer(15))";
		  rc = sqlite3_exec(db, sqlcmd, NULL, NULL, &ExeErrorMsg);
		  if(rc != SQLITE_OK)
		  AfxMessageBox(ExeErrorMsg);
		  CTime time = CTime::GetCurrentTime();
		  CString Timestr = time.Format("%Y-%m-%d-%H-%M-%S");
		  double val=_ttol(pDataStr->GetBuffer(0));
		  sqlcmd.Format("insert into data (DataTime,SensorVal) values ('%s',%d)",Timestr,val);
		  rc = sqlite3_exec(db, sqlcmd, NULL, NULL, &ExeErrorMsg);
		  if(rc != SQLITE_OK)
		  AfxMessageBox(ExeErrorMsg);
		  
			//AfxMessageBox("");
	sqlite3_close(db);*/
	
	
}

void CBridge_485Dlg::OnButtonTest() 
{
	CTime m_cur_time=CTime::GetCurrentTime();
	CString strTime = m_cur_time.Format("%Y-%m-%d %H:%M:%S");
	CStringArray *Array = new CStringArray;
	Array->SetSize(8);
	Array->SetAt(0,strTime);//计入时间
	CString temp = _T("");
	temp.Format("1");
	Array->SetAt(1,temp);//计入节点
	temp.Format("1");
	Array->SetAt(2,temp);//计入通道
	Array->SetAt(3,"Name");//计入感应器名称
	temp.Format("%4.2f",(rand()%100)/100.0+rand()%5);
	Array->SetAt(4,temp);//计入灵敏度
	temp.Format("%d",rand()%20);
	Array->SetAt(5,temp);//计入数值
	Array->SetAt(6,"Unit");//计入单位
	Array->SetAt(7,"Position");//计入位置*/	
	SendData(Array);
	/*	DataToCurView.Add("123");
	DataToCurView.Add("abc");
	for(int i = 0;i<5;i++)
	{
	if((phdlg[i]!= NULL)&&(IsWindow(phdlg[i]->m_hWnd)))
	{
	phdlg[i]->SendMessage(WM_RECEIVEDATA,i,(LPARAM)(&DataToCurView));
	}
	}
	*/
}

void CBridge_485Dlg::SendData(CStringArray* Array) 
{
	for(int i = 0;i<8;i++)
	{
		if((phdlg[i]!= NULL)&&(IsWindow(phdlg[i]->m_hWnd)))
		{
			phdlg[i]->SendMessage(WM_RECEIVEDATA,i+1,(LPARAM)(Array));
		}
	}
	
}

