// Bridge_485Dlg.h : header file
//
//{{AFX_INCLUDES()
#include "mscomm.h"
//}}AFX_INCLUDES

#if !defined(AFX_BRIDGE_485DLG_H__CA58FB38_53A6_45F7_905C_C9EDD6BB6169__INCLUDED_)
#define AFX_BRIDGE_485DLG_H__CA58FB38_53A6_45F7_905C_C9EDD6BB6169__INCLUDED_
#include "Brow_Cur_Data.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define WM_RECEIVEMSG WM_USER+100
/////////////////////////////////////////////////////////////////////////////
// CBridge_485Dlg dialog

class CBridge_485Dlg : public CDialog
{
// Construction
public:
	void SendPack();
	Brow_Cur_Data* Curhdlg;
	double* Send_To_History();
	double TestData;
	void OnLibBrow() ;
	void Keep_Step_Flag(int val);
	void Send_Cur_Testing_Data(char *phone_num,int flag);
	void Process_Phone_Cmd(int fflag);
	int Fetch_Phone_Buffer_Interval(void);
	void Resoulation_Cmd_Info(void);
	int Fetch_Phone_Data(char *buf_ptr,char *phone_num,char *cmd_id,char *dat_ptr);
	void Send_Warning_Msg(char *msg);
	void Test_Warning_Conditioan(void);
	void Set_Button_Text(int idc_bnt,char *str);
	void Set_Run_Mode();
	void Display_Meas_Res(int idc_list,char *str,int flag);
	double Com_Sensor_Value(short int xx,double lmd);
	int Fetch_Meas_485_Data(unsigned char *pkt);
	void Take_Meas_485_Net(unsigned char addr_id);
	void Load_Node_Info();
	int Check_485_Comm();
	int Check_ShouJi_Comm();
	void Add_Dtat_To_Lib(char *file_name,char *str);
	void Fill_485_data_Pkt();
	void Open_485_Port();
	void Open_232_Port();
	CBridge_485Dlg(CWnd* pParent = NULL);	// standard constructor
	void TDR_Send_Data_To_Com(unsigned char *send_buf, int data_len,int which_channel);//��������
	int TDR_Get_Cur_Buffer_Data(unsigned char *buf,int which_channel);//��������
	unsigned short int Com_CRC_16_Code(unsigned char *buf,int buf_len);
    void Fill_485_Connect_Pkt(unsigned char dev_addr);//�����������ݰ�

    int m_PPort_232,m_PPort_485;//���пں���
	char baud_str_232[20],baud_str_485[20];//������
	int flag_232,flag_485;
	//ȫ�ֱ���
	char Cur_Path_Dir[200];//��ǰ�ļ����ڵ�Ŀ¼
	char Config_Path_Dir[200];//�����ļ�Ŀ¼
	char Meas_Path_Dir[200];//�����ļ������ݿ��ļ�Ŀ¼
	char Meas_Lib_File_Name[200];//�������ݿ��ļ�����
	//�ڵ����
	int Total_Node_Num;//�ڵ�����
	int Node_Ch_num[32];//ÿ���ڵ����ͨ����
	char Node_Ch_Sensor_Name[32][8][20];//ÿ��ͨ���Ĵ���������
	double Node_Ch_Sensor_Lmd[32][8];//ÿ���ڵ�ͨ��������������
	char Node_Ch_Sensor_Unit[32][8][20];//ÿ���ڵ����ͨ���ĵ�λ
	char Test_Position[100];//ʵ��ص�
    //�Զ����б�־
	int Run_Auto_Flag;//0--�ֶ�;1--�Զ�
	int Delay_Time;//����ʱ����
	int Send_Mobile_data_Time;//���ֻ��������ݵ�ʱ����
	double Cur_Sensor_Meas_Val[320];//��ǰ������������ֵ
    //��ǰʩ���׶α�־
	int Step_flag;
	int Test_fflag;
//�����ֻ��Ŀ�������
	int Control_Command_ID;//�������
	int cmd_Dat;//��������
	char Cmd_Buffer[2048];//�������
	char cur_phone_num[40];//�ռ�����
	double InitValOfSensor[5];//��Ӧ����ʼֵ��˳��ΪԤѹ1��Ԥѹ2��Ԥѹ3��ʩ��1��ʩ��2
	char DataPackItem[8][50];//һ��ʱ���Ĳ������ݴ����1�ڵ㣬2ͨ����3���ƣ�4ԭʼֵ��ת��󡿣�5��ʼֵ��6��λ��7�ص㣬8ʱ��
// Dialog Data
	//{{AFX_DATA(CBridge_485Dlg)
	enum { IDD = IDD_BRIDGE_485_DIALOG };
	CMSComm	m_comm1;//RS_232
	CMSComm	m_comm2;//RS_485
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBridge_485Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CBridge_485Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnOnCommMscomm1();
	afx_msg void OnOnCommMscomm2();
	afx_msg void On232Cfg();
	afx_msg void On485Cfg();
	afx_msg void OnOpenS232();
	afx_msg void OnOpenS485();
	afx_msg void On232_Send();
	afx_msg void OnReceive_232();
	afx_msg void OnSend_485();
	afx_msg void OnReceive_485();
	afx_msg void On_BaoJing_Config();
	afx_msg void OnConfig_para();
	afx_msg void OnClearLib();
	afx_msg void OnShoujiCom();
	afx_msg void On485Com_ch();
	afx_msg void OnInitVal();
	afx_msg void OnFetch485Data();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnTimerMeas();
	afx_msg void OnSgStep();
	afx_msg void OnWarningPara();
	afx_msg void OnWarningTest();
	afx_msg void OnTestWirelessData();
	afx_msg void OnGetPhoneNum();
	afx_msg void OnTimerStop();
	afx_msg void OnHistLibBrow();
	afx_msg void OnCurDataBrow();
	afx_msg void OnButton3();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnCancelMode();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BRIDGE_485DLG_H__CA58FB38_53A6_45F7_905C_C9EDD6BB6169__INCLUDED_)
