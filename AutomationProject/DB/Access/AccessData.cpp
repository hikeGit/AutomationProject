#include "stdafx.h"
#include "..\..\include\DB\AccessData.h"
/************************************************* 

*************************************************/ 


//标识OLE初始化状态，以防重复初始化
bool CDataAccess::ms_bInitState = false;
bool CDataAccess::ms_bAccessConnected = false;
 _ConnectionPtr CDataAccess::m_pConnection;
 _RecordsetPtr   CDataAccess::m_pRecordset;
 _CommandPtr   CDataAccess::m_pCommand;

CDataAccess::CDataAccess()
{

} 

CDataAccess::~CDataAccess()
{
    
}
void CDataAccess::DataBaseExit()
{
	if(NULL!=m_pConnection)
	{
        m_pConnection.Release();
	}

	if(NULL!=m_pRecordset)
	{
        m_pRecordset.Release();
	}
	
	if(NULL!=m_pCommand)
	{
        m_pCommand.Release();
	}
	
	ms_bAccessConnected=false;
	ms_bInitState=false;

    CoUninitialize();
}
bool CDataAccess::DataBaseInit(CString strPath)
{
	this->AccessInit(true); 
	if(!this->Connect2DataBase(strPath))
	{
		return false;
	}
	return true;
}
/***************************************************************************************
*函 数 名：void CDataAccess::AccessInit(bool bPassWordUseOrNot)

*输入参数：bool bPassWordUseOrNot  ：标识OLE初始化状态，以防重复初始化
           bPassWordUseOrNot==0，不使用密码
		   bPassWordUseOrNot==1，使用密码

*函数功能：数据库OLE初始化

*返 回 值：无
***************************************************************************************/
void CDataAccess::AccessInit(bool bPassWordUseOrNot)
{
	
	if(!ms_bInitState)
	{
		CoInitialize(NULL);
		if (!CoInitialize(NULL))                          
		{
			AfxMessageBox(_T("OLE初始化失败！"));
            return;
		}
		ms_bInitState = 1;
	}
	if(bPassWordUseOrNot)  //判断数据库是否使用密码打开
	{
		SetPassWordState(USEPASSWORD);

		SetPassWord(_T("orchidflower")); //数据库密码
	}
	else
	{
		SetPassWordState(NOTUSEPASSWORD);
	}
}
/***************************************************************************************
*函 数 名：CDataAccess::SetPassWordState(bool bNewState)

*输入参数：bool bNewState 密码使用情况
            bNewState==0：没使用密码
			bNewState==1：使用密码

*函数功能：数据库密码使用状态

*返 回 值：无
***************************************************************************************/
void CDataAccess::SetPassWordState(bool bNewState)
{
	this->m_bPassWordEn = bNewState;
}
/***************************************************************************************
*函 数 名：CDataAccess::GetPassWordState(void)

*输入参数：无

*函数功能：获取数据库密码使用状态

*返 回 值：密码使用状态
***************************************************************************************/
bool CDataAccess::GetPassWordState(void)
{
	return m_bPassWordEn;
}
/***************************************************************************************
*函 数 名：CDataAccess::SetPassWord(CString PassWord)

*输入参数：CString PassWord ：数据库密码
          
*函数功能：设置数据库密码

*返 回 值：无
***************************************************************************************/
void CDataAccess::SetPassWord(CString PassWord)
{
	m_PassWord = PassWord;
}
/***************************************************************************************
*函 数 名：CDataAccess::GetPassWord(void)

*输入参数：无
          
*函数功能：获取数据库密码

*返 回 值：无
***************************************************************************************/
CString CDataAccess::GetPassWord(void)
{
	return m_PassWord;
}

/***************************************************************************************
*函 数 名：bool CDataAccess::Connect2DataBase(CString Path)

*输入参数：CString Path  ：数据库的存放路径

*函数功能：连接数据库

*返 回 值：true， 连接成功
           false，连接失败
***************************************************************************************/
bool CDataAccess::Connect2DataBase(CString Path)
{
	static CString temPath=Path;
	if(temPath!=Path)
	{
		DisconnectDataBase();
		temPath=Path;
		ms_bAccessConnected=false;
	}
	try                   
	{	
		CString l_NameTemp;
		if(GetPassWordState())
		{
			CString psw=GetPassWord();
			l_NameTemp = _T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=") + Path + _T(";Jet OLEDB:DataBase password=") 
				                + GetPassWord();
		}
		else
		{
			l_NameTemp = _T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=") + Path;
		}

		if(!ms_bAccessConnected)
		{
			ms_bAccessConnected=true;
			m_pConnection.CreateInstance(__uuidof(Connection));
		    m_pConnection->Open((_bstr_t)l_NameTemp,_T(""),_T(""),adModeUnknown);
		}		
	}

	catch(_com_error e)
	{
		/*CString Msg=(_T("数据库连接失败，确认数据库")+Path+_T("是否存在"));
		AfxMessageBox(Msg);*/
		return false;
	} 
	
	return true;
}

