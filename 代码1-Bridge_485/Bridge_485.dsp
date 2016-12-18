# Microsoft Developer Studio Project File - Name="Bridge_485" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Bridge_485 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Bridge_485.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Bridge_485.mak" CFG="Bridge_485 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Bridge_485 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Bridge_485 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Bridge_485 - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Bridge_485 - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /YX"stdafx.h" /FD /GZ /Zm1000 /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Bridge_485 - Win32 Release"
# Name "Bridge_485 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Bridge_485.cpp
# End Source File
# Begin Source File

SOURCE=.\Bridge_485.rc
# End Source File
# Begin Source File

SOURCE=.\Bridge_485Dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Brow_Cur_Data.cpp
# End Source File
# Begin Source File

SOURCE=.\Browse_History_Data.cpp
# End Source File
# Begin Source File

SOURCE=.\fg_485_Net_Node_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Forecast.cpp
# End Source File
# Begin Source File

SOURCE=.\InitSensorVal.cpp
# End Source File
# Begin Source File

SOURCE=.\Mobile_Dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\mscomm.cpp
# End Source File
# Begin Source File

SOURCE=.\RS_232_Para.cpp
# End Source File
# Begin Source File

SOURCE=.\RS_485_Dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Set_Sensor_Warning_Value.cpp
# End Source File
# Begin Source File

SOURCE=.\Sg_Step_Selectiong.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Testing_Warning_Value_Fun.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Bridge_485.h
# End Source File
# Begin Source File

SOURCE=.\Bridge_485Dlg.h
# End Source File
# Begin Source File

SOURCE=.\Bridge_Dll.h
# End Source File
# Begin Source File

SOURCE=.\Brow_Cur_Data.h
# End Source File
# Begin Source File

SOURCE=.\Browse_History_Data.h
# End Source File
# Begin Source File

SOURCE=.\fg_485_Net_Node_dlg.h
# End Source File
# Begin Source File

SOURCE=.\Forecast.h
# End Source File
# Begin Source File

SOURCE=.\InitSensorVal.h
# End Source File
# Begin Source File

SOURCE=.\Mobile_Dlg.h
# End Source File
# Begin Source File

SOURCE=.\mscomm.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\RS_232_Para.h
# End Source File
# Begin Source File

SOURCE=.\RS_485_Dlg.h
# End Source File
# Begin Source File

SOURCE=.\Set_Sensor_Warning_Value.h
# End Source File
# Begin Source File

SOURCE=.\Sg_Step_Selectiong.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Testing_Warning_Value_Fun.h
# End Source File
# End Group
# Begin Group "ChartCtrl"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ChartCtrl\ChartAxis.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartAxis.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartAxisLabel.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartAxisLabel.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartBalloonLabel.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartBalloonLabel.inl
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartBarSerie.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartBarSerie.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartCandlestickSerie.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartCandlestickSerie.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartCrossHairCursor.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartCrossHairCursor.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartCtrl.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartCursor.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartCursor.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartDateTimeAxis.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartDateTimeAxis.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartDragLineCursor.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartDragLineCursor.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartFont.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartFont.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartGanttSerie.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartGanttSerie.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartGradient.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartGradient.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartGrid.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartGrid.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartLabel.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartLabel.inl
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartLegend.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartLegend.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartLineSerie.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartLineSerie.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartLogarithmicAxis.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartLogarithmicAxis.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartMouseListener.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartPointsArray.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartPointsArray.inl
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartPointsSerie.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartPointsSerie.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartScrollBar.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartScrollBar.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartSerie.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartSerie.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartSerieBase.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartSerieBase.inl
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartSeriesMouseListener.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartStandardAxis.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartStandardAxis.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartString.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartSurfaceSerie.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartSurfaceSerie.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartTitle.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartTitle.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartXYSerie.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\ChartXYSerie.h
# End Source File
# Begin Source File

SOURCE=.\ChartCtrl\PointsOrdering.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Bridge_485.ico
# End Source File
# Begin Source File

SOURCE=.\res\Bridge_485.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\Bridge_Warn_DLL.lib
# End Source File
# End Target
# End Project
# Section Bridge_485 : {648A5600-2C6E-101B-82B6-000000000014}
# 	2:21:DefaultSinkHeaderFile:mscomm.h
# 	2:16:DefaultSinkClass:CMSComm
# End Section
# Section Bridge_485 : {E6E17E90-DF38-11CF-8E74-00A0C90F26F8}
# 	2:5:Class:CMSComm
# 	2:10:HeaderFile:mscomm.h
# 	2:8:ImplFile:mscomm.cpp
# End Section
