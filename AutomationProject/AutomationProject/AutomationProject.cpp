// AutomationProject.cpp : �������̨Ӧ�ó������ڵ㡣
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
	//ע�⣺����n��len��ֵ��С��ͬ,n�ǰ��ַ�����ģ�len�ǰ��ֽڼ����
	int n = strtemp.GetLength();
	//��ȡ���ֽ��ַ��Ĵ�С����С�ǰ��ֽڼ����
	int len = WideCharToMultiByte(CP_ACP, 0, strtemp, strtemp.GetLength(), NULL, 0, NULL, NULL);
	char * pFileName = new char[len + 1];   //���ֽ�Ϊ��λ
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
	strTempFormName.Format(_T("%dλ�ò���"), 0);

	accessData.ReadFormData_ACSDData(strPath, strTempFormName, vecData);

	for (auto value : vecData)
	{
		unique_ptr<char[]> pt1 = CStringToCharIndicator(value.strName);
		char *pFileName = pt1.get();

		cout << "���ƣ�" << pFileName << " "
			<< "Value" << value.dwValue << " "
			<< "Max:" << value.dwMax << " "
			<< "Min:" << value.dwMin << " ";
		cout << endl;
	}

	system("pause");
    return 0;
}

