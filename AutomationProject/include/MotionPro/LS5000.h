#pragma once
#include "IMotionCard.h"
#include "IIOCard.h"
#include "ILine.h"
#include "IAxis.h"
#include "Axis.h"
#include "Line.h"

#ifdef _DEBUG
#pragma comment(lib,"..\\..\\lib\\Debug\\LTDMC.lib") 
#else
#pragma comment(lib,"..\\..\\lib\\Release\\LTDMC.lib") 
#endif

class LS5000 : public IMotionCard
{
public:
	LS5000(CardInfo config):IMotionCard(config)
	{
		MaxLines = 100;
		if (config.CardPort > 0)
		{
			m_bExtendCard = true;
		}
	}
	~LS5000()
	{

	}
public:
		std::map<CString, CInput > m_Inputs;
		std::map<CString, COutput> m_Outputs;
		std::map<CString, CAxis> m_Axes;


public:
	IInputLine* GenerateInput(LineConfig config)  override;
	IOutputLine*  GenerateOutput(LineConfig config) override;
	IAxis *GenerateAxis(AxisConfig config) override;

	bool Connect() override;

	bool Disconnect() override;

	void Update() override;

	void Stop() override;

	void LoadConfig(CString configFile) override;

};