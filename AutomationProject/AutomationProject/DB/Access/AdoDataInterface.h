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

	//ADO数据库智能指针
public:
	_ConnectionPtr m_pConnection;
	_RecordsetPtr  m_pRecordset;
	_CommandPtr  m_pCommand;

protected:
	//密码使用状态
	bool m_bPassWordEn;

	//数据库密码
	CString m_PassWord;

	//标识OLE初始化状态，以防重复初始化
	static bool ms_bInitState;

	//数据库连接
	static bool ms_bAccessConnected;

public:
	//读取数据库
	bool ReadFormData(CString strPath, CString strFormName);


};

