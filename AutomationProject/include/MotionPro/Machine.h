#pragma once
#include <afxmt.h>
#include "TeachData.h"
#include "..\DB\AccessData.h"
#include <vector>
#include "Common.h"

#ifdef _DEBUG
#pragma comment(lib,"..\\..\\lib\\Debug\\DB.lib") 
#else
#pragma comment(lib,"..\\..\\lib\\Release\\DB.lib") 
#endif

#ifdef _MACHINE_EXPORTS
#define MACHINE_CLASS __declspec(dllexport)
#else
#define MACHINE_CLASS __declspec(dllimport)
#endif

class MACHINE_CLASS Machine : public CDataAccess
{
private:
	Machine();
	~Machine();
public:
	static Machine * GetInstance()
	{
		if (instance == NULL)
		{
			instanceLock.Lock();
			if (instance == NULL)
			{
				instance = new Machine();
			}
			instanceLock.Unlock();
			return   instance;
		}
		else
		{
			return instance;
		}
	}
private:
	static  Machine *instance;
	static CCriticalSection instanceLock;

private:
	const static  int InfoNum = 14;
	const   CString PositionInfo[InfoNum]
	{
		_T("PosName"),
		_T("PosNameDisplay"),
		_T("AxisName"),
		_T("Position"),
		_T("Speed"),
		_T("StartSpeed"),
		_T("EndSpeed"),
		_T("Acc"),
		_T("Dec"),
		_T("SP"),
		_T("Group"),
		_T("UpdatedTime"),
		_T("Category"),
		_T("Description")
	};

	typedef enum tagPositionInfo
	{
		PosName = 0,
		PosNameDisplay,
		AxisName,
		Position,
		Speed,
		StartSpeed,
		EndSpeed,
		Acc,
		Dec,
		SP,
		Group,
		UpdatedTime,
		Category,
		Description
	}enumTeachInfo;
private:
	bool LoadPositions(std::vector<std::map<CString, CString>> & data);
	void GetTeachingData();

	std::map<CString, CString>  AxisInfoMap(CString position,CString axis);
	std::map<CString, CString>  TeachInfoMap(CString position);
public:
	CTeachSetting  m_TeachSetting;
	CString m_strParamPath;
	CString m_strTeachingSheet;
public:
	bool SavePosition( const CTeachPosition  *  const posItem,const CString axisName);//修改单行数据
	bool SavePosition(const CTeachPosition   *  const posItem, const CAxisPosition * const axisItem);//修改单行数据

	bool SaveAllPositions();//修改保存所有数据表数据

};

