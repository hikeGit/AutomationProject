#pragma once
#include "ILine.h"
#include "LTDMC.h"
#include <thread>

class CInput:public   IInputLine
{
public:
	CInput(LineConfig config) :IInputLine(config)
	{

	}
	CInput()
	{
		MessageBox(NULL, _T("CInput调用默认构造函数！！！！"), _T("异常"), MB_TOPMOST);
	}
public:

};


class COutput :public IOutputLine
{
public:
	COutput(LineConfig config) : IOutputLine(config)
	{

	}

	COutput()
	{
		MessageBox(NULL, _T("COutput调用默认构造函数！！！！"), _T("异常"), MB_TOPMOST);
	}

public:
	void WriteState(bool state) override;
	void PWM(unsigned int frequency, unsigned int cycle)  override;

public:
	bool bPwm;


};