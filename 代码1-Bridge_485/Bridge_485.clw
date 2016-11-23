; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=Brow_Cur_Data
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Bridge_485.h"

ClassCount=12
Class1=CBridge_485App
Class2=CBridge_485Dlg
Class3=CAboutDlg

ResourceCount=14
Resource1=TESTING_WARNING_FUN
Resource2=IDR_MAINFRAME
Resource3=IDD_BRIDGE_485_DIALOG
Resource4=IDD_RS485_PARA
Class4=RS_232_Para
Resource5=IDD_ABOUTBOX
Class5=RS_485_Dlg
Resource6=IDD_SCOMM_PARA
Class6=Mobile_Dlg
Resource7=IDD_SENSOR_WARNING_VALUE
Class7=Cfg_485_Net_Node_dlg
Resource8=IDD_HIST_BROW_DIALOG
Class8=Browse_History_Data
Resource9=IDD_DIALOG1
Class9=CSg_Step_Selectiong
Resource10=IDD_CUR_DATA_DIALOG
Class10=CSet_Sensor_Warning_Value
Resource11=IDD_MOBILE_PHENG
Class11=CTesting_Warning_Value_Fun
Resource12=IDD_SG_STEP_SEL
Resource13=IDD_DIALOG2
Class12=Brow_Cur_Data
Resource14=IDR_MENU1

[CLS:CBridge_485App]
Type=0
HeaderFile=Bridge_485.h
ImplementationFile=Bridge_485.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CBridge_485App

[CLS:CBridge_485Dlg]
Type=0
HeaderFile=Bridge_485Dlg.h
ImplementationFile=Bridge_485Dlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CBridge_485Dlg

[CLS:CAboutDlg]
Type=0
HeaderFile=Bridge_485Dlg.h
ImplementationFile=Bridge_485Dlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_BRIDGE_485_DIALOG]
Type=1
Class=CBridge_485Dlg
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_MSCOMM1,{648A5600-2C6E-101B-82B6-000000000014},1342242816
Control4=IDC_MSCOMM2,{648A5600-2C6E-101B-82B6-000000000014},1342242816
Control5=IDC_LIST2,listbox,1352728833
Control6=IDC_BUTTON1,button,1208025088
Control7=IDC_BUTTON_TEST,button,1342242816

[MNU:IDR_MENU1]
Type=1
Class=CBridge_485Dlg
Command1=ID_MENU_NEW
Command2=IDC_HIST_LIB_BROW
Command3=ID_MENU_CLOSE
Command4=IDD_CLEAR_LIB
Command5=ID_MENU_EXIT
Command6=IDD_TIMER_MEAS
Command7=IDD_TIMER_STOP
Command8=MENU_SG_STEP
Command9=MENU_WARNING_PARA
Command10=IDD_WARNING_TEST
Command11=IDD_GET_PHONE_NUM
Command12=NODE_CONFIG
Command13=IDD_INIT_VAL
Command14=ID1_232_CFG
Command15=IDD_OPEN_S232
Command16=IDD2_485_CFG
Command17=IDD_OPEN_S485
Command18=WARNING_CONFIG
Command19=IDC_CUR_DATA_BROW
Command20=ID_MENUITEM32801
Command21=ID_MENUITEM32807
Command22=ID_MENUITEM32808
Command23=IDD_SHOUJI_COM
Command24=IDD_485_COM
Command25=IDD_FETCH_485_DATA
Command26=ID1_232_SEND
Command27=ID1_RECEIVE_232
Command28=IDD_TEST_WIRELESS_DATA
Command29=ID2_SEND_485
Command30=ID2_RECEIVE_485
CommandCount=30

[DLG:IDD_SCOMM_PARA]
Type=1
Class=RS_232_Para
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_COMBO1,combobox,1344339970
Control8=IDC_COMBO2,combobox,1344339970
Control9=IDC_COMBO3,combobox,1478557698
Control10=IDC_COMBO4,combobox,1478557698

[CLS:RS_232_Para]
Type=0
HeaderFile=RS_232_Para.h
ImplementationFile=RS_232_Para.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

[DLG:IDD_RS485_PARA]
Type=1
Class=RS_485_Dlg
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_COMBO1,combobox,1344339970
Control8=IDC_COMBO2,combobox,1344339970
Control9=IDC_COMBO3,combobox,1478557698
Control10=IDC_COMBO4,combobox,1478557698

