///*******************************************************************************
//**
//** �ļ�����datastruct.h
//**
//** �����ߣ�xyc_01
//**
//** ����ʱ�䣺2014.11.18
//**
//** �����£�2014.11.18
//** 
//** �汾�� ver 1.00.00
//** 
//** ģ����Ҫ���ܣ�
//
//
//**
//**  ģ���ʹ�ã�
//
//**
//**
//��ʷ��¼
//�޸��ˣ�xyc_01
//�޸�ʱ�䣺2014-11-18
//�޸����ݣ�������1���汾
//
//*******************************************************************************/
//#if !defined(_INCLUDE_DATAINTERFECE_DATASTRUCT_H_)
//#define _INCLUDE_DATAINTERFECE_DATASTRUCT_H_
//
////������ݿ�Ľṹ���������ļ�����
//#include <vector>
//
////����
//typedef struct _DATA1D
//{
//	std::vector<int> data;
//	CString strName;
//}Data1D;
//typedef std::vector<Data1D> Data2D;
//
////�û���½��Ϣ
//typedef struct _ACSD_USERLOGIN_INF
//{ 
//	CString 	strUserName;        //��½�û���
//	CString 	strUserPwd;         //��½����
//	CString 	strCreateTime;      //����ʱ��
//	long     	nUserLevel;			//�û�Ȩ��
//}ACSDUserInfo,*pACSDUserInfo;
//typedef std::vector<ACSDUserInfo> ACSDUserInfo1D;
//
////�ļ�����ṹ��
//typedef struct _ACSD_FILE_MNGER
//{
//	CString strParamDescription;
//	CString strParamValue;
//}ACSDFileMnger,*pACSDFileMnger;
//typedef std::vector<ACSDFileMnger> ACSDFileMnger1D;
//
////�����ṹ��
//typedef struct _ACSD_DATA
//{ 
//	CString strName;
//	double dwValue;
//	double dwMax;
//	double dwMin;
//	_ACSD_DATA()
//	{
//		dwValue=0;
//		dwMax=0;
//		dwMin=0;
//	}
//}ACSDData,*pACSDData;
//
////��������
//typedef std::vector<ACSDData> ACSDData1D;
//typedef std::vector<std::vector<ACSDData>> ACSDData2D;
//
////����ṹ��
//typedef struct _ACSD_POS_DATA
//{
//	CString strName;
//	double dwXValue;
//	double dwYValue;
//
//	_ACSD_POS_DATA()
//	{
//		dwXValue=0;
//		dwYValue=0;
//	}
//}ACSDPosData,*pACSDPosData;
//typedef std::vector<ACSDPosData> ACSDPosData1D;
//typedef std::vector<ACSDPosData1D> ACSDPosData2D;
//
////�Ϻ�������״
//typedef struct _SMBOXREGION
//{
//	CString strName;
//	double dwRadio;
//	double dwPtNum;
//}SMBoxRegion,*pSMBoxRegion;
//
////�ļ�
//typedef struct _ACSDFile
//{
//	CString strName;
//	CString strContent;
//}ACSDFile,*pACSDFile;
//
////������Ϣ�ṹ��
//typedef struct _ACSD_ERROR
//{  
//	CString     description;
//	CString     solution;
//}ACSDError,*pACSDError;
//typedef std::vector<ACSDError> ACSDError1D;
//
////��������ṹ��
//typedef struct _SMALARMDEF
//{  
//	CString     description_CHN;
//	CString     description_ENG;
//	CString 	solution_CHN;  
//	CString 	solution_ENG;         
//
//}SMAlarmDef,*pSMAlarmDef;
//typedef std::vector<SMAlarmDef> SMAlarmDef1D;
//
////ͼ��ͻ�е��ص�����
//typedef struct _ACSD_CAMMOTOR_DATA
//{
//	CString strName;
//	double dwX; //Ŀ�����ĵ�
//	double dwY;
//	double dwXplus;
//	double dwYplus;
//	double dwScore; //���ƶ�
//	_ACSD_CAMMOTOR_DATA()
//	{
//		dwX=0;
//		dwY=0;
//		dwXplus=0;
//		dwYplus=0;
//		dwScore=0;
//	}
//}ACSDCamMotorData,*pACSDCamMotorData;
//typedef std::vector<ACSDCamMotorData> ACSDCamMotorData1D;
//typedef std::vector<ACSDCamMotorData1D> ACSDCamMotorData2D;
//
//
////ͼƬ����
//typedef struct _ACSD_IMAGE_DATA
//{
//	BYTE* img; //ͼƬ����ָ��
//	unsigned long width; //ͼƬ���
//	unsigned long height; //ͼƬ�߶�
//	unsigned long Channel; //ͨ����
//
//}ACSDImageData;
//typedef std::vector<ACSDImageData> ACSDImageData1D;
//
////������¼
//typedef struct _ACSD_OPER_RECORD
//{
//	CString  str_time; // ��¼��ʱ��
//	CString  str_msg;  //��¼����Ϣ
//	DWORD    dwID;
//}ACSDOperRecord;
//typedef std::vector<ACSDOperRecord> ACSDOperRecord1D;
//
////ѡ�����
//typedef struct tagSelMode
//{
//	bool mode;
//	CString strName;
//}SelMode;
//typedef std::vector<SelMode> SelMode1D;
//
////�������ݿ�ö��
//enum _DATA_BASE_TYPE
//{
//	DATA_BASE_ACCESS,
//	DATA_BASE_SQLITE,
//	DATA_BASE_CSDUSER,
//};
//
////���
//typedef struct _ACSD_CAMERAMAPPING_INF
//{
//	CString 	strName;           //�������
//	CString     strDllName;        //Dll
//	long        sysID;             //ϵͳ�Ӿ���
//	long        devInterface;    //����ӿ�ID
//	long        devID;		       //�����
//	long		AngorithmType;     //���ص��㷨����
//}ACSDCameraData,*pACSDCameraDataDataa;
//typedef std::vector<ACSDCameraData> ACSDCameraData1D;
//
////�ļ��������ݽӿ�-��ʼ����
//typedef struct tagMgrFileData
//{
//	CString strFileType;   //�ļ���ʽ
//
//	CString strDefaultPath; //��ʱ����
//	CString strDefaultName;
//
//	CString strMechRunPath; //������Ŀ
//	CString strMechRunName;
//
//	CString strPrdtTemplatePath; //��Ʒģ��
//	CString strPrdtTemplateName;
//
//	CString strTempPath; //��ʱ�ļ���·��
//
//}MgrFileData;
//
////�ļ����ʹ���ʱ��
//typedef struct tagMgrFileNameTime
//{
//	CString strName; //����
//	CString strTime; //����ʱ��
//}MgrFileNameTime;
//typedef std::vector<MgrFileNameTime> MgrFileNameTime1D;
//
////��ȡ��
//typedef struct tagDataStringRow
//{
//	CString strField;
//	CString strContent;
//
//}DataStringRow;
//typedef std::vector<DataStringRow> DataStringRow1D;
//
////ͼ��������
//typedef struct tagCpDataString1D
//{
//	CString strField;
//	std::vector<BYTE*> pData1D;
//}CpDataString1D;
//
////�ò������ɺܶ���ɣ����������ݿ����
//typedef struct tagCDataString1D
//{
//	CString strField;
//	std::vector<CString> strContent1D;
//}CDataString1D;
//
//typedef struct tagCDataString2D
//{
//	CString strForm;
//	std::vector<CDataString1D> strContent1D;
//}CDataString2D;
//
//typedef struct tagCDataString3D
//{
//	CString strFile;
//	std::vector<CDataString2D> strContent1D;
//}CDataString3D;
//
////IOӳ��
//typedef struct _ACSD_IOMAPPING_INF
//{ 
//	CString 	discribe;        //����
//	long        sysIndex;        //ϵͳ�ź�����
//	long        sysBit;		     //ϵͳ�ź�λ
//	long		deviceID;        //���ƿ�ID
//	long        devIndex;        //Ӳ���ź�ID
//	long        devBit;          //Ӳ���ź�λ
//	long        deviceType;		 //���ƿ�����
//	long        devType;         //�ź�����
//}ACSDIOData,*pACSDIOData;
//typedef std::vector<ACSDIOData> ACSDIOData1D;
//
//#endif //_INCLUDE_DATAINTERFECE_DATASTRUCT_H_