/***************************************************************************************
*函 数 名：bool CDataAccess::DisconnectDataBase(void)

*输入参数：无

*函数功能：取消数据库连接

*返 回 值：无
***************************************************************************************/
void CDataAccess::DisconnectDataBase(void)
{
	if(m_pConnection)
	{
		if(m_pConnection->State)
			m_pConnection->Close();
		m_pConnection = NULL;
	}
	//CoUninitialize();
}
/***************************************************************************************
*函 数 名：bool CDataAccess::Connect2DataBase(CString Path)

*输入参数：CString FormName  ：数据表名称

*函数功能：打开数据表

*返 回 值：true， 打开成功
           false，打开失败
***************************************************************************************/
bool CDataAccess::OpenForm(CString strSQL)
{
	try
	{

		m_pRecordset.CreateInstance(__uuidof(Recordset));

		m_pRecordset->Open((_variant_t)(strSQL),   // 查询表中字段
							m_pConnection.GetInterfacePtr(),	 // 获取库接库的IDispatch指针
							adOpenDynamic,
							adLockOptimistic,
							adCmdText);
	}
	catch(_com_error e)
	{
	  AfxMessageBox(e.ErrorMessage());
		
		return FALSE;
	}

	return TRUE;
}

/***************************************************************************************
*函 数 名：bool CDataAccess::CreateForm(CString AccessPath,CString FormName)

*输入参数：CString FormName  ：数据表名称

*函数功能：打开数据表

*返 回 值：true， 打开成功
           false，打开失败
***************************************************************************************/
bool CDataAccess::CreateForm(CString AccessSQL,CString FormName)
{
	//OpenForm(AccessSQL);
 //   
	//m_pCommand.CreateInstance(__uuidof(Command));

	//try
	//{
	//	variant_t RecordAffected;
	//	CString Command1,Command2;

	//	Command1.Format(_T("CREATR TABLE INTO %s(ID,CreateTime,ParamDescription,Value,ParamUnit,ParmMax)");
 //    

	//	
	//}
	//catch(_com_error e)
	//{
	//    AfxMessageBox(e.ErrorMessage());
	//	
	//	return FALSE;
	//}


	return TRUE;
}

/***************************************************************************************
*函 数 名：WriteData(variant_t DataField,variant_t Content)

*输入参数：variant_t DataField  ：字段名称
           variant_t Content：插入的字段内容

*函数功能：写入数据库参数

*返 回 值：无
***************************************************************************************/
void CDataAccess::WriteData(variant_t DataField,variant_t Content)
{
  m_pRecordset->PutCollect(DataField,Content);
  m_pRecordset->Update();
}
/***************************************************************************************
*函 数 名：WriteDataEx(variant_t DataField,variant_t Content,int nRow)

*输入参数：variant_t DataField  ：字段名称
           variant_t Content：插入的字段内容
		   int nRow ：指定的记录行

*函数功能：指定行之后增加/修改记录

*返 回 值：无
***************************************************************************************/
void CDataAccess::WriteDataEx(variant_t DataField,variant_t Content,int nRow)
{
	m_pRecordset->MoveFirst();
	for(int i = 0; i < nRow;i++)
	{
		m_pRecordset->MoveNext();
	}
	m_pRecordset->PutCollect(DataField,Content);
	m_pRecordset->Update();
}

/***************************************************************************************
*函 数 名：CDataAccess::ReadData(variant_t Index)

*输入参数：variant_t Index  ：字段名称

*函数功能：获取字段的记录

*返 回 值：true， 成功
           false，失败
***************************************************************************************/
variant_t CDataAccess::ReadData(variant_t Index)
{
  return m_pRecordset->GetCollect(Index);
}
/***************************************************************************************
*函 数 名：CDataAccess::ReadDataEx(variant_t Index,int nRow)

*输入参数：variant_t Index  ：字段名称
           int nRow ：指定的记录行
           

*函数功能：获取指定字段的记录

*返 回 值：true， 成功
           false，失败
***************************************************************************************/
variant_t CDataAccess::ReadDataEx(variant_t Index,int nRow)
{
	m_pRecordset->MoveFirst();
	for(int i = 0; i < nRow;i++)
	{
		m_pRecordset->MoveNext();
	}
	return m_pRecordset->GetCollect(Index);
}
/***************************************************************************************
*函 数 名：CDataAccess::GetRowCount()

*输入参数：无
           
*函数功能：获取字段记录总数

*返 回 值：字段记录总数
***************************************************************************************/
int  CDataAccess::GetRowCount()
{
	int l_nCount = 0;
	if(!m_pRecordset->adoBOF)			
	{
		m_pRecordset->MoveFirst();
		for(;!m_pRecordset->adoEOF;m_pRecordset->MoveNext())
		{
			l_nCount++;
		}
	}
	return l_nCount;
}