[CLS:RS_485_Dlg]
Type=0
HeaderFile=RS_485_Dlg.h
ImplementationFile=RS_485_Dlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_COMBO1

[DLG:IDD_MOBILE_PHENG]
Type=1
Class=Mobile_Dlg
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342178055
Control4=IDC_COMBO1,combobox,1344339970
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT1,edit,1484849280
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT2,edit,1484849280
Control9=IDC_BUTTON1,button,1476460544
Control10=IDC_BUTTON2,button,1476460544

[CLS:Mobile_Dlg]
Type=0
HeaderFile=Mobile_Dlg.h
ImplementationFile=Mobile_Dlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

[DLG:IDD_DIALOG1]
Type=1
Class=Cfg_485_Net_Node_dlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST1,listbox,1352728833

[CLS:Cfg_485_Net_Node_dlg]
Type=0
HeaderFile=fg_485_Net_Node_dlg.h
ImplementationFile=fg_485_Net_Node_dlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

[DLG:IDD_DIALOG2]
Type=1
Class=Browse_History_Data
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1208025088
Control3=IDC_BUTTON1,button,1342242816
Control4=IDC_BUTTON2,button,1208025088
Control5=IDC_LIST2,listbox,1352728833

[CLS:Browse_History_Data]
Type=0
HeaderFile=Browse_History_Data.h
ImplementationFile=Browse_History_Data.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=Browse_History_Data

[DLG:IDD_SG_STEP_SEL]
Type=1
Class=CSg_Step_Selectiong
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_RADIO1,button,1342308361
Control4=IDC_RADIO2,button,1342177289
Control5=IDC_RADIO3,button,1342177289
Control6=IDC_RADIO4,button,1342177289
Control7=IDC_RADIO5,button,1342177289

[CLS:CSg_Step_Selectiong]
Type=0
HeaderFile=Sg_Step_Selectiong.h
ImplementationFile=Sg_Step_Selectiong.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_RADIO2

[DLG:IDD_SENSOR_WARNING_VALUE]
Type=1
Class=CSet_Sensor_Warning_Value
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342178055
Control4=IDC_RADIO1,button,1342308361
Control5=IDC_RADIO2,button,1342177289
Control6=IDC_RADIO3,button,1342177289
Control7=IDC_RADIO4,button,1342177289
Control8=IDC_RADIO5,button,1342177289
Control9=IDC_STEP_PHASE,button,1342178055
Control10=IDC_LIST1,listbox,1352728833

[CLS:CSet_Sensor_Warning_Value]
Type=0
HeaderFile=Set_Sensor_Warning_Value.h
ImplementationFile=Set_Sensor_Warning_Value.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

[DLG:TESTING_WARNING_FUN]
Type=1
Class=CTesting_Warning_Value_Fun
ControlCount=11
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342178055
Control4=IDC_LIST1,listbox,1352728832
Control5=IDC_BUTTON1,button,1342242816
Control6=IDC_STATIC,button,1342178055
Control7=IDC_RADIO1,button,1342308361
Control8=IDC_RADIO2,button,1342177289
Control9=IDC_RADIO3,button,1342177289
Control10=IDC_RADIO4,button,1342177289
Control11=IDC_RADIO5,button,1342177289

[CLS:CTesting_Warning_Value_Fun]
Type=0
HeaderFile=Testing_Warning_Value_Fun.h
ImplementationFile=Testing_Warning_Value_Fun.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

[DLG:IDD_HIST_BROW_DIALOG]
Type=1
Class=?
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_BROWSE_BUTTON,button,1342242817
Control4=IDC_CHART_HISTROY,ChartCtrl,1375797248
Control5=IDC_SCROLLBAR_HIST,scrollbar,1342177280
Control6=IDC_CLOSE_HIST,button,1342242816

[DLG:IDD_CUR_DATA_DIALOG]
Type=1
Class=Brow_Cur_Data
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_TEMPBUTTON,button,1342242816
Control4=IDC_CHART,ChartCtrl,1375797248
Control5=IDC_BUTTON_DRAW,button,1342242816
Control6=IDC_COMBO_NODE,combobox,1344339971
Control7=IDC_STATIC,static,1342308352
Control8=IDC_COMBO_CHANNEL,combobox,1344339971
Control9=IDC_STATIC,static,1342308352
Control10=IDC_FIELD_GRID,static,1073741842

[CLS:Brow_Cur_Data]
Type=0
HeaderFile=Brow_Cur_Data.h
ImplementationFile=Brow_Cur_Data.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_FIELD_GRID

