/*******************************************************************************
**
** �ļ�����Data.h
**
** �����ߣ�xyc_01
**
** ����ʱ�䣺2014.07.1
**
** �����£�2014.07.11
** 
** ˵������accesss���ݿ����ӵ�ģ��, ver 1.00.00
** 
** ģ��ԭ������Ҫ���ܣ�
             1���������ݿ�
			 2��ȡ���������ݿ�
			 3�������ݱ�
			 4�������±�
			 5�����ݿ������ȡ������
			 6�����ݿ������ֶ�
			 7�����ݿ�ɾ���ֶ�
			 8�����ݿ��޸��ֶ�����


**
**  ģ���ʹ�ã�
            �ȳ�ʼ��OLE
		    Ȼ���������ݿ������ݿ����
**
**
��ʷ��¼

2014-11-29 xyc_01��������1�汾

DataTypeEnum��: ��enum�������ض���

���ְ취������������

1��

#pragma warning(disable:4146)
#import "C:\Program Files\Common Files\System\ADO\msado15.dll" named_guids rename("EOF","adoEOF"), rename("BOF","adoBOF")
#pragma warning(default:4146)
using namespace ADODB;

2��

#pragma warning(disable:4146)
#import "C:\Program Files\Common Files\System\ado\msado15.dll" \
no_namespace \
rename("EOF","adoEOF") rename("DataTypeEnum","adoDataTypeEnum") \
rename("FieldAttributeEnum", "adoFielAttributeEnum") rename("EditModeEnum", "adoEditModeEnum") \
rename("LockTypeEnum", "adoLockTypeEnum") rename("RecordStatusEnum", "adoRecordStatusEnum") \
rename("ParameterDirectionEnum", "adoParameterDirectionEnum")


����һ�����Ҫ��DLL��ʹ��ǰ��д����ADO�࣬����ķ����Ͳ���Ч���ˣ���򵥵ķ�������ע�͵�STDAFX.H�ļ������
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
	//  ���ݿ��ֱ�Ӳ���
	//------------------------------------------------
public:
	//����һ�����ݱ�
	bool CreatMehineForm(CString strPath,CString strFormName);

	//�޸����ݿ�
	bool ModifyFormData(CString strPath,CString strFormName,CString strField,CString strData,int nIndex);

	//ɾ�����ݿ��ָ����
	bool DeleteFormData(CString strPath,CString strFormName,int nIndex);

	//������ݿ��ָ�����ݱ������
	bool ClearMechineForm(CString strPath,CString strFormName);

	//ɾ�����һ��
	bool DelFormDataEnd(CString strPath,CString strFormName);


	//------------------------------------------------
	//  ��ȡ���ݿ�Ĳ������������Ͷ�ȡ
	//------------------------------------------------
public:
	//��ȡ����������
	bool GetFormRowSize(CString strPath,CString strFormName,unsigned long &nSize);

	//��ȡ���ݿ�
	bool ReadFormData(CString strPath,CString strFormName,CString strField,int nIndex,CString& strData);

	//��ȡ�û�������Ϣ
	bool ReadFormData_UserInfo(CString strPath,CString strFormName,ACSDUserInfo1D& userInfo);

	//��ȡ�����ļ���Ϣ
	bool ReadFormData_FileInfo(CString strPath,CString strFormName,ACSDFileMnger1D& fileInfo);

	//��ȡ��ͨ����
	bool ReadFormData_ACSDData(CString strPath,CString strFormName,ACSDData1D& smData);

	//��ȡ��ͨ�������
	bool ReadFormData_ACSDPosData(CString strPath,CString strFormName,ACSDPosData1D& smData);

	//��ȡ��ͨ˫�������
	bool ReadFormData_ACSDCamMotorData(CString strPath,CString strFormName,ACSDCamMotorData1D& smData);

	//��ȡͼ�����
	bool ReadFormData_ACSDImageData(CString strPath,CString strFormName,ACSDImageData1D& smData);

	//��ȡָ��λ�õı�����Ϣ-yqh.2015.6.8
	bool ReadMechineErrorData(CString strPath,CString strFormName,unsigned long index,ACSDError& AlarmError);

	//------------------------------------------------
	//  ��ȡ���ݿ�Ĳ�����������������
	//------------------------------------------------
public:
	//�����û�������Ϣ
	bool AddFormData_UserInfo(CString strPath,CString strFormName,ACSDUserInfo userInfo);

	//���������ļ���Ϣ
	bool AddFormData_FileInfo(CString strPath,CString strFormName,ACSDFileMnger fileInfo);

	//������ͨ����
	bool AddFormData_ACSDData(CString strPath,CString strFormName,ACSDData smData);

	//������ͨ�������
	bool AddFormData_ACSDPosData(CString strPath,CString strFormName,ACSDPosData smData);

	//������ͨ˫�������
	bool AddFormData_ACSDCamMotorData(CString strPath,CString strFormName,ACSDCamMotorData smData);

	//����ͼ�����
	bool AddFormData_ACSDImageData(CString strPath,CString strFormName,ACSDImageData smData);

public:
	//�����û�������Ϣ
	bool AddFormData_UserInfo1D(CString strPath,CString strFormName,ACSDUserInfo1D userInfo);

	//���������ļ���Ϣ
	bool AddFormData_FileInfo1D(CString strPath,CString strFormName,ACSDFileMnger1D fileInfo);

	//������ͨ����
	bool AddFormData_ACSDData1D(CString strPath,CString strFormName,ACSDData1D smData);

	//������ͨ�������
	bool AddFormData_ACSDPosData1D(CString strPath,CString strFormName,ACSDPosData1D smData);

	//������ͨ˫�������
	bool AddFormData_ACSDCamMotorData1D(CString strPath,CString strFormName,ACSDCamMotorData1D smData);

	//����ͼ�����
	bool AddFormData_ACSDImageData1D(CString strPath,CString strFormName,ACSDImageData1D smData);

	bool AddFormData_ACSDIOData1D(CString strPath,CString strFormName,ACSDIOData1D ioData1D);
	//------------------------------------------------
	//  ���ݿ�Ĳ���
	//------------------------------------------------
public:
	//��ͼƬ����
	bool ModifyFormData_ACSDImageData(CString strPath,CString strFormName,ACSDImageData smData,unsigned long nIndex);


	//------------------------------------------------
	//  ���ݿ�ĵײ�����
	//------------------------------------------------
public:
	bool DataBaseInit(CString strPath);
	void DataBaseExit();
	//���ݿ�OLE��ʼ��
	void AccessInit(bool bPassWordUseOrNot);

	//�������ݿ�
	bool Connect2DataBase(CString strSQL);

	//ȡ���������ݿ�
	void DisconnectDataBase(void);

	//�����ݱ�
	bool OpenForm(CString FormName);

	//�����±�
	bool CreateForm(CString AccessSQL,CString FormName);

	//�������ݿ�����״̬���Ƿ�ʹ������
	void SetPassWordState(bool bNewState);

	//��ȡ���ݿ�����״̬
	bool GetPassWordState(void);

	//�������ݿ�����
	void SetPassWord(CString PassWord);

	//������ݿ�����
	CString GetPassWord(void);

	//д�����ݿ����
	void WriteData(variant_t DataField,variant_t Content);

	//ָ����֮������/�޸ļ�¼
	void WriteDataEx(variant_t DataField,variant_t Content,int nRow);

	//��ȡ�ֶεļ�¼
	variant_t ReadData(variant_t Index);

	//��ȡָ���ֶεļ�¼
	variant_t ReadDataEx(variant_t Index,int nRow);

	//��ȡ�ֶμ�¼����
	int  GetRowCount();

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

};

#endif  //(_INCLUDE_MACHINEACESS_INCLUDE_DATA_BASE_H_)