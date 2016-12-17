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
#include "Bridge_Dll.h"//������̬��ͷ�ļ�
#include "Brow_Cur_Data.h"
#include "InitSensorVal.h"

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
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_WM_CREATE()
	ON_WM_CANCELMODE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBridge_485Dlg message handlers

BOOL CBridge_485Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetWindowPos(&wndNoTopMost,0,0,0,0, SWP_NOMOVE | SWP_NOSIZE);
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
	InitValOfSensor[0]=0.0;//���׶θ�Ӧ����ʼֵ��ʼ��
	InitValOfSensor[1]=0.0;
	InitValOfSensor[2]=0.0;
	InitValOfSensor[3]=0.0;
	InitValOfSensor[4]=0.0;
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	flag_232=flag_485=0;//δ���ò���
	SetWindowText("�Ϸʹ�ҵ��ѧ��ľ��ˮ������ѧԺ");
	// TODO: Add extra initialization here
	//���ִ���ļ���ǰ����Ŀ¼
	::GetCurrentDirectory(199,(LPTSTR) Cur_Path_Dir);
	strcpy(Config_Path_Dir,Cur_Path_Dir);strcat(Config_Path_Dir,"\\Config");//�����ļ�Ŀ¼
	   Bridge_DLL_Set_Cfg_Path(Config_Path_Dir);//���������ļ�Ŀ¼
	   //  AfxMessageBox(Config_Path_Dir);
	   strcpy(Meas_Path_Dir,Cur_Path_Dir);strcat(Meas_Path_Dir,"\\Mdata");//�����ļ������ݿ��ļ�Ŀ¼
	   strcpy(Meas_Lib_File_Name,Meas_Path_Dir);strcat(Meas_Lib_File_Name,"\\MeasData.txt");
	   //�ļ�����
	   //Add_Dtat_To_Lib(Meas_Lib_File_Name,"2001;Node1;Ch1;10.5mm\n");
	   //AfxMessageBox(Meas_Path_Dir);
	   //AfxMessageBox(Cur_Path_Dir);
	   //����������Ϣ__������������
	   Load_Node_Info();//
	   Control_Command_ID=0;Cmd_Buffer[0]='\0';
	   //��������ģʽ
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
//����ͨѶ�ڲ�������
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
//�������ͨѶ��������
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
//��232�����öԻ���
void CBridge_485Dlg::Open_232_Port()
{
	// TODO: Add your control notification handler code here
	//	char spc[100];
	//sprintf(spc,"port=%d",m_PPort);
	//AfxMessageBox(spc);
	char tmp_str[30];
    
	if(flag_232==0) return;
    //MessageBox("23222");
	m_comm1.SetCommPort(m_PPort_232);//m_Port);//���ô���
	m_comm1.SetInputMode(1);//�������ݶ�ȡ��ʽΪ������
	strcpy(tmp_str,baud_str_232);strcat(tmp_str,",n,8,1");
	//MessageBox(tmp_str);
	m_comm1.SetSettings(tmp_str);//�������
	//m_Comm.SetSettings("115200,n,8,1");//�������
	m_comm1.SetRThreshold(1);//����������һ���ַ��Ϳ��Խ���
	m_comm1.SetInBufferSize(2048);//���ջ������Ĵ�С
	m_comm1.SetOutBufferSize(2048);//���ͻ�������С
	m_comm1.SetInBufferCount(0);//��ս��ջ�����
	if(!m_comm1.GetPortOpen())
	{
		m_comm1.SetPortOpen(true);//�򿪴���
		//	Dis_Button(IDC_BUTTON1,0);
		//	Dis_Button(IDC_BUTTON2,1);
		//Dis_Button(IDC_BUTTON3,1);
		//	com_open_flag=1;//���п��Ѵ�
		//	char ss1[100];
		//sprintf(ss1,"Serial_Num=%d",m_PPort_232);
		//MessageBox(tmp_str,ss1);
	}	
}
//��485�����öԻ���
void CBridge_485Dlg::Open_485_Port()
{
	// TODO: Add your control notification handler code here
	//	char spc[100];
	//sprintf(spc,"port=%d",m_PPort);
	//AfxMessageBox(spc);
	char tmp_str[30];
	if(flag_485==0) return;
	m_comm2.SetCommPort(m_PPort_485);//m_Port);//���ô���
	m_comm2.SetInputMode(1);//�������ݶ�ȡ��ʽΪ������
	strcpy(tmp_str,baud_str_485);strcat(tmp_str,",n,8,1");
	//MessageBox(tmp_str);
	m_comm2.SetSettings(tmp_str);//�������
	//m_Comm.SetSettings("115200,n,8,1");//�������
	m_comm2.SetRThreshold(1);//����������һ���ַ��Ϳ��Խ���
	m_comm2.SetInBufferSize(2048);//���ջ������Ĵ�С
	m_comm2.SetOutBufferSize(2048);//���ͻ�������С
	m_comm2.SetInBufferCount(0);//��ս��ջ�����
	if(!m_comm2.GetPortOpen())
	{
		m_comm2.SetPortOpen(true);//�򿪴���
		//	Dis_Button(IDC_BUTTON1,0);
		//	Dis_Button(IDC_BUTTON2,1);
		//	Dis_Button(IDC_BUTTON3,1);
		//com_open_flag=1;//���п��Ѵ�
		//MessageBox("485 opened");
		//char tmp[100];
		//	sprintf(tmp,"serial_num=%d",m_PPort_485);
		//	MessageBox(tmp,(char *) tmp_str);
	}	
}
//�����ߴ��п�
void CBridge_485Dlg::OnOpenS232() 
{
	// TODO: Add your command handler code here
	if(m_comm1.GetPortOpen())
	{
		m_comm1.SetPortOpen(false);//�رմ���
		Open_232_Port();
	}
	else {
		Open_232_Port();
	}
}
//�򿪲������п�
void CBridge_485Dlg::OnOpenS485() 
{
	// TODO: Add your command handler code here
	if(m_comm2.GetPortOpen())
	{
		m_comm2.SetPortOpen(false);//�رմ���
		Open_485_Port(); 
	}
	else {
		Open_485_Port(); 
		
	}
}
//�Ӵ��пڷ�������
void CBridge_485Dlg::TDR_Send_Data_To_Com(unsigned char *send_buf, int data_len,int which_channel)
{
	//which_channel=1,�ֻ���;=2,485��
	CByteArray m_Array;//����������
	m_Array.SetSize(data_len);
	for(int i=0;i<data_len;i++)//Ϊ���鸳ֵ
	{
		m_Array.SetAt(i,send_buf[i]); 
		
	}
	switch(which_channel) {
	case 1://�ֻ���
		{
			if(m_comm1.GetPortOpen()){
				// MessageBox("���ֻ���������");
				m_comm1.SetOutput(COleVariant(m_Array));//��������
			}
		}
		break;
	case 2://������
		{
			if(m_comm2.GetPortOpen()){
				//MessageBox("��485��������");
				m_comm2.SetOutput(COleVariant(m_Array));//��������
			}
		}
		break;
	}
	
}
//���ֻ���������
void CBridge_485Dlg::On232_Send() 
{
	// TODO: Add your command handler code here
	unsigned char pkt[1024];
    unsigned char tmp[100];
	//for(int i=0;i<5;i++) { sprintf((char *) tmp,"%d",i);pkt[i]=tmp[0];}
	strcpy((char *) pkt,"AT+CISMSSEND=13866120701,3,�й���ѧ������ѧ234");
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
//���ֻ���������
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
//���ؽڵ㷢������
void CBridge_485Dlg::OnSend_485() 
{
	// TODO: Add your command handler code here
	//	unsigned char pkt[20];
	//	for(int i=0;i<5;i++) pkt[i]=i*5;
	//TDR_Send_Data_To_Com(pkt,5,2);
	Fill_485_data_Pkt();//����RTU ���ݰ�
}
//�Ӳ������ƽڵ��������
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
//��õ�ǰ������������,����ֵΪ��ǰ�����ݳ���
int CBridge_485Dlg::TDR_Get_Cur_Buffer_Data(unsigned char *buf,int which_channel)
{
	int k(0);
	VARIANT m_input;
	switch(which_channel) {
	case 1:
		{
			k=m_comm1.GetInBufferCount();//���ջ������ַ���
			if(k>0) {
				m_input=m_comm1.GetInput();
				memmove(buf, (unsigned char*)m_input.parray->pvData,k);
			}
			
		}
		break;
	case 2:
		{
			k=m_comm2.GetInBufferCount();//���ջ������ַ���
			if(k>0) {
				m_input=m_comm2.GetInput();
				memmove(buf, (unsigned char*)m_input.parray->pvData,k);
			}
		}
		break;
	}
	
	return k;
}
//��������
void CBridge_485Dlg::On_BaoJing_Config() 
{
	// TODO: Add your command handler code here
	char cfg_name[200];
    Mobile_Dlg mobile_dlg;
	//���������ļ�
	strcpy(cfg_name,Config_Path_Dir);strcat(cfg_name,"\\Bconfig.txt");
	strcpy(mobile_dlg.Cfg_File_name,cfg_name);
	
	mobile_dlg.DoModal();
}
//����485���ݷ��������
void CBridge_485Dlg::Fill_485_data_Pkt()
{
    unsigned char Send_Pkt_Data[100];//�������ݰ�
	int pkt_len(0);//���ݰ�����
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
	//��������
   	TDR_Send_Data_To_Com(Send_Pkt_Data,pkt_len,2);
	
}
//����CRC-16У�����
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
//485����������ƽڵ��������
void CBridge_485Dlg::OnConfig_para() 
{
	// TODO: Add your command handler code here
	Cfg_485_Net_Node_dlg r485_para_dlg;
	char para_file_name[200];
	//�����ļ���
	strcpy(para_file_name,Config_Path_Dir);strcat(para_file_name,"\\Bpara.txt");
	// MessageBox(para_file_name);
	strcpy(r485_para_dlg.Cfg_File_Name,para_file_name);
	r485_para_dlg.DoModal();
}
//������������ӵ����ݿ��ļ�
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
//������������ļ�����
void CBridge_485Dlg::OnLibBrow() 
{
	// TODO: Add your command handler code here
	
}

void CBridge_485Dlg::OnClearLib() 
{
	// TODO: Add your command handler code here
	if(MessageBox("���������ļ�?","��ѡ��.......",MB_YESNO)==IDYES){
		FILE *fpt;
		fpt=fopen(Meas_Lib_File_Name,"w");
		if(fpt!=NULL) fclose(fpt);
	} 
}
//����ֻ�ͨѶ
int CBridge_485Dlg::Check_ShouJi_Comm()
{
	int ret(0);
	// TODO: Add your command handler code here
	
    unsigned char pkt[2048]; //unsigned char tmp[100];
	int k=TDR_Get_Cur_Buffer_Data(pkt,1);
	
	
	
	
	//for(int i=0;i<5;i++) { sprintf((char *) tmp,"%d",i);pkt[i]=tmp[0];}
	strcpy((char *) pkt,"AT");//+CISMSSEND=13866120701,3,�й���ѧ������ѧ234");
	
	
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
//���485ͨѶ����
int CBridge_485Dlg::Check_485_Comm()
{
	int ret(0);
	unsigned char pkt[2048];
	TDR_Get_Cur_Buffer_Data(pkt,2);
	Fill_485_Connect_Pkt(1);
   	Sleep(2000);//����ʱ��
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
//�ֻ�ģ��ͨѶ���
void CBridge_485Dlg::OnShoujiCom() 
{
	// TODO: Add your command handler code here
	int ret_val;
	ret_val=Check_ShouJi_Comm();
	if(ret_val==0)MessageBox("���������쳣");
	else MessageBox("������������____OK_______");
}
//485ͨѶ������
void CBridge_485Dlg::On485Com_ch() 
{
	// TODO: Add your command handler code here
	int ret_val;
	ret_val=Check_485_Comm();
	if(ret_val==0)MessageBox("��������쳣");
	else MessageBox("�����������______OK_______");
}
//��������������ʼֵ
void CBridge_485Dlg::OnInitVal() 
{
	// TODO: Add your command handler code here
	//
	InitSensorVal dlg;
	if(!dlg.DoModal())
		MessageBox("��������ʼֵ���ô��޷���");
}
//�������ļ��л�ò���������ڵ��������Ϣ
void CBridge_485Dlg::Load_Node_Info()
{
	FILE *fp;
	char para_file_name[200];
	char tmp[100] ;//,tmp1[100];
	int i,j,len;
	//�����ļ���
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
				//����������
				strcpy(Node_Ch_Sensor_Name[i][j],tmp);
				// MessageBox(Node_Ch_Sensor_Name[i][j]);
				//������������
				fgets(tmp,100,fp); Node_Ch_Sensor_Lmd[i][j]=atof(tmp);
				//sprintf(tmp1,"lmd=%5.3f",Node_Ch_Sensor_Lmd[i][j]);
				// MessageBox(tmp1);
				//��������λ
				fgets(tmp,100,fp);len=strlen(tmp);tmp[len-1]='\0';
				strcpy(Node_Ch_Sensor_Unit[i][j],tmp);
				//MessageBox(Node_Ch_Sensor_Unit[i][j]);
				
			}
		}     
		
		/*
		//�ڵ����
		int Total_Node_Num;//�ڵ�����
		int Node_Ch_num[32];//ÿ���ڵ����ͨ����
		char Node_Ch_Sensor_Name[32][8][20];//ÿ��ͨ���Ĵ���������
		double Node_Ch_Sensor_Lmd[32][8];//ÿ���ڵ�ͨ��������������
		char Node_Ch_Sensor_Unit[32][8][20];//ÿ���ڵ����ͨ���ĵ�λ
		*/
		fclose(fp);
		//��õ�ǰʩ���׶���Ϣ
		strcpy(para_file_name,Config_Path_Dir);strcat(para_file_name,"\\Sgcfg.txt");
		fp=fopen(para_file_name,"r");
		if(fp!=NULL){
			char tm_chr[200];fgets(tm_chr,200,fp);Step_flag=atoi(tm_chr);
			fclose(fp);
		}else Step_flag=0;
		
		
	}
	else {
		MessageBox("�������ļ�,���򽫽�������....");
		//exit(0);�ﺣ���޸�
		
	}
}
//�����������ݰ�
void CBridge_485Dlg::Fill_485_Connect_Pkt(unsigned char dev_addr)
{
    unsigned char Send_Pkt_Data[100];//�������ݰ�
	int pkt_len(0);//���ݰ�����
    unsigned short int CRC_val;
	
	pkt_len=0;
    Send_Pkt_Data[pkt_len]=dev_addr;pkt_len++;//�豸��ַ
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
	//��������
	TDR_Send_Data_To_Com(Send_Pkt_Data,pkt_len,2);
	
}
//�������
void CBridge_485Dlg::Take_Meas_485_Net(unsigned char addr_id)
{
	//addr_id----A/Dģ���ַ
	unsigned char Send_Pkt_Data[100];//�������ݰ�
	int pkt_len(0);//���ݰ�����
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
    
	//��������
   	TDR_Send_Data_To_Com(Send_Pkt_Data,pkt_len,2);
	//Sleep(2000);//����ʱ��2
	
	
}
//�Ӳ�����������������
int CBridge_485Dlg::Fetch_Meas_485_Data(unsigned char *pkt)
{
	int ret_val=TDR_Get_Cur_Buffer_Data(pkt,2);
	return ret_val;
}
//ɨ������ڵ����ݲ�д���ļ�
void CBridge_485Dlg::OnFetch485Data() 
{
	// TODO: Add your command handler code here
	int i,j;
	char tmp1[300],tmp2[200],output[300];
	unsigned char pkt[1024];
	int len;
	int Meas_cnt(0);//����ͨ������
					/*	//�ڵ����
					int Total_Node_Num;//�ڵ�����
					int Node_Ch_num[32];//ÿ���ڵ����ͨ����
					char Node_Ch_Sensor_Name[32][8][20];//ÿ��ͨ���Ĵ���������
					double Node_Ch_Sensor_Lmd[32][8];//ÿ���ڵ�ͨ��������������
					char Node_Ch_Sensor_Unit[32][8][20];//ÿ���ڵ����ͨ���ĵ�λ
	*/
	//����ʱ��
	CTime m_cur_time=CTime::GetCurrentTime();
	CString ss=m_cur_time.Format("%Y_%m_%d_%H_%M_%S;");
	strcpy(output,ss.operator LPCTSTR());
	
	//MessageBox(output);
	sprintf(tmp1,"%d",Total_Node_Num);//MessageBox(tmp1);
	
	
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
	int rc = sqlite3_open(ss,&db);
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
	}*/

	
	
	CTime t;
	for(i=0;i<Total_Node_Num;i++) {//�����ڵ�ѭ��
		//	for(j=0;j<Node_Ch_num[i];j++) {//����ͨ��ѭ��
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
					memset(DataPackItem,0,sizeof(DataPackItem)/sizeof(DataPackItem[0][0]));
					strcpy(tmp1,output);
					sprintf(DataPackItem[0],"%d",i+1);
					sprintf(DataPackItem[1],"%d",j+1);
					sprintf(tmp2,"�ڵ�%d;ͨ��%d;",i+1,j+1);
					strcat(tmp1,tmp2);
					strcat(tmp1,Node_Ch_Sensor_Name[i][j]);
					sprintf(DataPackItem[2],"%s",Node_Ch_Sensor_Name[i][j]);
					strcat(tmp1,";");
					unsigned short int xx;short int yy;
					xx=pkt[j*2+3];xx=(xx<<8)&0x0ff00;xx=xx+pkt[j*2+4];
					yy=(short int ) xx;
					double s_val;
					s_val=Com_Sensor_Value(yy,Node_Ch_Sensor_Lmd[i][j]);
					sprintf(DataPackItem[3],"%.4f",s_val);
					
					Cur_Sensor_Meas_Val[Meas_cnt]=s_val-InitValOfSensor[Step_flag];Meas_cnt++;//�Ѳ������������������.
					sprintf(DataPackItem[4],"%.4f",InitValOfSensor[Step_flag]);
					sprintf(tmp2,"%7.2f",s_val);
					strcat(tmp1,tmp2);
					//sprintf(tmp2,"%7.2f %7.2f",s_val,Cur_Sensor_Meas_Val[Meas_cnt-1]);strcat(tmp1,tmp2);
					strcat(tmp1,";");
					strcat(tmp1,Node_Ch_Sensor_Unit[i][j]);
					sprintf(DataPackItem[5],"%s",Node_Ch_Sensor_Unit[i][j]);
					strcat(tmp1,";");strcat(tmp1,Test_Position);
					sprintf(DataPackItem[6],"%s",Test_Position);
					t = CTime::GetCurrentTime();
					sprintf(DataPackItem[7],"%d:%d:%d",t.GetHour(),t.GetMinute(),t.GetSecond());
					SendPack();//�������ݰ�
					Display_Meas_Res(IDC_LIST2, tmp1,j);
					strcat(tmp1,"\n");
					//MessageBox(tmp1);
					Add_Dtat_To_Lib(Meas_Lib_File_Name,tmp1);//��������д���ļ�
					
				}
				// MessageBox("crc ok");
			}
		}
		
		
		//	}
		
	}
	
}
//���㴫����������
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
//��ʾ�������
void CBridge_485Dlg::Display_Meas_Res(int idc_list, char *str,int flag)
{
	CListBox *ptr;
	ptr=(CListBox *) GetDlgItem(idc_list);
	if(ptr!=NULL) {
		if(flag==0) ptr->ResetContent();
		ptr->AddString(str);
	}
}
//��ʱ����
void CBridge_485Dlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	int ret(0);Test_fflag=0;
	char cur_state[200],temp_ch[20];
	strcpy(cur_state,"�Ϸʹ�ҵ��ѧ��ˮѧԺ_");
	if(Run_Auto_Flag!=0) strcat(cur_state,"��ʱ����_");
	sprintf(temp_ch,"%d",Step_flag);
	strcat(cur_state,temp_ch);
	if(nIDEvent==10) {
		SetWindowText(cur_state);
		KillTimer(10);
		OnFetch485Data();//��ʱ����
		Test_Warning_Conditioan();//�������ݱ���
		//Cmd_Buffer[0]='\0';
		//_____����ֻ���Ϣ___
		ret=Fetch_Phone_Buffer_Interval();
		if(ret==1){
			// MessageBox(Cmd_Buffer);
			Resoulation_Cmd_Info();
		}
		//____�����������_____
		Process_Phone_Cmd(1);
		
		
		//	MessageBox("10");
		if(Test_fflag==0) {
			if(Run_Auto_Flag==0) SetTimer(10,2000,NULL);//
			else SetTimer(10,Delay_Time,NULL);//
		}
	}
	if(nIDEvent==20) {//���ֻ���������
		KillTimer(20);
		// MessageBox("20");
		SetTimer(20,Send_Mobile_data_Time,NULL);
	}
	CDialog::OnTimer(nIDEvent);
}
//��ʱ��������
void CBridge_485Dlg::OnTimerMeas() 
{
	// TODO: Add your command handler code here
	if(Run_Auto_Flag==0) SetTimer(10,2000,NULL);//
	else {
		SetTimer(10,Delay_Time,NULL);//
		SetTimer(20,Send_Mobile_data_Time,NULL);//��ʱ���ֻ���������
	}
}
//��������ģʽ
void CBridge_485Dlg::Set_Run_Mode()
{
	FILE *fp;
	char cfg_name[200];
	char tmp[100];
	int len;
	strcpy(cfg_name,Config_Path_Dir);strcat(cfg_name,"\\Bconfig.txt");
	Run_Auto_Flag=0;//�ֶ�����ģʽ
	fp=fopen(cfg_name,"r");
	if(fp!=NULL){
		fgets(tmp,100,fp);Run_Auto_Flag=atoi(tmp);
		fgets(tmp,100,fp);Delay_Time=atoi(tmp);
		if(Delay_Time<=0) Delay_Time=2000;
		else Delay_Time*=1000;
		//���ֻ��������ݵ�ʱ����
		fgets(tmp,100,fp);Send_Mobile_data_Time=atoi(tmp);
		if(Send_Mobile_data_Time<=0) Send_Mobile_data_Time=30*1000;
		else Send_Mobile_data_Time=Send_Mobile_data_Time*60000;
		//�ֻ�ͨѶ�ں���
		fgets(tmp,100,fp);m_PPort_232=atoi(tmp);
		fgets(baud_str_232,19,fp);len=strlen(baud_str_232);baud_str_232[len-1]='\0';
		//485����ͨѶ�ڲ���
		fgets(tmp,100,fp);m_PPort_485=atoi(tmp);
		fgets(baud_str_485,19,fp);len=strlen(baud_str_485);baud_str_485[len-1]='\0';
		fclose(fp);
		//�򿪲������
		if(Run_Auto_Flag!=0) {
			flag_485=1;
			OnOpenS485(); 
			//��232��
			flag_232=1;
			OnOpenS232();
			OnTimerMeas();//������ʱ��
		}
		if(Run_Auto_Flag==0) Set_Button_Text(IDC_BUTTON1,"�ֶ�ģʽ");
		else Set_Button_Text(IDC_BUTTON1,"��ʱģʽ");
	}
	
}
//��������ģʽ
void CBridge_485Dlg::Set_Button_Text(int idc_bnt, char *str)
{
	CButton *ptr;
	ptr=(CButton *) GetDlgItem(idc_bnt);
	if(ptr!=NULL) ptr->SetWindowText(str);
}
//��ǰʩ���׶�����
void CBridge_485Dlg::OnSgStep() 
{
	// TODO: Add your command handler code here
	CSg_Step_Selectiong dlg;
	int flag(0);
	//MessageBox(Config_Path_Dir);
	FILE *fp;
	char Step_file_name[200],buf[20];
	strcpy(Step_file_name,Config_Path_Dir);strcat(Step_file_name,"\\Sgcfg.txt");//ʩ�������ļ�
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
//�����ļ���������
void CBridge_485Dlg::OnWarningPara() 
{
	// TODO: Add your command handler code here
	CSet_Sensor_Warning_Value dlg;
	strcpy(dlg.Cfg_Path,Config_Path_Dir);
	dlg.DoModal();
}
//��������������֤
void CBridge_485Dlg::OnWarningTest() 
{
	// TODO: Add your command handler code here
	CTesting_Warning_Value_Fun dlg;
	strcpy(dlg.Cfg_Path,Config_Path_Dir);
	dlg.DoModal();
}
//��鱨������
void CBridge_485Dlg::Test_Warning_Conditioan()
{
	/// int Total_Node_Num;//�ڵ�����
	//int Node_Ch_num[32];//ÿ���ڵ����ͨ����
	int ret,i,Warning_Sensor_Num(0),Sensor_Pos[320];
	double SG_Warning_Val[320],warn_info[320];
	
	//�жϱ�����Ϣ
	//��ò�ͬ�׶α�������
	//����ʩ���׶β�ͬ,���ÿ���������ı���ֵ,�ɹ�,����1,ʧ��,����0.
	ret=Bridge_Dll_Get_Sensor_Warning_Val(Step_flag,SG_Warning_Val);
	if(ret==0) {
        MessageBox("��ñ�����Ϣʧ��.....");return;
	}
	//��ʾԤ������Ϣ
	int val=Bridge_Dll_Get_Warning_flag(Total_Node_Num,Node_Ch_num,SG_Warning_Val,
		Cur_Sensor_Meas_Val,&Warning_Sensor_Num,Sensor_Pos,warn_info);
	if(val==0) return;
	//������
	if(Warning_Sensor_Num==0) return;//�ޱ�����Ϣ
	   
	//��ʾ������Ϣ
	char warn_msg[200],tmp_chr[200];
	
	strcpy(warn_msg,"����:\n");
	//strcpy(disp_msg,"warning:");
	for(i=0;i<Warning_Sensor_Num;i++){
		sprintf(tmp_chr,"�׶δ���:%d__�ڵ�:%d__ͨ��:%d_\n����:%10.2f__����:%10.2f\n",Step_flag,Sensor_Pos[i*2],Sensor_Pos[i*2+1],
			warn_info[i*2],warn_info[i*2+1]);strcat(warn_msg,tmp_chr);
		//sprintf(tmp_chr,"%d_%d_%d_%7.1f__%1.1f",Step_flag,Sensor_Pos[i*2],Sensor_Pos[i*2+1],warn_info[i*2],warn_info[i*2+1]);
		//strcat(disp_msg,tmp_chr);
	}
	// SetWindowText(disp_msg);
	MessageBox(warn_msg,warn_msg);
	int len=strlen(warn_msg);if(len>130) warn_msg[130]='\0';
	//���ͱ�����Ϣ
	Test_fflag=1;
	Send_Warning_Msg(warn_msg);
}
//ͨ���ռ����ͱ�����Ϣ
void CBridge_485Dlg::Send_Warning_Msg(char *msg)
{
	// TODO: Add your command handler code here
	
	unsigned char pkt[1024];
    unsigned char tmp[100];
	char tmp_file_name[200];
	FILE *fp;
	int i;
	strcpy(tmp_file_name,Config_Path_Dir);strcat(tmp_file_name,"\\Bconfig.txt");//��������ļ�
	fp=fopen(tmp_file_name,"r");
	if(fp==NULL) {
		MessageBox("open config file error",tmp_file_name,MB_OK);
		return;
	}
	for( i=0;i<7;i++) {
		fgets((char *) tmp,100,fp);
		//MessageBox((char *) tmp);
	}
	//ȡ����Ҫ֪ͨ������
	int Person_Num(0),len;
	fgets((char *) tmp,100,fp);Person_Num=atoi((char *) tmp);
	//sprintf((char *) tmp,"%d",Person_Num);
	//MessageBox((char *) tmp);
    for(i=0;i<Person_Num;i++){//���Ͷ���Ϣ
		fgets((char *) tmp,100,fp);//��ý��ձ�����Ϣ����Ա����
		fgets((char *) tmp,100,fp);//��ý�����Ϣ�ֻ���
        len=strlen((char *) tmp);tmp[len-1]='\0';
		//MessageBox((char *)tmp);
        strcpy((char *) pkt,"AT+CISMSSEND=");//13866120701,3,��");
		strcat((char *) pkt,(char *) tmp);strcat((char *) pkt,",3,");
		strcat((char *) pkt,msg);//�γ�����������Ϣ
		//MessageBox((char *) pkt);
		//������Ϣ
		len=strlen((char *) pkt); pkt[len]=0x0d;len++;
		TDR_Send_Data_To_Com(pkt,len,1);
		Sleep(1000);
	}
	if(Person_Num!=0) MessageBox((char *) pkt,"������Ϣ!!!",MB_OK);
	fclose(fp);
	
}
//����ͨѶ���ݷ���
void CBridge_485Dlg::OnTestWirelessData() 
{
	// TODO: Add your command handler code here
	for(int i=0;i<4;i++) Cur_Sensor_Meas_Val[i]=0.0;
    Cur_Sensor_Meas_Val[2]=10.0;Cur_Sensor_Meas_Val[0]=10.0;
	Test_Warning_Conditioan();
}
//�Ӷ���Ϣ����ȡ�绰������������
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
	Control_Command_ID=atoi(cmd_id);//�������
	cmd_Dat=atoi(data_buf);//��������
	strcpy(cur_phone_num,phone_num);//���������վݺ���
	Process_Phone_Cmd(0);
	
}
//�������������ȡ�ֻ�����,����������������
int CBridge_485Dlg::Fetch_Phone_Data(char *buf_ptr, char *phone_num, char *cmd_id, char *dat_ptr)
{
	//����˵��buf_ptr---���վ��н��յĵ�����
	//phone_num---�洢���Ͷ���Ϣ���ֻ�����;cmd_id---������봮;dat_ptr---����Я��������
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
	//�������ĺϷ���
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
	//��ȡ�绰����
	pkt=0;
	for(i=index1+9;i<index1+10+10;i++) {phone_num[pkt]=buf_ptr[i];pkt++;}
	phone_num[pkt]='\0';
	//MessageBox(phone_num);
	
	//��ȡ�����������ݴ�
	pkt=0;
	for(i=index2+2;i<index3+2;i++) {tmp_ch[pkt]=buf_ptr[i];pkt++;}
	tmp_ch[pkt]='\0';
	//MessageBox(tmp_ch);
	//�����������
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
//�������ֻ����յ�������
void CBridge_485Dlg::Resoulation_Cmd_Info()
{
	char phone_num[20],cmd_id[20],data_buf[20];
	//	strcpy(smsg,"+CISMS:+8613866120701,15-12-29-19:35,Cb15_1Ce");
	//MessageBox(smsg);
	int ret=Fetch_Phone_Data(Cmd_Buffer, phone_num, cmd_id,data_buf);
	if(ret==0) {Control_Command_ID=0;return;}
	//MessageBox(phone_num,cmd_id);
	//	MessageBox(data_buf);
	Control_Command_ID=atoi(cmd_id);//�������
	cmd_Dat=atoi(data_buf);//��������
	strcpy(cur_phone_num,phone_num);//���������ֻ�����
	
}
//���ڻ�ȡ�ֻ�����
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
//�����ֻ���ص�����
void CBridge_485Dlg::Process_Phone_Cmd(int fflag)
{
	if(Control_Command_ID==0) return;
	switch(Control_Command_ID){
	case 10://��ѯ��ǰ����
		{
			if(fflag==0) MessageBox("��ѯ��ǰ����");
			else {
				Send_Cur_Testing_Data(cur_phone_num,1);
			}
		}
		break;
	case 15://���ù���ʩ���׶�
		{
			if(fflag==0) MessageBox("���ù���ʩ���׶�");
			
			else {
				if((cmd_Dat>0) && (cmd_Dat<5))Step_flag=cmd_Dat;
				else {Step_flag=0;cmd_Dat=0;}
				Keep_Step_Flag(Step_flag);//��������
				
				Send_Cur_Testing_Data(cur_phone_num,0);
			}
		}
		break;
	case 20://��ȡ��ǰ�Ĺ���״̬
		{
			if(fflag==0) MessageBox("���ù���ʩ���׶�");
			
			else {
				if((cmd_Dat>0) && (cmd_Dat<5))Step_flag=cmd_Dat;
				else {Step_flag=0;cmd_Dat=0;}
				Keep_Step_Flag(Step_flag);//��������
				
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
//���͵�ǰ����
void CBridge_485Dlg::Send_Cur_Testing_Data(char *phone_num,int flag)
{
    unsigned char pkt[1024];
	char tmp_chr[1024],temp_str[40];
	int len(0),i,j;
	strcpy((char *) pkt,"AT+CISMSSEND=");strcat((char *)pkt,cur_phone_num);
	strcat((char *) pkt,",3,");
	tmp_chr[0]='\0';
	switch(flag){
	case 1://���͵�ǰ����
		{   
			len=0;
			sprintf(temp_str,"%d %d",Total_Node_Num,Node_Ch_num[0]);
			//MessageBox(temp_str);
			for(i=0;i<Total_Node_Num;i++){//�ڵ�����
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
	case 0://����ʩ���׶α�־
		{
			sprintf(tmp_chr,"ʩ���׶�:%d",Step_flag);
            strcat((char *) pkt,tmp_chr);
		}
		break;
    case 2://��ȡ��ǰ�Ĺ���״̬---ʩ���ĵڼ��׶�
		{
			if(Step_flag==0) strcpy(tmp_chr,"Ԥѹ20%");
			if(Step_flag==1) strcpy(tmp_chr,"Ԥѹ80%");
			if(Step_flag==2) strcpy(tmp_chr,"Ԥѹ100%");
			if(Step_flag==3) strcpy(tmp_chr,"��1�ν���");
			if(Step_flag==4) strcpy(tmp_chr,"��2�ν���");
			//sprintf(tmp_chr,"_%d",Step_flag);
			strcat((char *) pkt,tmp_chr);
		}
		break;
	default://���ʹ�����Ϣ
		{
			strcpy(tmp_chr,"���֧��!!");	strcat((char *) pkt,tmp_chr);
		}
		break;
		
	}
	//������Ϣ
	len=strlen((char *) pkt); pkt[len]=0x0d;len++;pkt[len]='\0';
	// MessageBox((char *) pkt);
	TDR_Send_Data_To_Com(pkt,len,1);
	// Test_fflag=1;
}


void CBridge_485Dlg::Keep_Step_Flag(int val)
{
	FILE *fp;
	char Step_file_name[200],buf[20];
	strcpy(Step_file_name,Config_Path_Dir);strcat(Step_file_name,"\\Sgcfg.txt");//ʩ�������ļ�
	fp=fopen(Step_file_name,"w");
	if(fp!=NULL){
		sprintf(buf,"%d\n",val);fputs(buf,fp);
		fclose(fp);
	}
}
//�رն��²�������.
void CBridge_485Dlg::OnTimerStop() 
{
	// TODO: Add your command handler code here
	KillTimer(10);//
	KillTimer(20);//��ʱ���ֻ���������
}

double* CBridge_485Dlg::Send_To_History()
{
	Cur_Sensor_Meas_Val[0]=rand()%100 + 0.1;
	return Cur_Sensor_Meas_Val;
}

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
	Curhdlg = new Brow_Cur_Data;
	Curhdlg->Create(IDD_CUR_DATA_DIALOG,GetDesktopWindow());
	Curhdlg->ShowWindow(SW_SHOW);
	
	
}

void CBridge_485Dlg::OnButton3() 
{
	if(Curhdlg!=NULL)
		Curhdlg->PostMessage(WM_RECEIVEMSG,3,rand()%20);
	// TODO: Add your control notification handler code here
	
}

int CBridge_485Dlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}

void CBridge_485Dlg::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}

void CBridge_485Dlg::SendPack()
{

}
