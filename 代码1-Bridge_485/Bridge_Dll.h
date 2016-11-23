#include "stdafx.h"
#define DLLExport __declspec(dllexport)
//设置配置文件目录位置
extern "C" DLLExport void Bridge_DLL_Set_Cfg_Path(char *dir_path);
//根据施工阶段不同,获得每个传感器的报警值,成功,返回1,失败,返回0.
extern "C" DLLExport int Bridge_Dll_Get_Sensor_Warning_Val(int Sg_flag,double *Sensor_Warning_val);
//根据施工阶段不同,计算传感器的报警信息
extern "C" DLLExport int Bridge_Dll_Get_Warning_flag(int Node_Num,int *Node_Ch_Num,double *warning_val,
					double *Meas_val,int *Warning_Sensor_Num,int *Sensor_Pos,double *warn_info);
	//输入参数:Node_Num---节点总数,*Node_Ch_Num---每个节点的通道数;
	//warning_val---预设报警值;Meas_val---当前测量值;
	//输出信息:Warning_Sensor_Num---进入报警的传感器总数;Sensor_Pos---报警的传感器信息(所属节点,所属通道)
	//warn_info---进入报警的传感器数据(先测量值,后报警值)