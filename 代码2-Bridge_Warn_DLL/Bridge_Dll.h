#include "stdafx.h"
#define DLLExport __declspec(dllexport)
//���������ļ�Ŀ¼λ��
extern "C" DLLExport void Bridge_DLL_Set_Cfg_Path(char *dir_path);