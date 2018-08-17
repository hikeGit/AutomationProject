#pragma once
#include "IAxis.h"

class CAxis :public  IAxis
{
public:
	CAxis(AxisConfig config) :IAxis(config)
	{

	}
	CAxis()
	{

	}

	short ServoOn(bool onOff) override;
	short ServeOn(ushort card, ushort index, bool on, bool can = false, ushort node = 1)override;
	short ServeOn(bool onOff, IOutputLine * index) override;
	short ClearError()override;
	short ClearError(IOutputLine  * index);
	short ClearError(ushort card, ushort index, bool can = false, ushort node = 1) override; //伺服报警清除通用IO
	short ClearComPos() override;
	short ClearEncoderPos() override;
	short ClearPos() override;	 /// 清除轴位置
	short SetSL_Limit(ushort model) override;
	short SetEL_Limit(ushort model, ushort logic) override;
	short SetSpeed(double speed, double acc, double dec) override;
	short  ResetTarget(double destine) override;

																			
	void Home() override;

	short MoveTo(double destine) override; //绝对运动
	/// sync mode motion, move a distance relative to current axis' position
	/// 0:successful  not zero: error
	short MoveRelative(double distance, bool bHome = true) override;//相对运动
	/// jog start or stop
	short Jog(bool start, int dirction) override;
	short Jog(double step)override;
	void Update() override;
	void Stop() override;
	void Pause() override;
	void Resume()override;


};
