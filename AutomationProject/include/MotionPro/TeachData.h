#pragma once
#include <afx.h>
#include <initializer_list>
#include <vector>

class  CAxisPosition
{
public:
	CAxisPosition()
	{

	}
	CAxisPosition(CString strName, double pos, double speed, double start, double end, double acc, double dec, double s) :
		m_strAxisName(strName),m_dPosition(pos),m_dSpeed(speed),m_dStartSpeed(start),m_dEndSpeed(end),m_dAcc(acc),m_dDec(dec),m_dS(s)
	{

	}
	CAxisPosition(CString strName, std::initializer_list<double> init)
	{

		if (init.size() < 7)
		{
			MessageBox(NULL, _T("CTeachPos创建失败:" + strName), _T("CTeachPos创建失败"), MB_TOPMOST);
			return;
		}

		m_strAxisName = strName;
		auto ite = init.begin();
		m_dPosition = *ite;
		m_dSpeed = *(ite + 1);
		m_dStartSpeed = *(ite + 2);
		m_dEndSpeed = *(ite + 3);
		m_dAcc = *(ite + 4);
		m_dDec = *(ite + 5);
		m_dS = *(ite + 6);
	}
public:
	CString  m_strAxisName;
	double  m_dPosition;
	double  m_dSpeed;
	double  m_dStartSpeed;
	double  m_dEndSpeed;
	double  m_dAcc;
	double  m_dDec;
	double  m_dS;

};

class CTeachPosition
{

public:
	CTeachPosition()
	{
		
	}

public:
	CTeachPosition(CString posname, CString dispalay,CString category,CString description,CString update, std::vector<CAxisPosition> axispos):
		m_strPosName(posname), m_strDisplayName(dispalay),m_strCategory(category),m_strDescription(description),m_strUpdateTime(update),m_AxesPosition(axispos)
	{

	}

public:
	CTeachPosition(CString posname, std::vector<CAxisPosition> vec,std::initializer_list<CString> inilist)
	{
		if (inilist.size() < 5)
		{
				MessageBox(NULL, _T("CTeachPos创建失败:" + posname), _T("CTeachPos创建失败"), MB_TOPMOST);
				return;
		}

		m_strPosName = posname;
		m_AxesPosition = vec;
		auto ite = inilist.begin();

		m_strDisplayName = *ite;
		m_strCategory = *(ite + 1);
		m_strDescription = *(ite + 2);
		m_strUpdateTime = *(ite + 3);
		m_strGroup = *(ite + 4);
	}
public:
	CString m_strPosName;
	CString m_strDisplayName;
	CString m_strCategory;
	CString m_strDescription;
	CString m_strUpdateTime;
	//CTime   m_tUpdatedTime;
	CString  m_strGroup;
	//tm time;
	
	std::vector<CAxisPosition> m_AxesPosition;

public:
	CAxisPosition * operator[] (CString name)
	{
		for (auto &item : m_AxesPosition)
		{
			if (item.m_strAxisName == name)
				return &item;
		}
		CString erro;
		erro.Format(_T("查找名称为%s的轴位置参数失败，不存在这样的轴位置参数"), name);
		MessageBox(NULL , erro , _T("查找轴位置参数失败"), MB_TOPMOST);
		return NULL;
	}

};

class CTeachSetting
{
public:
	CTeachSetting()
	{

	}

public:
	std::vector<CTeachPosition> TeachPositions;

public:
	CTeachPosition *operator [] (CString name)
	{
		for (auto &item : TeachPositions)
		{
			if (item.m_strPosName == name)
				return &item;
		}
		CString erro;
		erro.Format(_T("查找名称为%s的位置参数失败，不存在这样的位置参数"), name);
		MessageBox(NULL, erro, _T("查找位置参数失败"), MB_TOPMOST);
		return NULL;
	}
};