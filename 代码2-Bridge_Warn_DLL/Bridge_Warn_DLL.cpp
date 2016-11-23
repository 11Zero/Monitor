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


//ȫ�ֱ���
int Dir_set_flag(0);//0---δ����;1---������
char Cfg_Directory_name[200];//�����ļ�Ŀ¼����

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
//���������ļ�Ŀ¼λ��
extern "C" DLLExport void Bridge_DLL_Set_Cfg_Path(char *dir_path)
{
  strcpy(Cfg_Directory_name,dir_path);strcat(Cfg_Directory_name,"\\");
  //::MessageBox(NULL,Cfg_Directory_name,"dir_name",MB_OK);
  Dir_set_flag=1;//�����ļ�Ŀ¼������
}
//����ʩ���׶β�ͬ,���ÿ���������ı���ֵ,�ɹ�,����1,ʧ��,����0.
extern "C" DLLExport int Bridge_Dll_Get_Sensor_Warning_Val(int Sg_flag,double *Sensor_Warning_val)
{
	char tmp_file[200];
	if(Dir_set_flag==0) return 0;
	 strcpy(tmp_file,Cfg_Directory_name);
	//Sg_flag:0---Ԥѹ20%,1---Ԥѹ80%,2---Ԥѹ100%,3---ʩ����1�ν���,4---ʩ����2�ν���.
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
   //��������
   FILE *fp;
  int index2(0),i,j;
  fp=fopen(tmp_file,"r");
  if(fp==NULL) {
	  ::MessageBox(NULL,"���ļ�����..",tmp_file,MB_OK);
	         return 0;//���ļ�����
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
//����ʩ���׶β�ͬ,���㴫�����ı�����Ϣ
extern "C" DLLExport int Bridge_Dll_Get_Warning_flag(int Node_Num,int *Node_Ch_Num,double *warning_val,
					double *Meas_val,int *Warning_Sensor_Num,int *Sensor_Pos,double *warn_info)
{
	//�������:Node_Num---�ڵ�����,*Node_Ch_Num---ÿ���ڵ��ͨ����;
	//warning_val---Ԥ�豨��ֵ;Meas_val---��ǰ����ֵ;
	//�����Ϣ:Warning_Sensor_Num---���뱨���Ĵ���������;Sensor_Pos---�����Ĵ�������Ϣ(�����ڵ�,����ͨ��)
	//warn_info---���뱨���Ĵ���������(�Ȳ���ֵ,�󱨾�ֵ)
   int kk2(0),kk1(0);
   int i,j;
//  char tmp_chr[200];
   *Warning_Sensor_Num=0;//
    
   for(i=0;i<Node_Num;i++){
	   for(j=0;j<Node_Ch_Num[i];j++){
         // sprintf(tmp_chr,"����:%10.2f ����:%10.2f ",Meas_val[kk1],warning_val[kk1]);
		 // ::MessageBox(NULL,tmp_chr,"comp",MB_OK);
		 if(fabs(Meas_val[kk1])>=fabs(warning_val[kk1])){
           //�����㱨������
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