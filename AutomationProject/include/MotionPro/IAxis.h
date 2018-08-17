#pragma once
#include <afx.h>
//#include "IMotionCard.h"
#include "ILine.h"

#ifndef USHORT
#define USHORT
typedef unsigned short  ushort;
#endif

typedef struct  tagHomeParam //回零参数
{
	/// home mode, 0: ORG; 1: EL; 2: EZ 回零模式
	int Mode;

	/// home direction, 1: positive direction; -1: negative direction 回零方向
	int Direction;

	/// home curve factor, 0~1, 0:T-curve; 1:S-curve, default is 0.5 //回零曲线要素
	double CurveFactor;

	/// homing acceleration & deceleration //回零速度模式，加速回零 & 减速回零
	double Acc;

	//启动速度
	double StartSpeed;

	//速度
	double Speed;

	/// offset from home stop sensor
	double Offset;

	/// EZ alignment enabled, default is false. don't know what's this???
	bool EZAlignEnabled;

	/// speed when leaving homing sensor
	double LeaveHomeSpeed;

	/// position when homed
	//double HomePosition;

}HomeParam;

typedef  struct tagAxisConfig//配置
{
	CString Name;
	CString DisplayName;
	CString CardName;

	int CardID;
	int Index;

	HomeParam HomeSetting;

	/// Axis position direction //轴的直接位置,正反向，规定位置与实际位置是否相同 取值 -1 与 1 
	int Direct;

	/// axis resolution, pulse count per mm //脉冲计数 单位MM毫米
	double CountPerMM;

	/// The logic of PEL/MEL input signal, 0: Negative logic, not inverse, 1: Positive logic, inverse logic
	short LimitLogic;//逻辑电平

	 /// the logic of origin sensor, 0: not inverse; 1: inverse
	short OriginLogic; //原点

	/// alarm sensor logic, 0: low active; 1: high active
	short AlarmLogic;//报警

	/// set the puls out mode; 0,Negative logic 1, Positive logic. not used for 2048C
	short OutMode;//输出模式

	/// whether read encoder position as the motion position
	bool UseEncoder;//编码器

	bool UseLimit_SL;//软限位

}AxisConfig;

typedef enum enumAxisState //轴声明
{
	Idle,
	Moving,
	MoveDone,
	MotionError,
	AxisError,
} AxisState;

class IAxis
{
public:
	IAxis(AxisConfig config):Config(config)
	{

	}
	IAxis()
	{

	}

public:
	virtual ~IAxis() {};
public:
	AxisConfig Config; //设置
	/// Axis command position or feedback position in mm
	double Position = {0};//位置

	/// ratio of current speed, it can be used for debug motion, easily change all speed to slow or full speed
	double SpeedScale = 0;

	/// motion speed
	double Speed = 0;

	/// motion acceleration
	double Acc = 0;

	/// motion deceleration
	double Dec = 0;

	/// whether it is servo on
	bool bIsServoOn = false;//伺服使能

							   /// whether axis is homed
	bool bHomed = false;//回原
	bool bMoving = false;

	/// Axis status
	AxisState State = Idle;

	/// Axis Error message
	CString ErrorMessage; //异常消息

	/// positive end limit triggered
	bool bPositiveEL =false; //正限位

	/// negative end limit triggered
	bool bNegativeEL = false; //负限位

	/// home sensor triggered
	bool bHomeSensor = false;

	/// axis home function
	virtual	void Home() =0;

	/// Servo on/off the motor
	virtual short ServoOn(bool onOff) = 0;
	virtual short ServeOn(ushort card, ushort index, bool on, bool can = false, ushort node = 1) = 0;
	virtual	short ServeOn(bool onOff, IOutputLine * index) = 0;
	/// 清除轴报警,对有些轴有用
	virtual	short ClearError() = 0;
	virtual	short ClearError(IOutputLine  * index) = 0;
	virtual	short ClearError(ushort card, ushort index, bool can = false, ushort node = 1) = 0;//伺服报警清除通用IO																						  
	virtual short ClearPos() = 0;/// 清除轴位置
	virtual	short ClearComPos() = 0;
	virtual	short ClearEncoderPos() = 0;
	//model 正负限位各自允许禁止的情况，logic 有效电平
	virtual	short SetEL_Limit(ushort model, ushort logic) = 0;
	virtual	short SetSL_Limit(ushort model) = 0;
																							 
	virtual	short SetSpeed(double speed, double acc, double dec) = 0; /// Set Axis moving speed
	/// usually for change the motion target before the motion completed
	/// most card has this feature
	virtual	short ResetTarget(double destine) = 0;

	/// sync mode motion function, move to destination
	/// 0:successful  not zero: error
	virtual short MoveTo(double destine) = 0;//绝对运动

	/// sync mode motion, move a distance relative to current axis' position
	/// 0:successful  not zero: error
	virtual	short MoveRelative(double distance, bool bHome = true) = 0;//相对运动

	/// jog start or stop
	virtual	short Jog(bool start, int dirction) = 0;
	/// step jog
	virtual	short Jog(double step) = 0;


	/// update axis state
	virtual	void Update() = 0;

	/// stop the movement immediately
	virtual	void Stop() = 0;

	/// stop current move, but can be resumed later
	/// it usually stop the axis, save the target position and send the command again later
	virtual	void Pause() = 0;

	/// resume motion paused, it usually resend the motion command
	virtual	void Resume() = 0;


};


