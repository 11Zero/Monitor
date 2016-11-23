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
!MESSAGE "Bridge_485 - Win32 ReleaseD" (based on "Win32 (x86) Application")
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
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /YX"stdafx.h" /FD /c
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
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /YX"stdafx.h" /FD /GZ /c
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

!ELSEIF  "$(CFG)" == "Bridge_485 - Win32 ReleaseD"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Bridge_485___Win32_ReleaseD"
# PROP BASE Intermediate_Dir "Bridge_485___Win32_ReleaseD"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Bridge_485___Win32_ReleaseD"
# PROP Intermediate_Dir "Bridge_485___Win32_ReleaseD"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /YX"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /Zi /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /YX"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386

!ENDIF 

# Begin Target

# Name "Bridge_485 - Win32 Release"
# Name "Bridge_485 - Win32 Debug"
# Name "Bridge_485 - Win32 ReleaseD"
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

SOURCE=.\CChart.h
# End Source File
# Begin Source File

SOURCE=.\fg_485_Net_Node_dlg.h
# End Source File
# Begin Source File

SOURCE=.\Forecast.h
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
# Begin Group "GridCtrl"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\GridCtrl\AdvComboBox.cpp
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\AdvComboBox.h
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\DropListBox.cpp
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\DropListBox.h
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\DropScrollBar.cpp
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\DropScrollBar.h
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\DropWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\DropWnd.h
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\GridCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\GridCtrl.h
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\includeGridCtrl.h
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\resource.h
# End Source File
# Begin Source File

SOURCE=.\GridCtrl\StdAfx.h
# End Source File
# End Group
# Begin Group "BCG"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\BCG\BCGCBPro.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGCBPro.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGCBProConfig.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGCBProInc.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGCBProVer.h
# End Source File
# Begin Source File

