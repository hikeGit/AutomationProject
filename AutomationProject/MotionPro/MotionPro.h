// MotionPro.h : MotionPro DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMotionProApp
// �йش���ʵ�ֵ���Ϣ������� MotionPro.cpp
//

class CMotionProApp : public CWinApp
{
public:
	CMotionProApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
