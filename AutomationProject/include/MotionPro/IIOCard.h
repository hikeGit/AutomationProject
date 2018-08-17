#pragma once
#include <afx.h>
//#include "ILine.h"
#include <map>

//using namespace std;

#ifndef USHORT
#define USHORT
typedef unsigned short  ushort;
#endif

typedef  struct tagCardInfo
{
	CString CardType;//卡类型，类名
	CString CardName;//卡名称，可能会有多个实例
	CString AssamblyName;//程序集名称
	int  CardID;
	int CardPort;
	int Type;
} CardInfo;

class IIOCard //IO卡
{

public:
	IIOCard(CardInfo config):Config(config)
	{
	
	};

	IIOCard()
	{
		MessageBox(NULL, _T("IIOCard调用默认构造函数！！！！"), _T("异常"), MB_TOPMOST);
	}
	virtual ~IIOCard() {};
//protected:
//	std::map<CString, IInputLine > m_Inputs;
//	std::map<CString, IOutputLine> m_Outputs;

public:

	CardInfo Config;

	bool m_bExtendCard;//是不是扩展卡
	/// IO card version information
	CString CardVersion;

	/// max line count
	int MaxLines;

	/// indicate the controller connected or not
	bool Connected;

	virtual	IInputLine* GenerateInput(LineConfig config)  = 0;

	virtual IOutputLine*  GenerateOutput(LineConfig config)  = 0;

	/// connect with IO card
	virtual	bool Connect() = 0;

	/// disconnect with IO card
	virtual	bool Disconnect()  = 0;

	/// update IO state
	virtual	void Update() = 0;

	/// stop IO change
	virtual	void Stop() = 0;

	virtual	void LoadConfig(CString configFile) = 0;

};