SOURCE=.\BCG\Bcgglobals.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\Bcgglobals.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPAccessibility.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPADOGridCtrl.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPAnalogClock.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPAnalogClock.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPAnimCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPAnimCtrl.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPAppBarWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPAppBarWnd.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPAppointment.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPAppointment.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPAppointmentDS.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPAppointmentDS.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPAppointmentProperty.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPAppointmentProperty.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPAppointmentStorage.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPAppointmentStorage.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPAutoHideButton.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPAutoHideButton.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPAutoHideDockBar.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPAutoHideDockBar.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPAutoHideToolBar.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPAutoHideToolBar.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPBarContainer.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPBarContainer.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPBarContainerManager.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPBarContainerManager.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPBaseControlBar.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPBaseControlBar.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPBaseInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPBaseInfo.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPBaseRibbonElement.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPBaseRibbonElement.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPBaseTabbedBar.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPBaseTabbedBar.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPBaseTabWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPBaseTabWnd.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPBaseToolBar.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPBaseToolBar.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPBreadcrumb.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPBreadcrumb.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPBreadcrumbControlImpl.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPBreadcrumbControlImpl.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPBrushButton.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPBrushButton.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPButton.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPButton.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPCalculator.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPCalculator.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPCalendarBar.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPCalendarBar.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPCalendarMenuButton.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPCalendarMenuButton.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPCaptionBar.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPCaptionBar.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPCaptionButton.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPCaptionButton.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPCaptionMenuButton.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPCaptionMenuButton.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPChartAxis.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPChartAxis.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPChartCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPChartCtrl.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPChartFormat.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPChartFormat.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPChartFormula.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPChartFormula.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPChartImpl.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPChartImpl.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPChartLegend.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPChartLegend.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPChartObject.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPChartObject.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPChartSeries.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPChartSeries.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPChartShape3D.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPChartShape3D.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPChartView.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPChartView.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPChartVisualObject.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPChartVisualObject.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPCircularGaugeImpl.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPCircularGaugeImpl.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPColorBar.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPColorBar.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPColorButton.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPColorButton.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPColorDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPColorDialog.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPColorIndicatorImpl.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPColorIndicatorImpl.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPColorMenuButton.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPColorMenuButton.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPComboBox.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPComboBox.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPCommandManager.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPCommandManager.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPContextMenuManager.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPContextMenuManager.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPControlBar.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPControlBar.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPControlBarImpl.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPControlBarImpl.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPControlRenderer.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPControlRenderer.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPCustomizeMenuButton.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPCustomizeMenuButton.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPD2DDefs.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPDAOGridCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPDAOGridCtrl.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPDateTimeCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPDateTimeCtrl.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPDBGridCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPDBGridCtrl.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPDiagramConnector.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPDiagramConnector.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPDiagramCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPDiagramCtrl.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPDiagramShape.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPDiagramShape.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPDiagramView.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPDiagramView.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPDiagramVisualConstructor.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPDiagramVisualConstructor.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPDiagramVisualContainer.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPDiagramVisualContainer.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPDiagramVisualObject.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPDiagramVisualObject.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPDialog.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPDialogBar.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPDialogBar.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPDlgImpl.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPDlgImpl.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPDockBar.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPDockBar.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPDockBarRow.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPDockBarRow.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPDockingCBWrapper.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPDockingCBWrapper.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPDockingControlBar.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPDockingControlBar.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPDockManager.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPDockManager.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPDragFrameImpl.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPDragFrameImpl.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPDrawManager.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPDrawManager.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPDropDown.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPDropDown.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPDropDownList.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPDropDownList.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPDurationCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPDurationCtrl.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPEdit.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPEditBrushDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPEditBrushDlg.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPEditCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPEditCtrl.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPEditListBox.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPEditListBox.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPEditView.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPEditView.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPEngine3D.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPEngine3D.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPEngine3DOpenGL.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPEngine3DOpenGL.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPExCheckList.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPExCheckList.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPExplorerToolBar.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPExplorerToolBar.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPFileDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPFileDialog.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPFontComboBox.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPFontComboBox.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPFormView.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPFormView.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPFrameImpl.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPFrameImpl.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPFrameWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPFrameWnd.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPFullScreenImpl.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPFullScreenImpl.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPGanttChart.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPGanttChart.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPGanttControl.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPGanttControl.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPGanttGrid.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPGanttGrid.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPGanttItem.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPGanttItem.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPGanttItemStorage.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPGanttItemStorage.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPGanttRenderer.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPGanttRenderer.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPGanttView.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPGanttView.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPGaugeImpl.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPGaugeImpl.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPGestureManager.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPGestureManager.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPGlobalUtils.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPGlobalUtils.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPGraphicsManager.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPGraphicsManager.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPGraphicsManagerD2D.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPGraphicsManagerD2D.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPGraphicsManagerGDI.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPGraphicsManagerGDI.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPGridCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPGridCtrl.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPGridFilter.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPGridFilter.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPGridFilterMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPGridFilterMenu.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPGridSerialize.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPGridSerialize.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPGridView.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPGridView.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPGroup.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPGroup.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPHeaderCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPHeaderCtrl.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPHelpids.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPHotSpotImageCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPHotSpotImageCtrl.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPImageEditDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPImageEditDlg.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPImageGaugeImpl.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPImageGaugeImpl.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPImageProcessing.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPImageProcessing.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPInplaceEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPInplaceEdit.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPInplaceToolTipCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPInplaceToolTipCtrl.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPIntelliSenseLB.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPIntelliSenseLB.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPIntelliSenseWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPIntelliSenseWnd.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPKeyboardManager.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPKeyboardManager.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPKeyboardPage.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPKeyboardPage.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPKeyHelper.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPKeyHelper.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPKeyMapDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPKeyMapDlg.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPKnob.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPKnob.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPLayout.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPLayout.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPLinearGaugeImpl.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPLinearGaugeImpl.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPLineStyleComboBox.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPLineStyleComboBox.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPListBox.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPListBox.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPListCtrl.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPLocalRes.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPLocalResource.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPMainClientAreaWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPMainClientAreaWnd.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPMaskEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPMaskEdit.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPMath.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPMath.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPMDIChildWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPMDIChildWnd.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPMDIFrameWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPMDIFrameWnd.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPMenuBar.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPMenuBar.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPMenuButton.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPMenuButton.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPMenuPage.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPMenuPage.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPMessageBox.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPMessageBox.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPMiniFrameWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPMiniFrameWnd.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPMouseManager.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPMouseManager.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPMousePage.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPMousePage.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPMultiDocTemplate.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPMultiMiniFrameWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPMultiMiniFrameWnd.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPNumericIndicatorImpl.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPNumericIndicatorImpl.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPODBCGridCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPODBCGridCtrl.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPOleCntrFrameWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPOleCntrFrameWnd.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPOleDocIPFrameWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPOleDocIPFrameWnd.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPOleIPFrameWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPOleIPFrameWnd.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPOleServerDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPOleServerDoc.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPOptionsPage.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPOptionsPage.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPOutlineParser.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPOutlineParser.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPOutlookBar.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPOutlookBar.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPOutlookBarDockingPane.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPOutlookBarDockingPane.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPOutlookBarPane.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPOutlookBarPane.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPOutlookButton.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPOutlookButton.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPOutlookWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPOutlookWnd.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPPageTransitionManager.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPPageTransitionManager.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPPlannerClockIcons.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPPlannerClockIcons.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPPlannerDropSource.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPPlannerDropSource.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPPlannerDropTarget.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPPlannerDropTarget.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPPlannerManagerCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPPlannerManagerCtrl.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPPlannerManagerView.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPPlannerManagerView.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPPlannerPrint.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPPlannerPrint.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPPlannerPrintDay.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPPlannerPrintDay.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPPlannerPrintDual.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPPlannerPrintDual.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPPlannerPrintMonth.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPPlannerPrintMonth.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPPlannerPrintWeek.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPPlannerPrintWeek.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPPlannerView.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPPlannerView.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPPlannerViewDay.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPPlannerViewDay.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPPlannerViewMonth.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPPlannerViewMonth.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPPlannerViewMulti.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPPlannerViewMulti.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPPlannerViewWeek.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPPlannerViewWeek.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPPlannerViewWorkWeek.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPPlannerViewWorkWeek.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPPngImage.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPPngImage.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPPopupDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPPopupDlg.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPPopupMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPPopupMenu.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPPopupMenuBar.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPPopupMenuBar.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPPopupWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPPopupWindow.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPPowerColorPicker.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPPowerColorPicker.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPPrintPreviewCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPPrintPreviewCtrl.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPPrintPreviewView.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPPrintPreviewView.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPProgressCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPProgressCtrl.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPProgressDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPProgressDlg.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPPropertyPage.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPPropertyPage.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPPropertySheet.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPPropertySheet.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPPropList.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPPropList.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRadialMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRadialMenu.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPReBar.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPReBar.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRebarState.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRebarState.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRecentDockInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRecentDockInfo.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRecurrence.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRecurrence.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRecurrenceRule.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRecurrenceRule.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRecurrenceRules.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRecurrenceRules.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRegistry.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRegistry.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRenameDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRenameDlg.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPReportCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPReportCtrl.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPReportView.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPReportView.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonBackstagePagePrint.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonBackstagePagePrint.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonBackstagePageRecent.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonBackstagePageRecent.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonBackstageView.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonBackstageView.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonBackstageViewPanel.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonBackstageViewPanel.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonBar.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonBar.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonButton.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonButton.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonButtonsGroup.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonButtonsGroup.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonCategory.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonCategory.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonCheckBox.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonCheckBox.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonCollector.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonCollector.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonColorButton.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonColorButton.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonComboBox.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonComboBox.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonCommandsListBox.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonCommandsListBox.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonConstructor.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonConstructor.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonCustomizationData.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonCustomizationData.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonCustomizePage.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonCustomizePage.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonCustomizeQATPage.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonCustomizeQATPage.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonDialogBar.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonDialogBar.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonEdit.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonElementHostCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonElementHostCtrl.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonFloaty.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonFloaty.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonHyperlink.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonHyperlink.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonInfo.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonInfoLoader.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonInfoLoader.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonInfoWriter.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonInfoWriter.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonItemDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonItemDlg.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonKeyboardCustomizeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonKeyboardCustomizeDlg.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonKeyTip.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonKeyTip.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonLabel.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonLabel.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonMainPanel.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonMainPanel.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonPaletteButton.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonPaletteButton.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonPanel.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonPanel.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonPanelMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonPanelMenu.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonProgressBar.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonProgressBar.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonQuickAccessToolbar.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonQuickAccessToolbar.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonQuickStepsButton.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonQuickStepsButton.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonSlider.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonSlider.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonStatusBar.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonStatusBar.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonStatusBarPane.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonStatusBarPane.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonToolsPage.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonToolsPage.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonTreeCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonTreeCtrl.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonUndoButton.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRibbonUndoButton.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGProMigrate.h
# End Source File
# Begin Source File

