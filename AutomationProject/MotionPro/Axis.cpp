#include "stdafx.h"
#include "..\include\MotionPro\Axis.h"

short CAxis::ServoOn(bool onOff)
{
	return 0;
}

short CAxis::ServeOn(ushort card, ushort index, bool on, bool can, ushort node)
{
	return 0;
}

short CAxis::ServeOn(bool onOff, IOutputLine * index)
{
	return 0;
}

short CAxis::ClearError()
{
	return 0;
}

short CAxis::ClearError(IOutputLine * index)
{
	return 0;
}

short CAxis::ClearError(ushort card, ushort index, bool can, ushort node)
{
	return 0;
}

short CAxis::ClearComPos()
{
	return 0;
}

short CAxis::ClearEncoderPos()
{
	return 0;
}

short CAxis::ClearPos()
{
	return 0;
}

short CAxis::SetSL_Limit(ushort model)
{
	return 0;
}

short CAxis::SetEL_Limit(ushort model, ushort logic)
{
	return 0;
}

short CAxis::SetSpeed(double speed, double acc, double dec)
{
	return 0;
}

short CAxis::ResetTarget(double destine)
{
	return 0;
}

void CAxis::Home()
{
}

short CAxis::MoveTo(double destine)
{
	return 0;
}

short CAxis::MoveRelative(double distance, bool bHome)
{
	return 0;
}

short CAxis::Jog(bool start, int dirction)
{
	return 0;
}

short CAxis::Jog(double step)
{
	return 0;
}

void CAxis::Update()
{
}

void CAxis::Stop()
{
}

void CAxis::Pause()
{
}

void CAxis::Resume()
{
}
