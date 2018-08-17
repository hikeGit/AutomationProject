#include "stdafx.h"
#include "..\include\MotionPro\Machine.h"

Machine * Machine::instance = 0;
CCriticalSection Machine::instanceLock;
//const  int Machine::InfoNum = 14;
Machine::Machine()
{
	m_strParamPath = GetExeDirectory() + _T("Param\\ParamConfig.mdb");
	m_strTeachingSheet = _T("位置参数");
	GetTeachingData();
}

Machine::~Machine()
{
	if (instance != NULL)
	{
		delete instance;
	}
}

 bool Machine::LoadPositions(std::vector<std::map<CString, CString>> & data)
{
	std::vector<std::map<CString, CString>> read;

	bool  rtn = ReadFormData(m_strParamPath,m_strTeachingSheet,  std::vector<CString>(PositionInfo, PositionInfo + InfoNum),read);
	if (rtn)
	{
		data = read;
		return true;
	} 
	else return false;
}

 void Machine::GetTeachingData()
 {
	 using  structData = struct  tagData
	 {
		 CAxisPosition axisPos;
		 CTeachPosition teachPos;//存储除axisposition之外的信息
	 };
	 using mulmap = std::multimap<CString, structData>;
	 using mulite = std::multimap<CString, structData>::const_iterator;
	 mulmap posMap;
	 mulite tempIte;

	 std::vector<std::map<CString, CString>> readData;
	 if (LoadPositions(readData))
	 {
		 structData  conData;
		 TCHAR *endPtr;
		 for (auto item : readData)
		 {	
			 conData.teachPos.m_strPosName = item[(PositionInfo[enumTeachInfo::PosName])];
			 conData.teachPos.m_strDisplayName = item[(PositionInfo[enumTeachInfo::PosNameDisplay])];
			 conData.axisPos.m_strAxisName = item[(PositionInfo[enumTeachInfo::AxisName])]; 
			 conData.axisPos.m_dPosition = _tcstod(item[(PositionInfo[enumTeachInfo::Position])],&endPtr);  
			 conData.axisPos.m_dSpeed = _tcstod(item[(PositionInfo[enumTeachInfo::Speed])], &endPtr);
			 conData.axisPos.m_dStartSpeed = _tcstod(item[(PositionInfo[enumTeachInfo::StartSpeed])], &endPtr);
			 conData.axisPos.m_dEndSpeed = _tcstod(item[(PositionInfo[enumTeachInfo::EndSpeed])], &endPtr);
			 conData.axisPos.m_dAcc = _tcstod(item[(PositionInfo[enumTeachInfo::Acc])],  &endPtr);
			 conData.axisPos.m_dDec = _tcstod(item[(PositionInfo[enumTeachInfo::Dec])], &endPtr);
			 conData.axisPos.m_dS = _tcstod(item[(PositionInfo[enumTeachInfo::SP])], &endPtr);
			 conData.teachPos.m_strGroup = item[(PositionInfo[enumTeachInfo::Group])]; 
			 conData.teachPos.m_strCategory = item[(PositionInfo[enumTeachInfo::Category])];  
			 conData.teachPos.m_strDescription = item[(PositionInfo[enumTeachInfo::Description])]; 
			 conData.teachPos.m_strUpdateTime = item[(PositionInfo[enumTeachInfo::UpdatedTime])]; 

			 posMap.insert(std::pair<CString, structData>(conData.teachPos.m_strPosName, conData));
		 }

		 std::multimap<CString, structData>::iterator ite = posMap.begin();
		 while (ite != posMap.end())
		 {
			 std::pair<mulmap::const_iterator, mulmap::const_iterator> pa = posMap.equal_range(ite->first);
			 std::vector<CAxisPosition> axisPos;

			 CTeachPosition tempTeachPos;

			 for (tempIte = pa.first; tempIte != pa.second; tempIte++)
			 {
				 axisPos.push_back(ite->second.axisPos);
			 }
			 
			 m_TeachSetting.TeachPositions.push_back(CTeachPosition(ite->first, axisPos,
			 { ite->second.teachPos.m_strDisplayName ,
				ite->second.teachPos.m_strCategory,
			    ite->second.teachPos.m_strDescription , 
				ite->second.teachPos.m_strUpdateTime , 
				ite->second.teachPos.m_strGroup 
			 }));

			 size_t num =  posMap.erase(ite->first);
			 ite = posMap.begin();
		 }
	 }
	 else
	 {
		 MessageBox(NULL, _T("加载位置参数数据库失败!"), _T("加载失败"), MB_TOPMOST);
	 }
 }


 std::map<CString, CString>  Machine::AxisInfoMap(CString  position,CString axis)
 {
	 std::map<CString, CString> tempMap;
	 for (auto item : m_TeachSetting.TeachPositions)
	 {
		 if (position == item.m_strPosName)
		 {
			 for (auto itemSub : item.m_AxesPosition)
			 {
				 if (axis == itemSub.m_strAxisName)
				 {
					 tempMap.insert(std::pair<CString, CString>(PositionInfo[enumTeachInfo::AxisName], itemSub.m_strAxisName));
					 tempMap.insert(std::pair<CString, CString>(PositionInfo[enumTeachInfo::Position], SetDoubleToCString(itemSub.m_dPosition)));
					 tempMap.insert(std::pair<CString, CString>(PositionInfo[enumTeachInfo::Speed], SetDoubleToCString(itemSub.m_dSpeed)));
					 tempMap.insert(std::pair<CString, CString>(PositionInfo[enumTeachInfo::StartSpeed], SetDoubleToCString(itemSub.m_dStartSpeed)));
					 tempMap.insert(std::pair<CString, CString>(PositionInfo[enumTeachInfo::EndSpeed], SetDoubleToCString(itemSub.m_dEndSpeed)));
					 tempMap.insert(std::pair<CString, CString>(PositionInfo[enumTeachInfo::Acc], SetDoubleToCString(itemSub.m_dAcc)));
					 tempMap.insert(std::pair<CString, CString>(PositionInfo[enumTeachInfo::Dec], SetDoubleToCString(itemSub.m_dDec)));
					 tempMap.insert(std::pair<CString, CString>(PositionInfo[enumTeachInfo::SP], SetDoubleToCString(itemSub.m_dS)));
					 return tempMap;
				 }
			 }
		 }
	 }

	 return tempMap;
 }

 std::map<CString, CString>  Machine::TeachInfoMap(CString position)
 {
	 std::map<CString, CString> tempMap;
	 for (auto itemSub : m_TeachSetting.TeachPositions)
	 {
		 if (position == itemSub.m_strPosName)
		 {
			 itemSub.m_strUpdateTime = SetCurrentTimeToCString();
			 tempMap.insert(std::pair<CString, CString>(PositionInfo[enumTeachInfo::PosName], itemSub.m_strPosName));
			 tempMap.insert(std::pair<CString, CString>(PositionInfo[enumTeachInfo::PosNameDisplay], itemSub.m_strDisplayName));
			 tempMap.insert(std::pair<CString, CString>(PositionInfo[enumTeachInfo::Group], itemSub.m_strGroup));
			 tempMap.insert(std::pair<CString, CString>(PositionInfo[enumTeachInfo::UpdatedTime], itemSub.m_strUpdateTime));
			 tempMap.insert(std::pair<CString, CString>(PositionInfo[enumTeachInfo::Category], itemSub.m_strCategory));
			 tempMap.insert(std::pair<CString, CString>(PositionInfo[enumTeachInfo::Description], itemSub.m_strDescription));
			 return tempMap;
		 }
	 }

	 return tempMap;
 }


 bool Machine::SavePosition(const CTeachPosition  * const posItem, const CString axisName)
 {
	 std::map<CString,CString> keys;
	 std::map<CString,CString> values;

	 for (auto item : posItem->m_AxesPosition)
	 {
		 if (item.m_strAxisName == axisName)
		 {
			 keys = TeachInfoMap(posItem->m_strPosName);
			 values = AxisInfoMap(posItem->m_strPosName, item.m_strAxisName);

			 keys.insert(std::pair<CString, CString>(PositionInfo[enumTeachInfo::AxisName], values[PositionInfo[enumTeachInfo::AxisName]]));
			 keys.erase(PositionInfo[enumTeachInfo::UpdatedTime]);
			 keys.erase(PositionInfo[enumTeachInfo::Description]);
			 keys.erase(PositionInfo[enumTeachInfo::Group]);
			 keys.erase(PositionInfo[enumTeachInfo::PosNameDisplay]);

			 values.erase(PositionInfo[enumTeachInfo::AxisName]);
			 values.insert(std::pair<CString, CString>(PositionInfo[enumTeachInfo::UpdatedTime], keys[PositionInfo[enumTeachInfo::UpdatedTime]]));

			  return ModifyFormData(m_strParamPath, m_strTeachingSheet, keys, values);
		 }
	 }

	 return false;
 }


 bool Machine::SavePosition(const CTeachPosition   *  const posItem, const CAxisPosition  * const axisItem)
 {
	 std::map<CString, CString> keys;
	 std::map<CString, CString> values;

	 for (auto item : posItem->m_AxesPosition)
	 {
		 if (item.m_strAxisName == axisItem->m_strAxisName)
		 {
			 keys = TeachInfoMap(posItem->m_strPosName);
			 values = AxisInfoMap(posItem->m_strPosName, item.m_strAxisName);

			 keys.insert(std::pair<CString, CString>(PositionInfo[enumTeachInfo::AxisName], values[PositionInfo[enumTeachInfo::AxisName]]));
			 keys.erase(PositionInfo[enumTeachInfo::UpdatedTime]);
			 keys.erase(PositionInfo[enumTeachInfo::Description]);
			 keys.erase(PositionInfo[enumTeachInfo::Group]);
			 keys.erase(PositionInfo[enumTeachInfo::PosNameDisplay]);

			 values.erase(PositionInfo[enumTeachInfo::AxisName]);
			 values.insert(std::pair<CString, CString>(PositionInfo[enumTeachInfo::UpdatedTime], keys[PositionInfo[enumTeachInfo::UpdatedTime]]));

			 return ModifyFormData(m_strParamPath, m_strTeachingSheet, keys, values);
		 }
	 }
	 return false;
 }


 bool Machine::SaveAllPositions()
 {
	 std::map<CString, CString>  rowTeachData;
	 std::map<CString, CString>  rowAxisData;
	 std::vector<std::map<CString, CString>> allData;

	 for (auto item : m_TeachSetting.TeachPositions)
	 {
		 rowTeachData = TeachInfoMap(item.m_strPosName);
		 for (auto itemSub : item.m_AxesPosition)
		 {
			 rowAxisData = AxisInfoMap(item.m_strPosName, itemSub.m_strAxisName);
		 }
	 }
	 for (auto item : rowAxisData)
	 {
		 rowTeachData.insert(item);
	 }

	 allData.push_back(rowTeachData);

	 return  ModifyFormDataAll(m_strParamPath, m_strTeachingSheet, allData);

 }

