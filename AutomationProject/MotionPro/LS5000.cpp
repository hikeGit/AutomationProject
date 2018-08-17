#include "stdafx.h"
#include "..\include\MotionPro\LS5000.h"
#include "..\include\MotionPro\Line.h"

IInputLine * LS5000::GenerateInput(LineConfig config)
{
	if (config.Index >= MaxLines)
	{
		return NULL;
	}
	CInput  line(config) ;
	m_Inputs.insert(std::pair<CString, CInput>(config.Name, line));
	if (m_bExtendCard) m_Inputs[config.Name].m_bInExtendCard = true;
	return &m_Inputs[config.Name];
}

IOutputLine * LS5000::GenerateOutput(LineConfig config)
{
	if (config.Index >= MaxLines)
	{
		return NULL;
	}
	COutput  line(config);
	m_Outputs.insert(std::pair<CString, COutput>(config.Name, line));
	if (m_bExtendCard) m_Outputs[config.Name].m_bInExtendCard = true;

	return &m_Outputs[config.Name];

}

IAxis * LS5000::GenerateAxis(AxisConfig config)
{
	CAxis axis(config);
	m_Axes.insert(std::pair<CString, CAxis>(config.Name, axis));

	return &m_Axes[config.Name];
}

bool LS5000::Connect()
{
	return false;
}

bool LS5000::Disconnect()
{
	return false;
}

void LS5000::Update()
{
}

void LS5000::Stop()
{
}

void LS5000::LoadConfig(CString configFile)
{
}
