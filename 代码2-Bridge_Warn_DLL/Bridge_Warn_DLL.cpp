// Bridge_Warn_DLL.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "Bridge_Warn_DLL.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define DLLExport __declspec(dllexport)


//全局变量
int Dir_set_flag(0);//0---未设置;1---已设置
char Cfg_Directory_name[200];//配置文件目录名称

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CBridge_Warn_DLLApp

BEGIN_MESSAGE_MAP(CBridge_Warn_DLLApp, CWinApp)
	//{{AFX_MSG_MAP(CBridge_Warn_DLLApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBridge_Warn_DLLApp construction

CBridge_Warn_DLLApp::CBridge_Warn_DLLApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CBridge_Warn_DLLApp object

CBridge_Warn_DLLApp theApp;
//设置配置文件目录位置
extern "C" DLLExport void Bridge_DLL_Set_Cfg_Path(char *dir_path)
{
  strcpy(Cfg_Directory_name,dir_path);strcat(Cfg_Directory_name,"\\");
  //::MessageBox(NULL,Cfg_Directory_name,"dir_name",MB_OK);
  Dir_set_flag=1;//配置文件目录已设置
}
//根据施工阶段不同,获得每个传感器的报警值,成功,返回1,失败,返回0.
extern "C" DLLExport int Bridge_Dll_Get_Sensor_Warning_Val(int Sg_flag,double *Sensor_Warning_val)
{
	char tmp_file[200];
	if(Dir_set_flag==0) return 0;
	 strcpy(tmp_file,Cfg_Directory_name);
	//Sg_flag:0---预压20%,1---预压80%,2---预压100%,3---施工第1次浇铸,4---施工第2次浇铸.
	switch(Sg_flag){
    case 0:{
		    strcat(tmp_file,"YY_Step1.txt");
		   }
		break;
	case 1:
		{
          strcat(tmp_file,"YY_Step2.txt");
		}
		break;
	case 2:
		{
          strcat(tmp_file,"YY_Step3.txt");
		}
		break;
	case 3:
		{
			 strcat(tmp_file,"SG_Step1.txt");
		}
		break;
	case 4:
		{
           strcat(tmp_file,"SG_Step2.txt");
		}
		break;
	default:
		return 0;
	}
     //::MessageBox(NULL,tmp_file,"dir_name",MB_OK);
   //返回数据
   FILE *fp;
  int index2(0),i,j;
  fp=fopen(tmp_file,"r");
  if(fp==NULL) {
	  ::MessageBox(NULL,"打开文件错误..",tmp_file,MB_OK);
	         return 0;//打开文件错误
  }
  char tmp_chr[200];
  int Sensor_Cnt,Node_Num;
  fgets(tmp_chr,20,fp);Sensor_Cnt=atoi(tmp_chr);
  //sprintf(tmp_chr,"node_num=%d",*Node_Num);
  //MessageBox(tmp_chr);
  for(i=0;i<Sensor_Cnt;i++){
       fgets(tmp_chr,200,fp);Node_Num=atoi(tmp_chr);
      // sprintf(tmp_chr,"node_num=%d",Node_Num[index1]);
       //MessageBox(tmp_chr);
	   for( j=0;j<Node_Num;j++){
         fgets(tmp_chr,200,fp);Sensor_Warning_val[index2]=atof(tmp_chr);
         //sprintf(tmp_chr,"node_num=%10.3f",Sensor_Val[index2]);
         //MessageBox(tmp_chr);
		 index2++;
	   }
	   
  }
  fclose(fp);
  return 1;
}
//根据施工阶段不同,计算传感器的报警信息
extern "C" DLLExport int Bridge_Dll_Get_Warning_flag(int Node_Num,int *Node_Ch_Num,double *warning_val,
					double *Meas_val,int *Warning_Sensor_Num,int *Sensor_Pos,double *warn_info)
{
	//输入参数:Node_Num---节点总数,*Node_Ch_Num---每个节点的通道数;
	//warning_val---预设报警值;Meas_val---当前测量值;
	//输出信息:Warning_Sensor_Num---进入报警的传感器总数;Sensor_Pos---报警的传感器信息(所属节点,所属通道)
	//warn_info---进入报警的传感器数据(先测量值,后报警值)
   int kk2(0),kk1(0);
   int i,j;
//  char tmp_chr[200];
   *Warning_Sensor_Num=0;//
    
   for(i=0;i<Node_Num;i++){
	   for(j=0;j<Node_Ch_Num[i];j++){
         // sprintf(tmp_chr,"测量:%10.2f 报警:%10.2f ",Meas_val[kk1],warning_val[kk1]);
		 // ::MessageBox(NULL,tmp_chr,"comp",MB_OK);
		 if(fabs(Meas_val[kk1])>=fabs(warning_val[kk1])){
           //已满足报警条件
			 *Warning_Sensor_Num=(*Warning_Sensor_Num)+1;
			 Sensor_Pos[kk2*2]=i;Sensor_Pos[kk2*2+1]=j;
			 warn_info[kk2*2]=Meas_val[kk1];warn_info[kk2*2+1]=warning_val[kk1];
			 kk2++;
		 }
		 kk1++;
        
	   }
	 }
   return 1;
}