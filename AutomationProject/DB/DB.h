// DB.h : DB DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDBApp
// �йش���ʵ�ֵ���Ϣ������� DB.cpp
//

class CDBApp : public CWinApp
{
public:
	CDBApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
