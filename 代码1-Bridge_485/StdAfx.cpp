// stdafx.cpp : source file that includes just the standard includes
//	Bridge_485.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

CString GB2312ToUTF8(char* str)
{
	CString result;
	WCHAR *strSrc = NULL;
	TCHAR *szRes = NULL;
	//获得临时变量的大小
	int i;
	i = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);
	strSrc = new WCHAR[i+1];
	MultiByteToWideChar(CP_ACP, 0, str, -1, strSrc, i);
	//获得临时变量的大小
	i = WideCharToMultiByte(CP_UTF8, 0, strSrc, -1, NULL, 0, NULL, NULL);
	szRes = new TCHAR[i+1];
	WideCharToMultiByte(CP_UTF8, 0, strSrc, -1, szRes, i, NULL, NULL);
	result = szRes;   
	if (strSrc != NULL)   
	{    
		delete []strSrc;
		strSrc = NULL;   
	}  
	if (szRes != NULL)   
	{    
		delete []szRes;    
		szRes = NULL;   
	}    
	return result;  
}

CString UTF8ToGB2312(char *str)  
{   
    CString result;   
    WCHAR *strSrc = NULL;   
    TCHAR *szRes = NULL;   
    int i;  // UTF8转换成Unicode   
    i = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);   
    strSrc = new WCHAR[i+1];   
    MultiByteToWideChar(CP_UTF8, 0, str, -1, strSrc, i);  // Unicode转换成GB2312   
    i = WideCharToMultiByte(CP_ACP, 0, strSrc, -1, NULL, 0, NULL, NULL);   
    szRes = new TCHAR[i+1];
    WideCharToMultiByte(CP_ACP, 0, strSrc, -1, szRes, i, NULL, NULL);    
    result = szRes;   
    if (strSrc != NULL)   
    {    
        delete []strSrc;
		strSrc = NULL;   
    }  
    if (szRes != NULL)   
    {    
        delete []szRes;    
        szRes = NULL;   
    }    
    return result;  
}  


