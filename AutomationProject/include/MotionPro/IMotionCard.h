#pragma once
#include <afx.h>
#include "IAxis.h"
#include <map>
#include "IIOCard.h"
class IMotionCard : public IIOCard
{

public:
	IMotionCard(CardInfo config):IIOCard(config)
	{
	
	}
//protected:
//	std::map<CString, IAxis> m_Axes;
public:
	double SpeedScale;

	virtual	IAxis*  GenerateAxis(AxisConfig param)  = 0;

	virtual  ~IMotionCard() {};
#pragma region 扩展
	//							    <summary>
	//							    2D interpolation general function
	//							    the speed setting will use the first axis' passed in axes array
	//							    </summary>
	//							    <param name="mode">
	//							    0: 2D linear
	//							    1: 2D Arc, center and angle mode. need to add angle in the other param, unit is radian
	//							    2: 2D arc, center and end point mode, others: the first is direction
	//							    </param>
	//							    <param name="axes">interpolation axes array, the first axis determine the motion speed</param>
	//							    <param name="posArray">destination or the center of arc</param>
	//							    <param name="isRelative"></param>
	//							    <param name="others"></param>
	//int Interpolation2D(int ptid, int mode, int[] axes, double[] positions, bool isRelative, params double[] others);

	// 标点 表格
	//#region point table
	//	 <summary>
	//	 Initialize the point table move
	//	 </summary>
	//	 <returns>point table ID, default is 0</returns>

	//	初始化
	//	int PTInitial(int[] axes, double speed, double acc, double dec, bool isRelative, int ptId);

	// <summary>
	// add line segement into point table, it should firstly call <see cref="PointTableInitial"/>
	// </summary>
	// <param name="ptbId"></param>
	// <param name="speed"></param>
	// <param name="endSpeed"></param>
	// <param name="pos"></param>
	//int PTAddLine(int ptbId, double speed, double endSpeed, double[] pos);

	// <summary>
	// add arc with center & angle, , it should firstly call <see cref="PointTableInitial"/>
	// </summary>
	// <param name="center"></param>
	// <param name="angle"></param>

	//添加弧度      Id             速度            结束速度      中心点          角度
	//int PTAddArc(int ptbId, double speed, double endSpeed, PointF center, double angle);

	// <summary>
	// add arc with center & end position, , it should firstly call <see cref="PointTableInitial"/>
	// </summary>
	// <param name="center"></param>
	// <param name="angle"></param>
	//int PTAddArc(int ptbId, double speed, double endSpeed, PointF center, PointF end);

	// <summary>
	// Set do command to sync with other motions, , it should firstly call <see cref="PointTableInitial"/>
	// </summary>
	// <param name="ptbId"></param>
	// <param name="doChannel"></param>
	// <param name="state">1: on, 0: off</param>
	//int PTAddDO(int ptbId, int doChannel, int state);

	// <summary>
	// start point table move, it should firstly call <see cref="PointTableInitial"/>
	// </summary>
	// <param name="ptbId"></param>
	// <param name="axes"></param>
	//int PTStart(int ptbId, int[] axes, PTProc extraProc = null);

	// <summary>
	// add delay in to the PT motion
	// </summary>
	// <param name="ptbId"></param>
	// <param name="delay">delay in mini second</param>
	// <returns>0:Pass, 1:abnormal</returns>
	//int PTDelay(int ptbId, int delay);
	//#endregion
#pragma endregion
};

