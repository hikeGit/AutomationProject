
#include "stdafx.h"
#include "..\include\MotionPro\MotionFactory.h"

MotionFactory * MotionFactory::instance = 0;
CCriticalSection MotionFactory::instanceLock;

MotionFactory::MotionFactory()
{
	m_strConfigPath = GetExeDirectory() + _T("Config\\CardConfig.mdb");
	m_strParamPath = GetExeDirectory() + _T("Param\\ParamConfig.mdb");
	
	LoadCardInfo();
	LoadLines(true);
	LoadLines(false);
	
	LoadAxisConfig();

	CreateCards();
	CreateLines(true);	
	CreateLines(false);
	CreateAxes();
}
//CardID是卡号，CardPort是节点号，Type 0:IO卡 1:Motion卡
bool MotionFactory::LoadCardInfo()
{
	std::vector<std::map<CString,CString>> data;
	CString carfinfo[6]{ _T("CardName"), _T("CardClass"), _T("Assambly"),_T("CardID"), _T("CardPort"),_T("Type") };
    bool  rtn =	ReadFormData(m_strConfigPath, _T("卡类型"), std::vector<CString>(carfinfo, carfinfo+6), data);
	if (rtn)
	{
		for (auto item : data)
		{
			CardInfo info;
			info.CardName = item[_T("CardName")];
			info.CardType = item[_T("CardClass")];
			info.AssamblyName = item[_T("Assambly")];
			info.CardID = _ttoi(item[_T("Assambly")]);
			info.CardPort = _ttoi( item[_T("CardPort")]);
			info.Type = _ttoi(item[_T("Type")]);
			m_AvailableCards.push_back(info);
			m_CardsMap.insert(std::pair<CString, CardInfo>(info.CardName, info));
		}
		return true;
	}
	return false;
}

bool MotionFactory::LoadLines(bool in)
{
	std::vector<std::map<CString,CString>> data;
	const int num = 5;
	CString linetype = in ? _T("输入映射") : _T("输出映射");
	CString info[num]{ _T("DisplayName"), _T("KeyName"), _T("CardName"),_T("Index"), _T("Reverse") };
	bool  rtn = ReadFormData(m_strConfigPath, linetype, std::vector<CString>(info, info + num), data);
	if (rtn)
	{
		for (auto item : data)
		{
			LineConfig config;
			config.DisplayName = item[_T("DisplayName")];
			config.Name = item[_T("KeyName")];
			config.CardName = item[_T("CardName")];
			config.Index = _ttoi(item[_T("Index")]);
			config.Reversed = _ttoi(item[_T("Reverse")]) == 1 ? true : false;

			if (m_CardsMap.count(config.CardName) > 0)
			{
				config.CardID = m_CardsMap[config.CardName].CardID;
				config.CardPort = m_CardsMap[config.CardName].CardPort;
			}

			in ? m_InputsConfig.push_back(config) : m_OutputsConfig.push_back(config);
		}
		return true;
	}
	return false;

}

bool MotionFactory::LoadHomeSetting()
{
	std::vector<std::map<CString, CString>> data;
	const int num = 10;
	CString cardinfo[num]{ _T("KeyName"), _T("Mode"), _T("Direction"),_T("StartSpeed"),_T("Speed"), _T("Acc"),_T("LeaveHomeSpeed"),_T("Offset"),_T("CurveFactor"),_T("EZAlignEnabled") };
	bool  rtn = ReadFormData(m_strParamPath, _T("轴原点设定"), std::vector<CString>(cardinfo, cardinfo + num), data);
	if (rtn)
	{
		for (auto item : data)
		{
			HomeParam info;
			CString keyName;
			TCHAR *endPtr;
			keyName = item[_T("KeyName")];
			info.Mode = _ttoi(item[_T("Mode")]);
			info.Direction = _ttoi(item[_T("Direction")]);
			info.StartSpeed = _tcstod(item[_T("StartSpeed")],&endPtr);
			info.Speed = _tcstod(item[_T("Speed")], &endPtr);
			info.Acc = _tcstod(item[_T("Acc")], &endPtr);
			info.LeaveHomeSpeed = _tcstod(item[_T("LeaveHomeSpeed")], &endPtr);
			info.Offset = _tcstod(item[_T("Offset")], &endPtr);
			info.CurveFactor = _tcstod(item[_T("CurveFactor")], &endPtr);
			info.EZAlignEnabled = _ttoi(item[_T("EZAlignEnabled")]) == 1 ? true : false;
			m_AxisHomeSetting.insert(std::pair<CString, HomeParam>(keyName, info));
		}
		return true;
	}
	return false;
}

