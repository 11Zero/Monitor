#include "stdafx.h"
#define DLLExport __declspec(dllexport)
//���������ļ�Ŀ¼λ��
extern "C" DLLExport void Bridge_DLL_Set_Cfg_Path(char *dir_path);
//����ʩ���׶β�ͬ,���ÿ���������ı���ֵ,�ɹ�,����1,ʧ��,����0.
extern "C" DLLExport int Bridge_Dll_Get_Sensor_Warning_Val(int Sg_flag,double *Sensor_Warning_val);
//����ʩ���׶β�ͬ,���㴫�����ı�����Ϣ
extern "C" DLLExport int Bridge_Dll_Get_Warning_flag(int Node_Num,int *Node_Ch_Num,double *warning_val,
					double *Meas_val,int *Warning_Sensor_Num,int *Sensor_Pos,double *warn_info);
	//�������:Node_Num---�ڵ�����,*Node_Ch_Num---ÿ���ڵ��ͨ����;
	//warning_val---Ԥ�豨��ֵ;Meas_val---��ǰ����ֵ;
	//�����Ϣ:Warning_Sensor_Num---���뱨���Ĵ���������;Sensor_Pos---�����Ĵ�������Ϣ(�����ڵ�,����ͨ��)
	//warn_info---���뱨���Ĵ���������(�Ȳ���ֵ,�󱨾�ֵ)