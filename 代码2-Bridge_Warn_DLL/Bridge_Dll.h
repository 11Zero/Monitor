#include "stdafx.h"
#define DLLExport __declspec(dllexport)
//设置配置文件目录位置
extern "C" DLLExport void Bridge_DLL_Set_Cfg_Path(char *dir_path);