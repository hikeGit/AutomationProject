#include "stdafx.h"
#include "..\include\MotionPro\Common.h"

CString GetExeDirectory()
{
	TCHAR path[MAX_PATH];
	GetModuleFileName(NULL, path, MAX_PATH);
	CString strPath = path;
	int pos = strPath.ReverseFind('\\');
	strPath = strPath.Left(pos + 1);
	return strPath;
}

std::unique_ptr<char[]> CStringToCharIndicator(CString strtemp)
{
	//注意：以下n和len的值大小不同,n是按字符计算的，len是按字节计算的
	int n = strtemp.GetLength();
	//获取宽字节字符的大小，大小是按字节计算的
	int len = WideCharToMultiByte(CP_ACP, 0, strtemp, strtemp.GetLength(), NULL, 0, NULL, NULL);
	char * pFileName = new char[len + 1];   //以字节为单位
	std::unique_ptr<char[]> pFileName1(pFileName);
	WideCharToMultiByte(CP_ACP, 0, strtemp, strtemp.GetLength(), pFileName, len, NULL, NULL);

	pFileName[len] = '\0';
	return pFileName1;
}

CString  SetIntToCString(int value)
{
	CString tempStr;
	tempStr.Format(_T("%d"), value);
	return tempStr;
}
CString  SetDoubleToCString(double value)
{
	CString tempStr;
	tempStr.Format(_T("%f"), value);
	return tempStr;
}

CString  SetCurrentTimeToCString()
{
	CString str;
	SYSTEMTIME st{ 0 };
	GetLocalTime(&st);
	str.Format(_T("%d-%02d-%02d %02d:%02d:%02d"),
		st.wYear,
		st.wMonth,
		st.wDay,
		st.wHour,
		st.wMinute,
		st.wSecond);

	return str;
}