SOURCE=.\BCG\bcgprores.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRotationObject.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPRotationObject.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPScrollBar.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPScrollBar.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPSDPlaceMarkerWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPSDPlaceMarkerWnd.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPSelectSkinDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPSelectSkinDlg.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPShadowManager.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPShadowManager.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPShellBreadcrumb.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPShellBreadcrumb.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPShellList.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPShellList.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPShellManager.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPShellManager.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPShellTree.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPShellTree.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPShowAllButton.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPShowAllButton.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPSkinEntry.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPSkinManager.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPSkinManager.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPSlider.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPSlider.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPSliderCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPSliderCtrl.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPSmartDockingManager.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPSmartDockingManager.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPSmartDockingMarker.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPSmartDockingMarker.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPSound.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPSound.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPSpinButtonCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPSpinButtonCtrl.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPSplitterWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPSplitterWnd.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPStatic.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPStatic.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPStaticGaugeImpl.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPStaticGaugeImpl.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPStatusBar.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPStatusBar.h
# End Source File
# Begin Source File

SOURCE=.\BCG\bcgpstyle.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPSwitchImpl.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPSwitchImpl.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPTabbedControlBar.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPTabbedControlBar.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPTabbedToolbar.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPTabbedToolbar.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPTabView.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPTabView.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPTabWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPTabWnd.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPTagCloud.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPTagCloud.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPTagManager.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPTagManager.h
# End Source File
# Begin Source File

