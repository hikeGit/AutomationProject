#include "stdafx.h"
#include "..\include\MotionPro\Line.h"

void COutput::WriteState(bool state)
{
	if (m_LineConfig.Reversed)
	{
		if (!m_bInExtendCard)
		{
			dmc_write_outbit(m_LineConfig.CardID, m_LineConfig.Index, state ? 1 : 0);
		}
		else
		{
			dmc_write_can_outbit(m_LineConfig.CardID,m_LineConfig.CardPort,m_LineConfig.Index,state?1:0);

		}
	}
	else
	{
		if (!m_bInExtendCard)
		{
			dmc_write_outbit(m_LineConfig.CardID, m_LineConfig.Index, state ? 0 : 1);
		}
		else
		{
			dmc_write_can_outbit(m_LineConfig.CardID, m_LineConfig.CardPort, m_LineConfig.Index, state ? 0 : 1);

		}
	}


}

void COutput::PWM(unsigned int frequency, unsigned int cycles)
{
	if (bPwm)
	{
		return;
	}

	int onTime = (int)(1000 / frequency);

	bPwm = true;

	std::thread  pwm([ & ]( ) /*->int*/
	{
		bool forever = cycles == -1;

		bool state = true;

		WriteState(state);

		while ((forever || (cycles-- > 0)) && bPwm)
		{
			Sleep(onTime);/////
			if (bPwm)
			{
				break;
			}
			state = ((state + 1) % 2) == 1 ? true : false;
			WriteState(state);
		}
	});

	pwm.detach();
}
