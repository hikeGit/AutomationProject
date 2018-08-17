#pragma once
#include <afx.h>
//#include "IMotionCard.h"
#include "ILine.h"

#ifndef USHORT
#define USHORT
typedef unsigned short  ushort;
#endif

typedef struct  tagHomeParam //�������
{
	/// home mode, 0: ORG; 1: EL; 2: EZ ����ģʽ
	int Mode;

	/// home direction, 1: positive direction; -1: negative direction ���㷽��
	int Direction;

	/// home curve factor, 0~1, 0:T-curve; 1:S-curve, default is 0.5 //��������Ҫ��
	double CurveFactor;

	/// homing acceleration & deceleration //�����ٶ�ģʽ�����ٻ��� & ���ٻ���
	double Acc;

	//�����ٶ�
	double StartSpeed;

	//�ٶ�
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

typedef  struct tagAxisConfig//����
{
	CString Name;
	CString DisplayName;
	CString CardName;

	int CardID;
	int Index;

	HomeParam HomeSetting;

	/// Axis position direction //���ֱ��λ��,�����򣬹涨λ����ʵ��λ���Ƿ���ͬ ȡֵ -1 �� 1 
	int Direct;

	/// axis resolution, pulse count per mm //������� ��λMM����
	double CountPerMM;

	/// The logic of PEL/MEL input signal, 0: Negative logic, not inverse, 1: Positive logic, inverse logic
	short LimitLogic;//�߼���ƽ

	 /// the logic of origin sensor, 0: not inverse; 1: inverse
	short OriginLogic; //ԭ��

	/// alarm sensor logic, 0: low active; 1: high active
	short AlarmLogic;//����

	/// set the puls out mode; 0,Negative logic 1, Positive logic. not used for 2048C
	short OutMode;//���ģʽ

	/// whether read encoder position as the motion position
	bool UseEncoder;//������

	bool UseLimit_SL;//����λ

}AxisConfig;

typedef enum enumAxisState //������
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
	AxisConfig Config; //����
	/// Axis command position or feedback position in mm
	double Position = {0};//λ��

	/// ratio of current speed, it can be used for debug motion, easily change all speed to slow or full speed
	double SpeedScale = 0;

	/// motion speed
	double Speed = 0;

	/// motion acceleration
	double Acc = 0;

	/// motion deceleration
	double Dec = 0;

	/// whether it is servo on
	bool bIsServoOn = false;//�ŷ�ʹ��

							   /// whether axis is homed
	bool bHomed = false;//��ԭ
	bool bMoving = false;

	/// Axis status
	AxisState State = Idle;

	/// Axis Error message
	CString ErrorMessage; //�쳣��Ϣ

	/// positive end limit triggered
	bool bPositiveEL =false; //����λ

	/// negative end limit triggered
	bool bNegativeEL = false; //����λ

	/// home sensor triggered
	bool bHomeSensor = false;

	/// axis home function
	virtual	void Home() =0;

	/// Servo on/off the motor
	virtual short ServoOn(bool onOff) = 0;
	virtual short ServeOn(ushort card, ushort index, bool on, bool can = false, ushort node = 1) = 0;
	virtual	short ServeOn(bool onOff, IOutputLine * index) = 0;
	/// ����ᱨ��,����Щ������
	virtual	short ClearError() = 0;
	virtual	short ClearError(IOutputLine  * index) = 0;
	virtual	short ClearError(ushort card, ushort index, bool can = false, ushort node = 1) = 0;//�ŷ��������ͨ��IO																						  
	virtual short ClearPos() = 0;/// �����λ��
	virtual	short ClearComPos() = 0;
	virtual	short ClearEncoderPos() = 0;
	//model ������λ���������ֹ�������logic ��Ч��ƽ
	virtual	short SetEL_Limit(ushort model, ushort logic) = 0;
	virtual	short SetSL_Limit(ushort model) = 0;
																							 
	virtual	short SetSpeed(double speed, double acc, double dec) = 0; /// Set Axis moving speed
	/// usually for change the motion target before the motion completed
	/// most card has this feature
	virtual	short ResetTarget(double destine) = 0;

	/// sync mode motion function, move to destination
	/// 0:successful  not zero: error
	virtual short MoveTo(double destine) = 0;//�����˶�

	/// sync mode motion, move a distance relative to current axis' position
	/// 0:successful  not zero: error
	virtual	short MoveRelative(double distance, bool bHome = true) = 0;//����˶�

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


