#pragma once
#include <afxmt.h>
#include "IAxis.h"
#include "IIOCard.h"
#include "ILine.h"
#include "IMotionCard.h"
#include "LS5000.h"
#include <map>
#include "Common.h"
#include "..\DB\AccessData.h"

#ifdef _DEBUG
#pragma comment(lib,"..\\..\\lib\\Debug\\DB.lib") 
#else
#pragma comment(lib,"..\\..\\lib\\Release\\DB.lib") 
#endif

#ifdef _MOTIONFACTORY_EXPORTS
#define MOTIONFACTORY_CLASS __declspec(dllexport)
#else
#define MOTIONFACTORY_CLASS __declspec(dllimport)
#endif

class  MOTIONFACTORY_CLASS MotionFactory : public CDataAccess
{
#pragma region singleton
private:
	static MotionFactory *  instance;
	static CCriticalSection instanceLock;
	int d = 5;
public:
	static MotionFactory * GetInstance()
	{
		if (instance == NULL)
		{
			instanceLock.Lock();
			if (instance == NULL)
			{
				instance = new MotionFactory();
			}
			instanceLock.Unlock();
			return   instance;
		}
		else
		{
			return instance;
		}
	}

	MotionFactory();

	~MotionFactory()
	{
		if (instance != NULL)
		{
			delete instance;
		}
		for (auto & item : m_MotionCards)
		{
			if (item.second != NULL)
			{
				delete item.second;
			}
		}
	}
#pragma endregion 
public:
	std::map<CString, IMotionCard*>  m_MotionCards;
	std::map<CString, IIOCard*> m_IOCards;
	std::map<CString, IInputLine*> m_Inputs;
	std::map<CString, IOutputLine*> m_Outputs;
	std::map<CString, IAxis*> m_Axes;

public :
	std::vector< CardInfo> m_AvailableCards;
	std::map<CString, CardInfo> m_CardsMap;
	std::vector<LineConfig> m_InputsConfig;
	std::vector<LineConfig> m_OutputsConfig;
	std::map<CString, HomeParam> m_AxisHomeSetting;
	std::map<CString, AxisConfig> m_AxisConfig_Map;
	std::vector<AxisConfig> m_AxisConfig_Vector;
	//CDataAccess * access;
	CString m_strConfigPath;
	CString m_strParamPath;
public:
	bool LoadCardInfo();
	bool LoadLines(bool in);//0  ‰»Î 1 ‰≥ˆ
	bool LoadHomeSetting();
	bool LoadAxisConfig();
	bool CreateCards();
	bool  CreateLines(bool in);
	bool CreateAxes();	 
};

