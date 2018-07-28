#pragma once

#ifndef _INCLUDE_MACHINEACESS_INCLUDE_DATA_BASE_H_
#define _INCLUDE_MACHINEACESS_INCLUDE_DATA_BASE_H_
#endif


#include "afx.h"
#include "AdoConnect.h"
#include "AdoCommand.h"
#include "AdoRecordSet.h"

class AdoDataInterface
{
public:
	AdoDataInterface();
	~AdoDataInterface();

	//ADO���ݿ�����ָ��
public:
	_ConnectionPtr m_pConnection;
	_RecordsetPtr  m_pRecordset;
	_CommandPtr  m_pCommand;

protected:
	//����ʹ��״̬
	bool m_bPassWordEn;

	//���ݿ�����
	CString m_PassWord;

	//��ʶOLE��ʼ��״̬���Է��ظ���ʼ��
	static bool ms_bInitState;

	//���ݿ�����
	static bool ms_bAccessConnected;

public:
	//��ȡ���ݿ�
	bool ReadFormData(CString strPath, CString strFormName);


};

