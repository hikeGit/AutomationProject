// AutomationProject.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include "DB\Access\AccessData.h"
#include <memory>
using namespace std;

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


int main()
{
	int * p = new int[5];
	delete[] p;

	CDataAccess accessData;
	ACSDData1D vecData;
	CString strPath = "E:\\Practise\\AutomationProject\\Debug\\826P_MECH.mdb";
	CString strTempFormName;
	strTempFormName.Format(_T("%d位置参数"), 0);

	accessData.ReadFormData_ACSDData(strPath, strTempFormName, vecData);

	{
		unique_ptr<char[]> pt1 = CStringToCharIndicator("22222");
		char *pt = pt1.get();
		cout << pt << endl;
	}

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

