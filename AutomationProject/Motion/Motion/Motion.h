// Motion.h : Motion DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMotionApp
// �йش���ʵ�ֵ���Ϣ������� Motion.cpp
//

class CMotionApp : public CWinApp
{
public:
	CMotionApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