bool MotionFactory::LoadAxisConfig()
{
	std::vector<std::map<CString, CString>> data;
	const int num = 12;
	CString cardinfo[num]
	{
		_T("KeyName"),
		_T("DisplayName"), 
		_T("CardName"),
		_T("Index"), 
		_T("CountPerMM"),
		_T("UseEncoder"),
		_T("Direct"),
		_T("OutMode"),
		_T("OriginLogic"),
		_T("AlarmLogic"),
		_T("LimitLogic"),
		_T("UseLimit_SL") 
	};

	bool  rtn = ReadFormData(m_strConfigPath, _T("轴映射"), std::vector<CString>(cardinfo, cardinfo + num), data);
	if (rtn )
	{
		for (auto item : data)
		{
			AxisConfig info;
			TCHAR *endPtr;
			info.Name = item[_T("KeyName")];
			info.DisplayName = item[_T("DisplayName")];
			info.CardName = item[_T("CardName")];
			info.Index = _ttoi(item[_T("Index")]);
			info.CountPerMM = _tcstod(item[_T("CountPerMM")], &endPtr);
			info.UseEncoder = _ttoi(item[_T("UseEncoder")]) == 1 ? true : false;
			info.Direct = _ttoi(item[_T("Direct")]);
			info.OutMode = _ttoi(item[_T("OutMode")]);
			info.OriginLogic = _ttoi(item[_T("OriginLogic")]);
			info.AlarmLogic = _ttoi(item[_T("AlarmLogic")]);
			info.LimitLogic = _ttoi(item[_T("LimitLogic")]);
			info.UseLimit_SL = _ttoi(item[_T("UseLimit_SL")]) == 1 ? true : false;
			
			if (!LoadHomeSetting()) return false;
			if (m_AxisHomeSetting.find(info.Name) == m_AxisHomeSetting.end()) return false;
			info.HomeSetting = m_AxisHomeSetting[info.Name];

			if (m_CardsMap.count(info.CardName) == 0)  return false;
			info.CardID = m_CardsMap[info.Name].CardID;

			m_AxisConfig_Map.insert(std::pair<CString, AxisConfig>(info.Name, info));
			m_AxisConfig_Vector.push_back(info);
		}
		return true;
	}
	else
	{
		return false;
	}
}

bool MotionFactory::CreateCards()
{
	try
	{
		for (auto item : m_AvailableCards)
		{
			if (item.CardType == "LS5000")
			{
				if (item.Type == 0)
				{
					m_MotionCards.insert(std::pair<CString, IMotionCard*>(item.CardName, new LS5000(item)));
				}
				else if (item.Type == 1)
				{
					m_IOCards.insert(std::pair<CString, IIOCard*>(item.CardName, new LS5000(item)));
				}
			}
		}	
		return true;
	}
	catch (...)
	{
		MessageBox(NULL, _T("创建卡失败！！！！！！"), _T("ERRO"), MB_TOPMOST);
		return false;
	}
}

bool MotionFactory::CreateLines(bool in)
{
	try
	{
		for (auto item : (in?m_InputsConfig:m_OutputsConfig))
		{
			if (m_MotionCards.count(item.CardName)>0)
			{
				if (in)m_Inputs.insert(std::pair<CString, IInputLine *>(item.Name, m_MotionCards[item.CardName]->GenerateInput(item)));
				else m_Outputs.insert(std::pair<CString, IOutputLine *>(item.Name, m_MotionCards[item.CardName]->GenerateOutput(item)));					
			}
			else if(m_IOCards.count(item.CardName) > 0)
			{
				if (in)m_Inputs.insert(std::pair<CString, IInputLine *>(item.Name, m_IOCards[item.CardName]->GenerateInput(item)));
				else m_Outputs.insert(std::pair<CString, IOutputLine *>(item.Name, m_IOCards[item.CardName]->GenerateOutput(item)));
			}
			else
			{
				CString erro;
				erro.Format(_T("IO%s创建异常"), item.Name);
				throw std::exception((LPCSTR)(LPSTR)erro.GetBuffer());
			}
		}
		return true;
	}
	catch (std::exception e)
	{
		CString erro(e.what());
		MessageBox(NULL,erro, _T("ERRO"), MB_TOPMOST);
		return false;
	}
	catch (...)
	{
		MessageBox(NULL, _T("创建IO点失败！！！！！！"), _T("ERRO"), MB_TOPMOST);
		return false;
	}

}

bool MotionFactory::CreateAxes()
{
	try
	{
		for (auto item : m_AxisConfig_Vector)
		{
			if (m_MotionCards.count(item.CardName) > 0)
			{
				m_Axes.insert(std::pair<CString, IAxis *>(item.Name, m_MotionCards[item.CardName]->GenerateAxis(item)));
			}				
			else
			{
				CString erro;
				erro.Format(_T("轴%s创建异常"), item.Name);
				throw std::exception((LPCSTR)(LPSTR)erro.GetBuffer());
			}
		}
		return true;
	}
	catch (std::exception e)
	{
		CString erro(e.what());
		MessageBox(NULL, erro, _T("ERRO"), MB_TOPMOST);
		return false;
	}
	catch (...)
	{
		MessageBox(NULL, _T("创建轴失败！！！！！！"), _T("ERRO"), MB_TOPMOST);
		return false;
	}

}