SOURCE=.\BCG\bcgptargetver.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPTaskPaneMiniFrameWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPTaskPaneMiniFrameWnd.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPTasksPane.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPTasksPane.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPTearOffManager.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPTearOffManager.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPTextFormatDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPTextFormatDlg.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPTextGaugeImpl.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPTextGaugeImpl.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPToolBar.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPToolBar.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPToolbarButton.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPToolbarButton.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPToolbarComboBoxButton.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPToolbarComboBoxButton.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPToolbarCustomize.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPToolbarCustomize.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPToolbarCustomizePages.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPToolbarCustomizePages.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPToolbarDateTimeCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPToolbarDateTimeCtrl.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPToolbarDropSource.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPToolbarDropSource.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPToolbarDropTarget.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPToolbarDropTarget.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPToolbarEditBoxButton.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPToolbarEditBoxButton.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPToolbarFontCombo.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPToolbarFontCombo.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPToolBarImages.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPToolBarImages.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPToolbarMenuButton.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPToolbarMenuButton.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPToolbarMenuButtonsButton.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPToolbarMenuButtonsButton.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPToolbarSpinEditBoxButton.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPToolbarSpinEditBoxButton.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPToolbarSystemMenuButton.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPToolbarSystemMenuButton.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPToolBox.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPToolBox.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPToolsPage.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPToolsPage.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPToolTipCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPToolTipCtrl.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPTooltipManager.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPTooltipManager.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPTreeCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPTreeCtrl.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPTreeMap.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPTreeMap.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPURLLinkButton.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPURLLinkButton.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPUserTool.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPUserTool.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPUserToolsManager.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPUserToolsManager.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPVisualCollector.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPVisualCollector.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPVisualConstructor.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPVisualConstructor.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPVisualContainer.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPVisualContainer.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPVisualCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPVisualCtrl.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPVisualInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPVisualInfo.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPVisualManager.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPVisualManager.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPVisualManager2003.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPVisualManager2003.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPVisualManager2007.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPVisualManager2007.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPVisualManager2010.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPVisualManager2010.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPVisualManager2013.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPVisualManager2013.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPVisualManagerCarbon.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPVisualManagerCarbon.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPVisualManagerScenic.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPVisualManagerScenic.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPVisualManagerVS2005.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPVisualManagerVS2005.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPVisualManagerVS2008.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPVisualManagerVS2008.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPVisualManagerVS2010.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPVisualManagerVS2010.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPVisualManagerVS2012.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPVisualManagerVS2012.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPVisualManagerXP.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPVisualManagerXP.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPWindowsManagerDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPWindowsManagerDlg.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPWinUITiles.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPWinUITiles.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPWinXPVisualManager.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPWinXPVisualManager.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPWnd.h
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPWorkspace.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\BCGPWorkspace.h
# End Source File
# Begin Source File

SOURCE=.\BCG\ButtonAppearanceDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\ButtonAppearanceDlg.h
# End Source File
# Begin Source File

SOURCE=.\BCG\ButtonsList.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\ButtonsList.h
# End Source File
# Begin Source File

SOURCE=.\BCG\ButtonsTextList.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\ButtonsTextList.h
# End Source File
# Begin Source File

SOURCE=.\BCG\CalendarPopup.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\CalendarPopup.h
# End Source File
# Begin Source File

SOURCE=.\BCG\CmdUsageCount.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\CmdUsageCount.h
# End Source File
# Begin Source File

SOURCE=.\BCG\ColorPage1.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\ColorPage1.h
# End Source File
# Begin Source File

SOURCE=.\BCG\ColorPage2.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\ColorPage2.h
# End Source File
# Begin Source File

SOURCE=.\BCG\ColorPopup.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\ColorPopup.h
# End Source File
# Begin Source File

SOURCE=.\BCG\CustomizeButton.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\CustomizeButton.h
# End Source File
# Begin Source File

SOURCE=.\BCG\ImagePaintArea.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\ImagePaintArea.h
# End Source File
# Begin Source File

SOURCE=.\BCG\KeyAssign.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\KeyAssign.h
# End Source File
# Begin Source File

SOURCE=.\BCG\MenuHash.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\MenuHash.h
# End Source File
# Begin Source File

SOURCE=.\BCG\MenuImages.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\MenuImages.h
# End Source File
# Begin Source File

SOURCE=.\BCG\PropertySheetCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\PropertySheetCtrl.h
# End Source File
# Begin Source File

SOURCE=.\BCG\RegPath.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\RegPath.h
# End Source File
# Begin Source File

SOURCE=.\BCG\resource.h
# End Source File
# Begin Source File

SOURCE=.\BCG\ToolbarNameDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\ToolbarNameDlg.h
# End Source File
# Begin Source File

SOURCE=.\BCG\TrackMouse.cpp
# End Source File
# Begin Source File

SOURCE=.\BCG\TrackMouse.h
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
