/*******************************************************************************
**
** 文件名：Data.h
**
** 创建者：xyc_01
**
** 创建时间：2014.07.1
**
** 最后更新：2014.07.11
** 
** 说明：和accesss数据库连接的模块, ver 1.00.00
** 
** 模块原理与主要功能：
             1，连接数据库
			 2，取消连接数据库
			 3，打开数据表
			 4，创建新表
			 5，数据库密码获取和设置
			 6，数据库新增字段
			 7，数据库删除字段
			 8，数据库修改字段内容


**
**  模块的使用：
            先初始化OLE
		    然后连接数据库做数据库操作
**
**
历史记录

2014-11-29 xyc_01，创建第1版本

DataTypeEnum”: “enum”类型重定义

两种办法来解决这个问题

1）

#pragma warning(disable:4146)
#import "C:\Program Files\Common Files\System\ADO\msado15.dll" named_guids rename("EOF","adoEOF"), rename("BOF","adoBOF")
#pragma warning(default:4146)
using namespace ADODB;

2）

#pragma warning(disable:4146)
#import "C:\Program Files\Common Files\System\ado\msado15.dll" \
no_namespace \
rename("EOF","adoEOF") rename("DataTypeEnum","adoDataTypeEnum") \
rename("FieldAttributeEnum", "adoFielAttributeEnum") rename("EditModeEnum", "adoEditModeEnum") \
rename("LockTypeEnum", "adoLockTypeEnum") rename("RecordStatusEnum", "adoRecordStatusEnum") \
rename("ParameterDirectionEnum", "adoParameterDirectionEnum")


另外一种如果要在DLL中使用前人写过的ADO类，上面的方法就不起效果了，最简单的方法就是注释掉STDAFX.H的几句代码
// #ifndef _AFX_NO_DAO_SUPPORT
// #include <afxdao.h>            // MFC DAO database classes
// #endif // _AFX_NO_DAO_SUPPORT

*******************************************************************************/


#ifndef _INCLUDE_MACHINEACESS_INCLUDE_DATA_BASE_H_
#define _INCLUDE_MACHINEACESS_INCLUDE_DATA_BASE_H_

#include "afx.h"
#include "AdoConnect.h"
#include "AdoCommand.h"
#include "AdoRecordSet.h"
//#import "Ado/msado15.dll" no_namespace rename("EOF","adoEOF")
#include "DataStruct.h"

#define USEPASSWORD		1
#define NOTUSEPASSWORD	0
class  CDataAccess
{
public:
	CDataAccess();
	~CDataAccess();

	//------------------------------------------------
	//  数据库的直接操作
	//------------------------------------------------
public:
	//创建一个数据表
	bool CreatMehineForm(CString strPath,CString strFormName);

	//修改数据库
	bool ModifyFormData(CString strPath,CString strFormName,CString strField,CString strData,int nIndex);

	//删除数据库的指定行
	bool DeleteFormData(CString strPath,CString strFormName,int nIndex);

	//清空数据库的指定数据表的内容
	bool ClearMechineForm(CString strPath,CString strFormName);

	//删除最后一行
	bool DelFormDataEnd(CString strPath,CString strFormName);


	//------------------------------------------------
	//  读取数据库的操作：按照类型读取
	//------------------------------------------------
public:
	//获取表格的总行数
	bool GetFormRowSize(CString strPath,CString strFormName,unsigned long &nSize);

	//读取数据库
	bool ReadFormData(CString strPath,CString strFormName,CString strField,int nIndex,CString& strData);

	//读取用户管理信息
	bool ReadFormData_UserInfo(CString strPath,CString strFormName,ACSDUserInfo1D& userInfo);

	//读取数据文件信息
	bool ReadFormData_FileInfo(CString strPath,CString strFormName,ACSDFileMnger1D& fileInfo);

	//读取普通参数
	bool ReadFormData_ACSDData(CString strPath,CString strFormName,ACSDData1D& smData);

	//读取普通坐标参数
	bool ReadFormData_ACSDPosData(CString strPath,CString strFormName,ACSDPosData1D& smData);

