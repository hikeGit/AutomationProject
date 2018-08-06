// AutomationProject.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
//#include "DB\Access\AccessData.h"
#include <memory>
#include <afx.h>
using namespace std;

#define _DEBUG

unique_ptr<char[]> CStringToCharIndicator(CString strtemp)
{	
	//注意：以下n和len的值大小不同,n是按字符计算的，len是按字节计算的
	int n = strtemp.GetLength();
	//获取宽字节字符的大小，大小是按字节计算的
	int len = WideCharToMultiByte(CP_ACP, 0, strtemp, strtemp.GetLength(), NULL, 0, NULL, NULL);
	char * pFileName = new char[len + 1];   //以字节为单位
	unique_ptr<char[]> pFileName1(pFileName);
	WideCharToMultiByte(CP_ACP, 0, strtemp, strtemp.GetLength(),pFileName, len, NULL, NULL);

	pFileName[len] = '\0';
	return pFileName1;
}

CString GetExeDirectory()
{
	TCHAR path[MAX_PATH];
	GetModuleFileName(NULL, path, MAX_PATH);
	CString strPath = path;
	int pos = strPath.ReverseFind('\\');
	strPath = strPath.Left(pos + 1);
	return strPath;
}

#ifdef _DEBUG
#pragma comment(lib,"..\\lib\\Debug\\DB.lib") 
#else
#pragma comment(lib,"..\\lib\\Release\\DB.lib") 
#endif

#include "..\include\DB\AccessData.h"
int main()
{
	int * p = new int[5];
	delete[] p;

	CDataAccess accessData;
	ACSDData1D vecData;
	CString strPath = GetExeDirectory();
	strPath+= "826P_MECH.mdb";
	CString strTempFormName;
	strTempFormName.Format(_T("%d位置参数"), 0);

	accessData.ReadFormData_ACSDData(strPath, strTempFormName, vecData);

	for (auto value : vecData)
	{
		unique_ptr<char[]> pt1 = CStringToCharIndicator(value.strName);
		char *pFileName = pt1.get();

		cout << "名称：" << pFileName << " "
			<< "Value" << value.dwValue << " "
			<< "Max:" << value.dwMax << " "
			<< "Min:" << value.dwMin << " ";
		cout << endl;
	}

	system("pause");
    return 0;
}