//创建一个数据表
bool CDataAccess::CreatMehineForm(CString strPath,CString strFormName)
{
	return true;
}

//删除数据库的指定行
bool CDataAccess::DeleteFormData(CString strPath,CString strFormName,int nIndex)
{
	DataBaseInit(strPath); //打开数据库

	CString SQL=_T("SELECT * FROM ")+strFormName;
	if(!(OpenForm(SQL)))  //当前工作文档
	{
		CString Msg=_T("打开")+strFormName+_T("数据表失败！");
		AfxMessageBox(Msg,MB_TOPMOST);
		return false;
	}

	if(!m_pRecordset->adoBOF)			//如果数据库不为空
		m_pRecordset->MoveFirst();

	for(int i=0;!m_pRecordset->adoEOF; m_pRecordset->MoveNext()) //计算总数
	{
		if (i==nIndex)
		{
			m_pRecordset->Delete(adAffectCurrent);
		}
		i++;
	}
	
	return true;
}
//删除最后一行
bool CDataAccess::DelFormDataEnd(CString strPath,CString strFormName)
{
	DataBaseInit(strPath); //打开数据库

	CString SQL=_T("SELECT * FROM ")+strFormName;
	if(!(OpenForm(SQL)))  //当前工作文档
	{
		CString Msg=_T("打开")+strFormName+_T("数据表失败！");
		AfxMessageBox(Msg,MB_TOPMOST);
		return false;
	}

	if(!m_pRecordset->adoBOF)
	{
		m_pRecordset->MoveLast();
		m_pRecordset->Delete(adAffectCurrent);
	}

	return true;
}
//清空数据库的指定数据表的内容
bool CDataAccess::ClearMechineForm(CString strPath,CString strFormName)
{
	DataBaseInit(strPath); //打开数据库

	CString SQL=_T("SELECT * FROM ")+strFormName;
	if(!(OpenForm(SQL)))  //当前工作文档
	{
		CString Msg=_T("打开")+strFormName+_T("数据表失败！");
		AfxMessageBox(Msg,MB_TOPMOST);
		return false;
	}

	if(!m_pRecordset->adoBOF)			//如果数据库不为空
		m_pRecordset->MoveFirst();

	for(int i=0;!m_pRecordset->adoEOF; m_pRecordset->MoveNext()) //计算总数
	{
		m_pRecordset->Delete(adAffectCurrent);
	}
	
	return true;
}
//获取表格的总行数
bool CDataAccess::GetFormRowSize(CString strPath,CString strFormName,unsigned long &nSize)
{
	CString strTemp;

	DataBaseInit(strPath);

	CString SQL=_T("SELECT * FROM ")+strFormName;
	if(!(OpenForm(SQL)))  //当前工作文档
	{
		CString Msg=_T("打开")+strFormName+_T("数据表失败！");
		AfxMessageBox(Msg,MB_TOPMOST);
		return false;
	}
	nSize=0;
	for(;!m_pRecordset->adoEOF; m_pRecordset->MoveNext()) //读取数据路径
	{
		nSize=nSize+1;
	}

	return true;
}

bool CDataAccess::ReadFormData(CString strPath, CString strFormName, std::vector<CString> & vec, std::vector<std::map<CString,CString> > &resultData)
{
	DataBaseInit(strPath);

	CString SQL = _T("SELECT * FROM ") + strFormName;
	if (!(OpenForm(SQL)))  //当前工作文档
	{
		CString Msg = _T("打开") + strFormName + _T("数据表失败！");
		AfxMessageBox(Msg, MB_TOPMOST);
		return false;
	}
	std::vector<std::map<CString,CString>> allData;
	std::map<CString,CString>  rowData;
	CString strCurReading = _T("NoReading");//当前正在读的字段，报警用
	CString strTemp;
	int i = 0;

	try
	{
		if (m_pRecordset->GetFields()->Count <(long) vec.size())
		{
			throw std::exception("传入的字段数大于数据库实际字段数");
		}
		for (; !m_pRecordset->adoEOF; m_pRecordset->MoveNext()) //读取数据路径
		{
			for ( i = 0; i <(int) vec.size(); i++)
			{
				strCurReading = vec[i];
				strTemp = m_pRecordset->GetCollect((const _variant_t)vec[i]);
				rowData.insert(std::pair<CString, CString>(vec[i], strTemp));
			}
			allData.push_back(rowData);
			rowData.clear();
		}
		resultData = allData;
	}
	catch (std::exception e)
	{
		CString erro(e.what());
		CString Msg = _T("读取") + strFormName + _T("数据表失败！")+_T("当前字段：")+strCurReading +_T(" \n") + _T("异常为:") + erro;
		AfxMessageBox(Msg, MB_TOPMOST);
		return false;
	}
	catch (_com_error  e)
	{
		CString erro((LPCTSTR)e.Description());
		CString Msg = _T("读取") + strFormName + _T("数据表失败！\n") + _T("异常为:") + erro ;
		AfxMessageBox(Msg, MB_TOPMOST);
		return false;
	}
	catch (...)
	{
		CString t;
		t.Format(_T("index = %d"), i);
		CString Msg = _T("读取") + strFormName + _T("数据表失败！\n") + _T("未知异常。") + t + _T(":") + strCurReading;
		AfxMessageBox(Msg, MB_TOPMOST);
		return false;
	}
	return true;
}

