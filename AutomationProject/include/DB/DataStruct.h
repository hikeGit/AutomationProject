///*******************************************************************************
//**
//** 文件名：datastruct.h
//**
//** 创建者：xyc_01
//**
//** 创建时间：2014.11.18
//**
//** 最后更新：2014.11.18
//** 
//** 版本： ver 1.00.00
//** 
//** 模块主要功能：
//
//
//**
//**  模块的使用：
//
//**
//**
//历史记录
//修改人：xyc_01
//修改时间：2014-11-18
//修改内容：创建第1个版本
//
//*******************************************************************************/
//#if !defined(_INCLUDE_DATAINTERFECE_DATASTRUCT_H_)
//#define _INCLUDE_DATAINTERFECE_DATASTRUCT_H_
//
////针对数据库的结构做的数据文件定义
//#include <vector>
//
////数组
//typedef struct _DATA1D
//{
//	std::vector<int> data;
//	CString strName;
//}Data1D;
//typedef std::vector<Data1D> Data2D;
//
////用户登陆信息
//typedef struct _ACSD_USERLOGIN_INF
//{ 
//	CString 	strUserName;        //登陆用户名
//	CString 	strUserPwd;         //登陆密码
//	CString 	strCreateTime;      //创建时间
//	long     	nUserLevel;			//用户权限
//}ACSDUserInfo,*pACSDUserInfo;
//typedef std::vector<ACSDUserInfo> ACSDUserInfo1D;
//
////文件管理结构体
//typedef struct _ACSD_FILE_MNGER
//{
//	CString strParamDescription;
//	CString strParamValue;
//}ACSDFileMnger,*pACSDFileMnger;
//typedef std::vector<ACSDFileMnger> ACSDFileMnger1D;
//
////参数结构体
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
////参数数组
//typedef std::vector<ACSDData> ACSDData1D;
//typedef std::vector<std::vector<ACSDData>> ACSDData2D;
//
////坐标结构体
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
////料盒区域形状
//typedef struct _SMBOXREGION
//{
//	CString strName;
//	double dwRadio;
//	double dwPtNum;
//}SMBoxRegion,*pSMBoxRegion;
//
////文件
//typedef struct _ACSDFile
//{
//	CString strName;
//	CString strContent;
//}ACSDFile,*pACSDFile;
//
////错误信息结构体
//typedef struct _ACSD_ERROR
//{  
//	CString     description;
//	CString     solution;
//}ACSDError,*pACSDError;
//typedef std::vector<ACSDError> ACSDError1D;
//
////报警定义结构体
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
////图像和机械相关的数据
//typedef struct _ACSD_CAMMOTOR_DATA
//{
//	CString strName;
//	double dwX; //目标中心点
//	double dwY;
//	double dwXplus;
//	double dwYplus;
//	double dwScore; //相似度
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
////图片数据
//typedef struct _ACSD_IMAGE_DATA
//{
//	BYTE* img; //图片数据指针
//	unsigned long width; //图片宽度
//	unsigned long height; //图片高度
//	unsigned long Channel; //通道数
//
//}ACSDImageData;
//typedef std::vector<ACSDImageData> ACSDImageData1D;
//
////操作记录
//typedef struct _ACSD_OPER_RECORD
//{
//	CString  str_time; // 记录的时间
//	CString  str_msg;  //记录的信息
//	DWORD    dwID;
//}ACSDOperRecord;
//typedef std::vector<ACSDOperRecord> ACSDOperRecord1D;
//
////选项参数
//typedef struct tagSelMode
//{
//	bool mode;
//	CString strName;
//}SelMode;
//typedef std::vector<SelMode> SelMode1D;
//
////定义数据库枚举
//enum _DATA_BASE_TYPE
//{
//	DATA_BASE_ACCESS,
//	DATA_BASE_SQLITE,
//	DATA_BASE_CSDUSER,
//};
//
////相机
//typedef struct _ACSD_CAMERAMAPPING_INF
//{
//	CString 	strName;           //相机名称
//	CString     strDllName;        //Dll
//	long        sysID;             //系统视觉号
//	long        devInterface;    //相机接口ID
//	long        devID;		       //相机号
//	long		AngorithmType;     //加载的算法类型
//}ACSDCameraData,*pACSDCameraDataDataa;
//typedef std::vector<ACSDCameraData> ACSDCameraData1D;
//
////文件管理数据接口-初始化用
//typedef struct tagMgrFileData
//{
//	CString strFileType;   //文件格式
//
//	CString strDefaultPath; //临时数据
//	CString strDefaultName;
//
//	CString strMechRunPath; //运行数目
//	CString strMechRunName;
//
//	CString strPrdtTemplatePath; //产品模板
//	CString strPrdtTemplateName;
//
//	CString strTempPath; //临时文件夹路径
//
//}MgrFileData;
//
////文件名和创建时间
//typedef struct tagMgrFileNameTime
//{
//	CString strName; //名字
//	CString strTime; //创建时间
//}MgrFileNameTime;
//typedef std::vector<MgrFileNameTime> MgrFileNameTime1D;
//
////读取行
//typedef struct tagDataStringRow
//{
//	CString strField;
//	CString strContent;
//
//}DataStringRow;
//typedef std::vector<DataStringRow> DataStringRow1D;
//
////图像数据用
//typedef struct tagCpDataString1D
//{
//	CString strField;
//	std::vector<BYTE*> pData1D;
//}CpDataString1D;
//
////该操作的由很多表构成，类似于数据库操作
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
////IO映射
//typedef struct _ACSD_IOMAPPING_INF
//{ 
//	CString 	discribe;        //描述
//	long        sysIndex;        //系统信号索引
//	long        sysBit;		     //系统信号位
//	long		deviceID;        //控制卡ID
//	long        devIndex;        //硬件信号ID
//	long        devBit;          //硬件信号位
//	long        deviceType;		 //控制卡类型
//	long        devType;         //信号类型
//}ACSDIOData,*pACSDIOData;
//typedef std::vector<ACSDIOData> ACSDIOData1D;
//
//#endif //_INCLUDE_DATAINTERFECE_DATASTRUCT_H_
