// AutomationProject.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include "DB\Access\AccessData.h"
#include <memory>
using namespace std;

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


int main()
{
	int * p = new int[5];
	delete[] p;

	CDataAccess accessData;
	ACSDData1D vecData;
	CString strPath = "E:\\Practise\\AutomationProject\\Debug\\826P_MECH.mdb";
	CString strTempFormName;
	strTempFormName.Format(_T("%dλ�ò���"), 0);

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

		cout << "���ƣ�" << pFileName << " "
			<< "Value" << value.dwValue << " "
			<< "Max:" << value.dwMax << " "
			<< "Min:" << value.dwMin << " ";
		cout << endl;
	}

	system("pause");
    return 0;
}

