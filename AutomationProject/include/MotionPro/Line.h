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
		MessageBox(NULL, _T("CInput����Ĭ�Ϲ��캯����������"), _T("�쳣"), MB_TOPMOST);
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
		MessageBox(NULL, _T("COutput����Ĭ�Ϲ��캯����������"), _T("�쳣"), MB_TOPMOST);
	}

public:
	void WriteState(bool state) override;
	void PWM(unsigned int frequency, unsigned int cycle)  override;

public:
	bool bPwm;


};