//读取数据库
bool CDataAccess::ReadFormData(CString strPath,CString strFormName,CString strField,int nIndex,CString& strData)
{
	CString strTemp;

	DataBaseInit(strPath);

	CString SQL=_T("SELECT * FROM ")+strFormName;
	if(!(OpenForm(SQL)))  //当前工作文档
	{
		CString Msg=_T("打开")+strFormName+_T("数据表失败！");
		AfxMessageBox(Msg,MB_TOPMOST);
		return false;
	}

	int temIndex=0;
	for(;!m_pRecordset->adoEOF; m_pRecordset->MoveNext()) //读取数据路径
	{
		if (temIndex==nIndex)
		{
			strData=m_pRecordset->GetCollect((const _variant_t)strField);
		}
		temIndex=temIndex+1;
	}


	return true;
}

//修改数据库
bool CDataAccess::ModifyFormData(CString strPath, CString strFormName, CString strField, CString strData, int nIndex)
{
	_variant_t d_Data = (LPCTSTR)strData;  //CString 转换成数据库的参数类型

	DataBaseInit(strPath);    //打开数据库

	CString SQL = _T("SELECT * FROM ") + strFormName;
	if (!(OpenForm(SQL)))  //当前工作文档
	{
		CString Msg = _T("打开") + strFormName + _T("数据表失败！");
		AfxMessageBox(Msg, MB_TOPMOST);
		return false;
	}
	WriteDataEx((_variant_t)strField, d_Data, nIndex); //写入参数
	return true;
}

//保存所有数据
//需要完善的地方，一是判断传进来的字段数是否小于数据库里的字段数，二是传进来的行数是否小于数据库表的行数（前提时数据库已经存在）
bool  CDataAccess::SaveFormDataAll(CString strPath, CString strFormName, const std::vector<std::map<CString, CString>> &formdata_in)
{

	CString strCurReading = _T("NoReading");
	CString strCurRow = _T("-1");
	CString ErroMsg;
	//直接在表上改(Modify)，后期可以写一个示教点生成器，不用打开数据库，而是根据生成器里的信息自动添加数据(add)
	try
	{
		DataBaseInit(strPath);
		CString SQL = _T("SELECT * FROM ") + strFormName;
		if (!(OpenForm(SQL)))  //当前工作文档
		{
			ErroMsg = _T("打开") + strFormName + _T("数据表失败！");
			throw std::exception((LPCSTR)(LPSTR)ErroMsg.GetBuffer());
		}

		int num = formdata_in[0].size();//传递进来的map数量，即字段信息。
		std::map<CString, CString> inmap = formdata_in[0];//获取传递进来的map字段信
		//判断异常信息
		if (m_pRecordset->GetFields()->Count < num)
		{
			throw std::exception(("传入的字段数大于数据表实际字段数"));
		}
		unsigned long tempcount = 0;
		GetFormRowSize(strPath, strFormName, tempcount);
		if (tempcount< formdata_in.size())
		{
			throw std::exception("需要保存的数据总数大于数据表中存在的数据总数");
		}

		//更改数据库
		int mapindex = 0;
		for (; !m_pRecordset->adoEOF; m_pRecordset->MoveNext()) //一行数据
		{
			for (auto item : formdata_in[mapindex])//某一个字段数据更新
			{				
				m_pRecordset->PutCollect((variant_t)item.first, (variant_t)item.second);
				strCurReading = item.first;
			}
			mapindex++;
			strCurRow.Format(_T("%d"), mapindex);
		}
		m_pRecordset->Update();
	}

	catch (_com_error  e)
	{
		CString erro((LPCTSTR)e.Description());
		CString Msg = _T("保存") + strFormName + _T("数据表失败！\n") + _T("当前行数：") + strCurRow + _T("  当前字段：") + strCurReading + _T("\n异常为:") + erro;
		AfxMessageBox(Msg, MB_TOPMOST);
		return false;
	}
	catch (std::exception e)
	{
		CString erro(e.what());
		CString Msg = _T("保存") + strFormName + _T("数据表失败！") + _T("当前行数：") + strCurRow + _T("  当前字段：") + strCurReading + _T(" \n") + _T("\n异常为:") + erro;
		AfxMessageBox(Msg, MB_TOPMOST);
		return false;
	}
	catch (...)
	{
		CString Msg = _T("读取") + strFormName + _T("数据表失败！\n") + _T("未知异常。") + _T("当前行数：") + strCurRow + _T("  当前字段：") + strCurReading;
		AfxMessageBox(Msg, MB_TOPMOST);
		return false;
	}
	return true;

}
//保存特定行数据
bool CDataAccess::SaveFormData(CString strPath, CString strFormName, const std::map<CString,CString> &savekeys, const std::map<CString, CString> & savedata)
{
	CString strCurReading = _T("NoReading");
	CString strCurRow = _T("-1");
	CString ErroMsg;
	//直接在表上改(Modify)，后期可以写一个示教点生成器，不用打开数据库，而是根据生成器里的信息自动添加数据(add)
	try
	{
		DataBaseInit(strPath);
		CString SQL = _T("SELECT * FROM ") + strFormName;
		if (!(OpenForm(SQL)))  //当前工作文档
		{
			ErroMsg = _T("打开") + strFormName + _T("数据表失败！");
			throw std::exception((LPCSTR)(LPSTR)ErroMsg.GetBuffer());
		}

		//更改数据库
		int mapindex = 0;
		for (; !m_pRecordset->adoEOF; m_pRecordset->MoveNext()) //一行数据
		{
			bool bAllKeysOk = true;
			for (auto item : savekeys)
			{
				if (m_pRecordset->GetCollect((variant_t)item.first) != item.second)
				{
					bAllKeysOk = false;
					mapindex++;
					strCurRow.Format(_T("%d"), mapindex);
					strCurReading = item.first;
					continue;
				}
			}

			if (!bAllKeysOk)
			{
				throw std::exception("保存时需要查找·比对关键字失败");				
			}			
		}

		for (auto item : savedata)
		{
			m_pRecordset->PutCollect((variant_t)item.first, (variant_t)item.second);
		}

		m_pRecordset->Update();
	}

	catch (_com_error  e)
	{
		CString erro((LPCTSTR)e.Description());
		CString Msg = _T("保存") + strFormName + _T("数据表失败！\n") + _T("当前行数：") + strCurRow + _T("  当前字段：") + strCurReading + _T("\n异常为:") + erro;
		AfxMessageBox(Msg, MB_TOPMOST);
		return false;
	}
	catch (std::exception e)
	{
		CString erro(e.what());
		CString Msg = _T("保存") + strFormName + _T("数据表失败！") + _T("当前行数：") + strCurRow + _T("  当前字段：") + strCurReading + _T(" \n") + _T("\n异常为:") + erro;
		AfxMessageBox(Msg, MB_TOPMOST);
		return false;
	}
	catch (...)
	{
		CString Msg = _T("读取") + strFormName + _T("数据表失败！\n") + _T("未知异常。") + _T("当前行数：") + strCurRow + _T("  当前字段：") + strCurReading;
		AfxMessageBox(Msg, MB_TOPMOST);
		return false;
	}
	return true;
}

