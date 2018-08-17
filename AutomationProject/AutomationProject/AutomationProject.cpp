// AutomationProject.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <memory>
#include <afx.h>
#include "..\include\DB\AccessData.h"
#include "..\include\MotionPro\MotionFactory.h"
#include "..\include\MotionPro\Machine.h"


//#include "..\include\MotionPro\MotionFactory.h"
using namespace std;

#pragma warning(disable:4996)

#ifdef _DEBUG
#pragma comment(lib,"../lib/Debug/DB.lib") 
#pragma comment(lib,"../lib/Debug/MotionPro.lib") 
#else
#pragma comment(lib,"..\\lib\\Release\\DB.lib") 
#pragma comment(lib,"..\\lib\\Release\\MotionPro.lib") 
#endif



bool  Load(bool in)
{
	cout << "<<<<<<<<<<<<<<<<<<<<<<IO点>>>>>>>>>>>>>>>>>>>" << endl;
		for (auto item :( in?MotionFactory::GetInstance()->m_InputsConfig : MotionFactory::GetInstance()->m_OutputsConfig))
		{
			unique_ptr<char[]> pt1 = CStringToCharIndicator(item.DisplayName);
			char *pt = pt1.get();
			cout << pt << "  ";

			pt1 = CStringToCharIndicator(item.Name);
			pt = pt1.get();
			cout << pt << "  ";

			pt1 = CStringToCharIndicator(item.CardName);
			pt = pt1.get();
			cout << pt << "  ";

			char  ar[10];
			sprintf(ar, "%d", item.Index);
			cout << ar << "  ";

			sprintf(ar, "%d", item.Reversed);
			cout << ar << "  ";

			sprintf(ar, "%d", item.CardID);
			cout << ar << "  ";

			sprintf(ar, "%d", item.CardPort);
			cout << ar << "  ";
			cout << endl;
		}
		return true;
}
bool LoadCards()
{
	cout << "<<<<<<<<<<<<<<<<<<<<<<Card>>>>>>>>>>>>>>>>>>>" << endl;
		for (auto item : MotionFactory::GetInstance()->m_AvailableCards)
		{
			unique_ptr<char[]> pt1 = CStringToCharIndicator(item.CardName);
			char *pt = pt1.get();
			cout << pt << "  ";

			pt1 = CStringToCharIndicator(item.CardType);
			pt = pt1.get();
			cout << pt << "  ";

			pt1 = CStringToCharIndicator(item.AssamblyName);
			pt = pt1.get();
			cout << pt << "  ";

			char  ar[10];
			sprintf(ar, "%d", item.CardID);
			cout << ar << "  ";

			sprintf(ar, "%d", item.CardPort);
			cout << ar << "  ";

			sprintf(ar, "%d", item.Type);
			cout << ar << "  ";

			cout << endl;
		}
		return true;
}

int main()
{
	if (LoadCards() && Load(true) && Load(false))
	{

	}
	else
	{
		cout << "异常！！！！！！！！！！！！！！！！！！！！！！"<<endl;
	}

	Machine::GetInstance();

	system("pause");
    return 0;
}