	//读取普通双坐标参数
	bool ReadFormData_ACSDCamMotorData(CString strPath,CString strFormName,ACSDCamMotorData1D& smData);

	//读取图像参数
	bool ReadFormData_ACSDImageData(CString strPath,CString strFormName,ACSDImageData1D& smData);

	//读取指定位置的报警信息-yqh.2015.6.8
	bool ReadMechineErrorData(CString strPath,CString strFormName,unsigned long index,ACSDError& AlarmError);

	//------------------------------------------------
	//  读取数据库的操作：按照类型增加
	//------------------------------------------------
public:
	//增加用户管理信息
	bool AddFormData_UserInfo(CString strPath,CString strFormName,ACSDUserInfo userInfo);

	//增加数据文件信息
	bool AddFormData_FileInfo(CString strPath,CString strFormName,ACSDFileMnger fileInfo);

	//增加普通参数
	bool AddFormData_ACSDData(CString strPath,CString strFormName,ACSDData smData);

	//增加普通坐标参数
	bool AddFormData_ACSDPosData(CString strPath,CString strFormName,ACSDPosData smData);

	//增加普通双坐标参数
	bool AddFormData_ACSDCamMotorData(CString strPath,CString strFormName,ACSDCamMotorData smData);

	//增加图像参数
	bool AddFormData_ACSDImageData(CString strPath,CString strFormName,ACSDImageData smData);

public:
	//增加用户管理信息
	bool AddFormData_UserInfo1D(CString strPath,CString strFormName,ACSDUserInfo1D userInfo);

	//增加数据文件信息
	bool AddFormData_FileInfo1D(CString strPath,CString strFormName,ACSDFileMnger1D fileInfo);

	//增加普通参数
	bool AddFormData_ACSDData1D(CString strPath,CString strFormName,ACSDData1D smData);

	//增加普通坐标参数
	bool AddFormData_ACSDPosData1D(CString strPath,CString strFormName,ACSDPosData1D smData);

	//增加普通双坐标参数
	bool AddFormData_ACSDCamMotorData1D(CString strPath,CString strFormName,ACSDCamMotorData1D smData);

	//增加图像参数
	bool AddFormData_ACSDImageData1D(CString strPath,CString strFormName,ACSDImageData1D smData);

	bool AddFormData_ACSDIOData1D(CString strPath,CString strFormName,ACSDIOData1D ioData1D);
	//------------------------------------------------
	//  数据库的操作
	//------------------------------------------------
public:
	//存图片数据
	bool ModifyFormData_ACSDImageData(CString strPath,CString strFormName,ACSDImageData smData,unsigned long nIndex);


	//------------------------------------------------
	//  数据库的底层连接
	//------------------------------------------------
public:
	bool DataBaseInit(CString strPath);
	void DataBaseExit();
	//数据库OLE初始化
	void AccessInit(bool bPassWordUseOrNot);

	//连接数据库
	bool Connect2DataBase(CString strSQL);

	//取消连接数据库
	void DisconnectDataBase(void);

	//打开数据表
	bool OpenForm(CString FormName);

	//创建新表
	bool CreateForm(CString AccessSQL,CString FormName);

	//设置数据库密码状态，是否使用密码
	void SetPassWordState(bool bNewState);

	//获取数据库密码状态
	bool GetPassWordState(void);

	//设置数据库密码
	void SetPassWord(CString PassWord);

	//获得数据库密码
	CString GetPassWord(void);

	//写入数据库参数
	void WriteData(variant_t DataField,variant_t Content);

	//指定行之后增加/修改记录
	void WriteDataEx(variant_t DataField,variant_t Content,int nRow);

	//获取字段的记录
	variant_t ReadData(variant_t Index);

	//获取指定字段的记录
	variant_t ReadDataEx(variant_t Index,int nRow);

	//获取字段记录总数
	int  GetRowCount();

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

};

#endif  //(_INCLUDE_MACHINEACESS_INCLUDE_DATA_BASE_H_)