bool  CDataAccess::ModifyFormDataAll(CString strPath, CString strFormName, const std::vector<std::map<CString, CString>> &formdata)
{

     return	SaveFormDataAll(strPath, strFormName, formdata);
}
bool CDataAccess::ModifyFormData(CString strPath, CString strFormName, const std::map<CString,CString> &savekeys, const std::map<CString, CString> & savedata)
{
	return  SaveFormData(strPath, strFormName, savekeys, savedata);
}


#pragma region 删除
//增加用户管理信息
//bool CDataAccess::AddFormData_UserInfo(CString strPath,CString strFormName,ACSDUserInfo userInfo)
//{
//	CString strTemp;
//
//	DataBaseInit(strPath);
//
//	CString SQL=_T("SELECT * FROM ")+strFormName;
//	if(!(OpenForm(SQL)))  //当前工作文档
//	{
//		CString Msg=_T("打开")+strFormName+_T("数据表失败！");
//		AfxMessageBox(Msg,MB_TOPMOST);
//		return false;
//	}
//	int i=0;
//	while(!m_pRecordset->adoEOF)//移动到最底
//	{
//		m_pRecordset->MoveNext();
//		i++;
//	}
//	m_pRecordset->AddNew();
//
//	CString  str_userLevel;
//	str_userLevel.Format(_T("%d"), userInfo.nUserLevel);
//	WriteData(_T("UsersName"),(variant_t)userInfo.strUserName);
//	WriteData(_T("PWD"),(variant_t)userInfo.strUserPwd);
//	WriteData(_T("CreateTime"),(variant_t)userInfo.strCreateTime);
//	WriteData(_T("AccessRight"),(variant_t)str_userLevel);
//
//	
//	return true;
//}
//增加数据文件信息
//bool CDataAccess::AddFormData_FileInfo(CString strPath,CString strFormName,ACSDFileMnger fileInfo)
//{
//	CString strTemp;
//
//	DataBaseInit(strPath);
//
//	CString SQL=_T("SELECT * FROM ")+strFormName;
//
//	if(!(OpenForm(SQL)))  //当前工作文档
//	{
//		CString Msg=_T("打开")+strFormName+_T("数据表失败！");
//		AfxMessageBox(Msg,MB_TOPMOST);
//		return false;
//	}
//
//	int i=0;
//	while(!m_pRecordset->adoEOF)//移动到最底
//	{
//		m_pRecordset->MoveNext();
//		i++;
//	}
//	m_pRecordset->AddNew();
//	WriteData(_T("ID"),(variant_t)i);
//	WriteData(_T("ParamDescription"),(variant_t)fileInfo.strParamDescription);
//	WriteData(_T("ParamValue"),(variant_t)fileInfo.strParamValue);
//
//	return true;
//}
//增加普通参数
//bool CDataAccess::AddFormData_ACSDData(CString strPath,CString strFormName,ACSDData smData)
//{
//	CString strTemp;
//
//	DataBaseInit(strPath);
//
//	CString SQL=_T("SELECT * FROM ")+strFormName;
//
//	if(!(OpenForm(SQL)))  //当前工作文档
//	{
//		CString Msg=_T("打开")+strFormName+_T("数据表失败！");
//		AfxMessageBox(Msg,MB_TOPMOST);
//		return false;
//	}
//
//	int i=0;
//	while(!m_pRecordset->adoEOF)//移动到最底
//	{
//		m_pRecordset->MoveNext();
//		i++;
//	}
//	m_pRecordset->AddNew();
//	WriteData(_T("ID"),(variant_t)i);
//	WriteData(_T("ParamDescription"),(variant_t)smData.strName);
//	WriteData(_T("ParamValue"),(variant_t)smData.dwValue);
//	WriteData(_T("ParamMax"),(variant_t)smData.dwMax);
//	WriteData(_T("ParamMin"),(variant_t)smData.dwMin);
//
//	return true;
//}
//增加普通坐标参数
//bool CDataAccess::AddFormData_ACSDPosData(CString strPath,CString strFormName,ACSDPosData smData)
//{
//	CString strTemp;
//
//	DataBaseInit(strPath);
//
//	CString SQL=_T("SELECT * FROM ")+strFormName;
//
//	if(!(OpenForm(SQL)))  //当前工作文档
//	{
//		CString Msg=_T("打开")+strFormName+_T("数据表失败！");
//		AfxMessageBox(Msg,MB_TOPMOST);
//		return false;
//	}
//
//	int i=0;
//	while(!m_pRecordset->adoEOF)//移动到最底
//	{
//		m_pRecordset->MoveNext();
//		i++;
//	}
//	m_pRecordset->AddNew();
//	WriteData(_T("ID"),(variant_t)i);
//	WriteData(_T("名称"),(variant_t)smData.strName);
//	WriteData(_T("X坐标"),(variant_t)smData.dwXValue);
//	WriteData(_T("Y坐标"),(variant_t)smData.dwYValue);
//
//	return true;
//}
//增加普通双坐标参数-yqh.2015.03.05
//bool CDataAccess::AddFormData_ACSDCamMotorData(CString strPath,CString strFormName,ACSDCamMotorData smData)
//{
//	CString strTemp;
//
//	DataBaseInit(strPath);
//
//	CString SQL=_T("SELECT * FROM ")+strFormName;
//
//	if(!(OpenForm(SQL)))  //当前工作文档
//	{
//		CString Msg=_T("打开")+strFormName+_T("数据表失败！");
//		AfxMessageBox(Msg,MB_TOPMOST);
//		return false;
//	}
//
//	int i=0;
//	while(!m_pRecordset->adoEOF)//移动到最底
//	{
//		m_pRecordset->MoveNext();
//		i++;
//	}
//	m_pRecordset->AddNew();
//	WriteData(_T("ID"),(variant_t)i);
//	WriteData(_T("X坐标"),(variant_t)smData.dwX);
//	WriteData(_T("Y坐标"),(variant_t)smData.dwY);
//	WriteData(_T("X脉冲值"),(variant_t)smData.dwXplus);
//	WriteData(_T("Y脉冲值"),(variant_t)smData.dwYplus);
//	WriteData(_T("名称"),(variant_t)smData.strName);
//	
//	return true;
//}
//增加用户管理信息
//bool CDataAccess::AddFormData_UserInfo1D(CString strPath,CString strFormName,ACSDUserInfo1D userInfo)
//{
//	CString strTemp;
//
//	DataBaseInit(strPath);
//
//	CString SQL=_T("SELECT * FROM ")+strFormName;
//	if(!(OpenForm(SQL)))  //当前工作文档
//	{
//		CString Msg=_T("打开")+strFormName+_T("数据表失败！");
//		AfxMessageBox(Msg,MB_TOPMOST);
//		return false;
//	}
//	int i=0;
//	while(!m_pRecordset->adoEOF)//移动到最底
//	{
//		m_pRecordset->MoveNext();
//		i++;
//	}
//	
//	for (size_t z=0;z<userInfo.size();z++)
//	{
//		m_pRecordset->AddNew();
//		CString  str_userLevel;
//		str_userLevel.Format(_T("%d"), userInfo[z].nUserLevel);
//		WriteData(_T("UsersName"),(variant_t)userInfo[z].strUserName);
//		WriteData(_T("PWD"),(variant_t)userInfo[z].strUserPwd);
//		WriteData(_T("CreateTime"),(variant_t)userInfo[z].strCreateTime);
//		WriteData(_T("AccessRight"),(variant_t)str_userLevel);
//	}
//	
//	return true;
//}
//增加数据文件信息
//bool CDataAccess::AddFormData_FileInfo1D(CString strPath,CString strFormName,ACSDFileMnger1D fileInfo)
//{
//	CString strTemp;
//
//	DataBaseInit(strPath);
//
//	CString SQL=_T("SELECT * FROM ")+strFormName;
//
//	if(!(OpenForm(SQL)))  //当前工作文档
//	{
//		CString Msg=_T("打开")+strFormName+_T("数据表失败！");
//		AfxMessageBox(Msg,MB_TOPMOST);
//		return false;
//	}
//
//	int i=0;
//	while(!m_pRecordset->adoEOF)//移动到最底
//	{
//		m_pRecordset->MoveNext();
//		i++;
//	}
//
//	for (size_t z=0;z<fileInfo.size();z++)
//	{
//		m_pRecordset->AddNew();
//		WriteData(_T("ID"),(variant_t)(i+z));
//		WriteData(_T("ParamDescription"),(variant_t)fileInfo[z].strParamDescription);
//		WriteData(_T("ParamValue"),(variant_t)fileInfo[z].strParamValue);
//	}
//	return true;
//}
//增加普通参数
//bool CDataAccess::AddFormData_ACSDData1D(CString strPath,CString strFormName,ACSDData1D smData)
//{
//	CString strTemp;
//
//	DataBaseInit(strPath);
//
//	CString SQL=_T("SELECT * FROM ")+strFormName;
//
//	if(!(OpenForm(SQL)))  //当前工作文档
//	{
//		CString Msg=_T("打开")+strFormName+_T("数据表失败！");
//		AfxMessageBox(Msg,MB_TOPMOST);
//		return false;
//	}
//
//	int i=0;
//	while(!m_pRecordset->adoEOF)//移动到最底
//	{
//		m_pRecordset->MoveNext();
//		i++;
//	}
//	for (size_t z=0;z<smData.size();z++)
//	{
//		m_pRecordset->AddNew();
//		WriteData(_T("ID"),(variant_t)(i+z));
//		WriteData(_T("ParamDescription"),(variant_t)smData[z].strName);
//		WriteData(_T("ParamValue"),(variant_t)smData[z].dwValue);
//		WriteData(_T("ParamMax"),(variant_t)smData[z].dwMax);
//		WriteData(_T("ParamMin"),(variant_t)smData[z].dwMin);
//	}
//	
//
//	return true;
//}
//增加普通坐标参数
//bool CDataAccess::AddFormData_ACSDPosData1D(CString strPath,CString strFormName,ACSDPosData1D smData)
//{
//	CString strTemp;
//
//	DataBaseInit(strPath);
//
//	CString SQL=_T("SELECT * FROM ")+strFormName;
//
//	if(!(OpenForm(SQL)))  //当前工作文档
//	{
//		CString Msg=_T("打开")+strFormName+_T("数据表失败！");
//		AfxMessageBox(Msg,MB_TOPMOST);
//		return false;
//	}
//
//	int i=0;
//	while(!m_pRecordset->adoEOF)//移动到最底
//	{
//		m_pRecordset->MoveNext();
//		i++;
//	}
//	for (size_t z=0;z<smData.size();z++)
//	{
//		m_pRecordset->AddNew();
//		WriteData(_T("ID"),(variant_t)(i+z));
//		WriteData(_T("名称"),(variant_t)smData[z].strName);
//		WriteData(_T("X坐标"),(variant_t)smData[z].dwXValue);
//		WriteData(_T("Y坐标"),(variant_t)smData[z].dwYValue);
//	}
//
//
//	return true;
//}
//增加普通双坐标参数-yqh.2015.03.05
//bool CDataAccess::AddFormData_ACSDCamMotorData1D(CString strPath,CString strFormName,ACSDCamMotorData1D smData)
//{
//	CString strTemp;
//
//	DataBaseInit(strPath);
//
//	CString SQL=_T("SELECT * FROM ")+strFormName;
//
//	if(!(OpenForm(SQL)))  //当前工作文档
//	{
//		CString Msg=_T("打开")+strFormName+_T("数据表失败！");
//		AfxMessageBox(Msg,MB_TOPMOST);
//		return false;
//	}
//
//	int i=0;
//	while(!m_pRecordset->adoEOF)//移动到最底
//	{
//		m_pRecordset->MoveNext();
//		i++;
//	}
//	for (size_t z=0;z<smData.size();z++)
//	{
//		m_pRecordset->AddNew();
//		WriteData(_T("ID"),(variant_t)(i+z));
//		WriteData(_T("X坐标"),(variant_t)smData[z].dwX);
//		WriteData(_T("Y坐标"),(variant_t)smData[z].dwY);
//		WriteData(_T("X脉冲值"),(variant_t)smData[z].dwXplus);
//		WriteData(_T("Y脉冲值"),(variant_t)smData[z].dwYplus);
//		WriteData(_T("名称"),(variant_t)smData[z].strName);
//	}
//	
//
//	return true;
//}
//存图片数据
//bool CDataAccess::ModifyFormData_ACSDImageData(CString strPath,CString strFormName,ACSDImageData smData,unsigned long nIndex)
//{
//#define  IMG_DEPTH 8
//#define  IMG_CHANNAL 1
//
//	DataBaseInit(strPath);
//	CString bStr;
//	//-------------------------------------
//	CString SQL=_T("SELECT * FROM ")+strFormName;
//	if(!(OpenForm(SQL)))  //当前工作文档
//	{
//		CString Msg=_T("打开")+strFormName+_T("数据表失败！");
//		AfxMessageBox(Msg,MB_TOPMOST);
//		return false;
//	}
//
//	CString bField=_T("宽");
//	bStr.Format(_T("%d"),smData.width);
//	_variant_t d_Data=(LPCTSTR)bStr; 
//	WriteDataEx((_variant_t)bField,d_Data,nIndex); //写入参数宽
//
//	bField=_T("高");
//	bStr.Format(_T("%d"),smData.height);
//	d_Data=(LPCTSTR)bStr; 
//	WriteDataEx((_variant_t)bField,d_Data,nIndex); //写入参数高
//
//	BYTE			*pBuf = smData.img;        //写入图像数据
//	VARIANT			varBLOB;
//	SAFEARRAY		*psa;
//	SAFEARRAYBOUND	rgsabound[1];
//
//	unsigned long widthstep=(smData.width*IMG_DEPTH/8+3)/4*4; //字节对齐
//	unsigned long lDataSize=widthstep*smData.height; //不能用img->width*img->height
//	if(pBuf)
//	{   
//		rgsabound[0].lLbound = 0;
//		rgsabound[0].cElements = lDataSize;
//		psa = SafeArrayCreate(VT_UI1, 1, rgsabound);
//		for (long i = 0; i < (long)lDataSize; i++)
//		{
//			SafeArrayPutElement (psa, &i, pBuf++);
//		}
//		varBLOB.vt = VT_ARRAY | VT_UI1;
//		varBLOB.parray = psa;
//
//		m_pRecordset->MoveFirst();  //移动到指定的行
//		for(unsigned int i = 0; i <nIndex;i++)
//		{
//			m_pRecordset->MoveNext();
//		}
//		m_pRecordset->GetFields()->GetItem(_T("数据"))->AppendChunk(varBLOB);
//		m_pRecordset->Update();
//	}
//
//	
//	return true;
//}
//增加IO参数
//bool CDataAccess::AddFormData_ACSDIOData1D(CString strPath,CString strFormName,ACSDIOData1D ioData1D)
//{
//	CString strTemp;
//
//	DataBaseInit(strPath);
//
//	CString SQL=_T("SELECT * FROM ")+strFormName;
//
//	if(!(OpenForm(SQL)))  //当前工作文档
//	{
//		CString Msg=_T("打开")+strFormName+_T("数据表失败！");
//		AfxMessageBox(Msg,MB_TOPMOST);
//		return false;
//	}
//
//	int i=0;
//	while(!m_pRecordset->adoEOF)//移动到最底
//	{
//		m_pRecordset->MoveNext();
//		i++;
//	}
//	for (size_t z=0;z<ioData1D.size();z++)
//	{
//		m_pRecordset->AddNew();
//		WriteData(_T("ID"),(variant_t)(i+z));
//		WriteData(_T("Discribe"),(variant_t)ioData1D[z].discribe);
//		WriteData(_T("SysXIndex"),(variant_t)ioData1D[z].sysIndex);
//		WriteData(_T("SysXBit"),(variant_t)ioData1D[z].sysBit);
//		WriteData(_T("DeviceID"),(variant_t)ioData1D[z].deviceID);
//		WriteData(_T("DevXIndex"),(variant_t)ioData1D[z].devIndex);
//		WriteData(_T("DevXBit"),(variant_t)ioData1D[z].devBit);
//		WriteData(_T("DeviceType"),(variant_t)ioData1D[z].deviceType);
//		WriteData(_T("DevXType"),(variant_t)ioData1D[z].devType);
//	}
//
//	return true;
//}
#pragma endregion