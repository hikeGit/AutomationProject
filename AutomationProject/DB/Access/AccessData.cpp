#include "stdafx.h"
#include "..\..\include\DB\AccessData.h"
/************************************************* 

*************************************************/ 


//��ʶOLE��ʼ��״̬���Է��ظ���ʼ��
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
*�� �� ����void CDataAccess::AccessInit(bool bPassWordUseOrNot)

*���������bool bPassWordUseOrNot  ����ʶOLE��ʼ��״̬���Է��ظ���ʼ��
           bPassWordUseOrNot==0����ʹ������
		   bPassWordUseOrNot==1��ʹ������

*�������ܣ����ݿ�OLE��ʼ��

*�� �� ֵ����
***************************************************************************************/
void CDataAccess::AccessInit(bool bPassWordUseOrNot)
{
	
	if(!ms_bInitState)
	{
		CoInitialize(NULL);
		if (!CoInitialize(NULL))                          
		{
			AfxMessageBox(_T("OLE��ʼ��ʧ�ܣ�"));
            return;
		}
		ms_bInitState = 1;
	}
	if(bPassWordUseOrNot)  //�ж����ݿ��Ƿ�ʹ�������
	{
		SetPassWordState(USEPASSWORD);

		SetPassWord(_T("orchidflower")); //���ݿ�����
	}
	else
	{
		SetPassWordState(NOTUSEPASSWORD);
	}
}
/***************************************************************************************
*�� �� ����CDataAccess::SetPassWordState(bool bNewState)

*���������bool bNewState ����ʹ�����
            bNewState==0��ûʹ������
			bNewState==1��ʹ������

*�������ܣ����ݿ�����ʹ��״̬

*�� �� ֵ����
***************************************************************************************/
void CDataAccess::SetPassWordState(bool bNewState)
{
	this->m_bPassWordEn = bNewState;
}
/***************************************************************************************
*�� �� ����CDataAccess::GetPassWordState(void)

*�����������

*�������ܣ���ȡ���ݿ�����ʹ��״̬

*�� �� ֵ������ʹ��״̬
***************************************************************************************/
bool CDataAccess::GetPassWordState(void)
{
	return m_bPassWordEn;
}
/***************************************************************************************
*�� �� ����CDataAccess::SetPassWord(CString PassWord)

*���������CString PassWord �����ݿ�����
          
*�������ܣ��������ݿ�����

*�� �� ֵ����
***************************************************************************************/
void CDataAccess::SetPassWord(CString PassWord)
{
	m_PassWord = PassWord;
}
/***************************************************************************************
*�� �� ����CDataAccess::GetPassWord(void)

*�����������
          
*�������ܣ���ȡ���ݿ�����

*�� �� ֵ����
***************************************************************************************/
CString CDataAccess::GetPassWord(void)
{
	return m_PassWord;
}

/***************************************************************************************
*�� �� ����bool CDataAccess::Connect2DataBase(CString Path)

*���������CString Path  �����ݿ�Ĵ��·��

*�������ܣ��������ݿ�

*�� �� ֵ��true�� ���ӳɹ�
           false������ʧ��
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
		/*CString Msg=(_T("���ݿ�����ʧ�ܣ�ȷ�����ݿ�")+Path+_T("�Ƿ����"));
		AfxMessageBox(Msg);*/
		return false;
	} 
	
	return true;
}

/***************************************************************************************
*�� �� ����bool CDataAccess::DisconnectDataBase(void)

*�����������

*�������ܣ�ȡ�����ݿ�����

*�� �� ֵ����
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
*�� �� ����bool CDataAccess::Connect2DataBase(CString Path)

*���������CString FormName  �����ݱ�����

*�������ܣ������ݱ�

*�� �� ֵ��true�� �򿪳ɹ�
           false����ʧ��
***************************************************************************************/
bool CDataAccess::OpenForm(CString strSQL)
{
	try
	{

		m_pRecordset.CreateInstance(__uuidof(Recordset));

		m_pRecordset->Open((_variant_t)(strSQL),   // ��ѯ�����ֶ�
							m_pConnection.GetInterfacePtr(),	 // ��ȡ��ӿ��IDispatchָ��
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
*�� �� ����bool CDataAccess::CreateForm(CString AccessPath,CString FormName)

*���������CString FormName  �����ݱ�����

*�������ܣ������ݱ�

*�� �� ֵ��true�� �򿪳ɹ�
           false����ʧ��
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
*�� �� ����WriteData(variant_t DataField,variant_t Content)

*���������variant_t DataField  ���ֶ�����
           variant_t Content��������ֶ�����

*�������ܣ�д�����ݿ����

*�� �� ֵ����
***************************************************************************************/
void CDataAccess::WriteData(variant_t DataField,variant_t Content)
{
  m_pRecordset->PutCollect(DataField,Content);
  m_pRecordset->Update();
}
/***************************************************************************************
*�� �� ����WriteDataEx(variant_t DataField,variant_t Content,int nRow)

*���������variant_t DataField  ���ֶ�����
           variant_t Content��������ֶ�����
		   int nRow ��ָ���ļ�¼��

*�������ܣ�ָ����֮������/�޸ļ�¼

*�� �� ֵ����
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
*�� �� ����CDataAccess::ReadData(variant_t Index)

*���������variant_t Index  ���ֶ�����

*�������ܣ���ȡ�ֶεļ�¼

*�� �� ֵ��true�� �ɹ�
           false��ʧ��
***************************************************************************************/
variant_t CDataAccess::ReadData(variant_t Index)
{
  return m_pRecordset->GetCollect(Index);
}
/***************************************************************************************
*�� �� ����CDataAccess::ReadDataEx(variant_t Index,int nRow)

*���������variant_t Index  ���ֶ�����
           int nRow ��ָ���ļ�¼��
           

*�������ܣ���ȡָ���ֶεļ�¼

*�� �� ֵ��true�� �ɹ�
           false��ʧ��
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
*�� �� ����CDataAccess::GetRowCount()

*�����������
           
*�������ܣ���ȡ�ֶμ�¼����

*�� �� ֵ���ֶμ�¼����
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

//����һ�����ݱ�
bool CDataAccess::CreatMehineForm(CString strPath,CString strFormName)
{
	return true;
}

//ɾ�����ݿ��ָ����
bool CDataAccess::DeleteFormData(CString strPath,CString strFormName,int nIndex)
{
	DataBaseInit(strPath); //�����ݿ�

	CString SQL=_T("SELECT * FROM ")+strFormName;
	if(!(OpenForm(SQL)))  //��ǰ�����ĵ�
	{
		CString Msg=_T("��")+strFormName+_T("���ݱ�ʧ�ܣ�");
		AfxMessageBox(Msg,MB_TOPMOST);
		return false;
	}

	if(!m_pRecordset->adoBOF)			//������ݿⲻΪ��
		m_pRecordset->MoveFirst();

	for(int i=0;!m_pRecordset->adoEOF; m_pRecordset->MoveNext()) //��������
	{
		if (i==nIndex)
		{
			m_pRecordset->Delete(adAffectCurrent);
		}
		i++;
	}
	
	return true;
}
//ɾ�����һ��
bool CDataAccess::DelFormDataEnd(CString strPath,CString strFormName)
{
	DataBaseInit(strPath); //�����ݿ�

	CString SQL=_T("SELECT * FROM ")+strFormName;
	if(!(OpenForm(SQL)))  //��ǰ�����ĵ�
	{
		CString Msg=_T("��")+strFormName+_T("���ݱ�ʧ�ܣ�");
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
//������ݿ��ָ�����ݱ������
bool CDataAccess::ClearMechineForm(CString strPath,CString strFormName)
{
	DataBaseInit(strPath); //�����ݿ�

	CString SQL=_T("SELECT * FROM ")+strFormName;
	if(!(OpenForm(SQL)))  //��ǰ�����ĵ�
	{
		CString Msg=_T("��")+strFormName+_T("���ݱ�ʧ�ܣ�");
		AfxMessageBox(Msg,MB_TOPMOST);
		return false;
	}

	if(!m_pRecordset->adoBOF)			//������ݿⲻΪ��
		m_pRecordset->MoveFirst();

	for(int i=0;!m_pRecordset->adoEOF; m_pRecordset->MoveNext()) //��������
	{
		m_pRecordset->Delete(adAffectCurrent);
	}
	
	return true;
}
//��ȡ����������
bool CDataAccess::GetFormRowSize(CString strPath,CString strFormName,unsigned long &nSize)
{
	CString strTemp;

	DataBaseInit(strPath);

	CString SQL=_T("SELECT * FROM ")+strFormName;
	if(!(OpenForm(SQL)))  //��ǰ�����ĵ�
	{
		CString Msg=_T("��")+strFormName+_T("���ݱ�ʧ�ܣ�");
		AfxMessageBox(Msg,MB_TOPMOST);
		return false;
	}
	nSize=0;
	for(;!m_pRecordset->adoEOF; m_pRecordset->MoveNext()) //��ȡ����·��
	{
		nSize=nSize+1;
	}

	return true;
}

bool CDataAccess::ReadFormData(CString strPath, CString strFormName, std::vector<CString> & vec, std::vector<std::map<CString,CString> > &resultData)
{
	DataBaseInit(strPath);

	CString SQL = _T("SELECT * FROM ") + strFormName;
	if (!(OpenForm(SQL)))  //��ǰ�����ĵ�
	{
		CString Msg = _T("��") + strFormName + _T("���ݱ�ʧ�ܣ�");
		AfxMessageBox(Msg, MB_TOPMOST);
		return false;
	}
	std::vector<std::map<CString,CString>> allData;
	std::map<CString,CString>  rowData;
	CString strCurReading = _T("NoReading");//��ǰ���ڶ����ֶΣ�������
	CString strTemp;
	int i = 0;

	try
	{
		if (m_pRecordset->GetFields()->Count <(long) vec.size())
		{
			throw std::exception("������ֶ����������ݿ�ʵ���ֶ���");
		}
		for (; !m_pRecordset->adoEOF; m_pRecordset->MoveNext()) //��ȡ����·��
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
		CString Msg = _T("��ȡ") + strFormName + _T("���ݱ�ʧ�ܣ�")+_T("��ǰ�ֶΣ�")+strCurReading +_T(" \n") + _T("�쳣Ϊ:") + erro;
		AfxMessageBox(Msg, MB_TOPMOST);
		return false;
	}
	catch (_com_error  e)
	{
		CString erro((LPCTSTR)e.Description());
		CString Msg = _T("��ȡ") + strFormName + _T("���ݱ�ʧ�ܣ�\n") + _T("�쳣Ϊ:") + erro ;
		AfxMessageBox(Msg, MB_TOPMOST);
		return false;
	}
	catch (...)
	{
		CString t;
		t.Format(_T("index = %d"), i);
		CString Msg = _T("��ȡ") + strFormName + _T("���ݱ�ʧ�ܣ�\n") + _T("δ֪�쳣��") + t + _T(":") + strCurReading;
		AfxMessageBox(Msg, MB_TOPMOST);
		return false;
	}
	return true;
}

//��ȡ���ݿ�
bool CDataAccess::ReadFormData(CString strPath,CString strFormName,CString strField,int nIndex,CString& strData)
{
	CString strTemp;

	DataBaseInit(strPath);

	CString SQL=_T("SELECT * FROM ")+strFormName;
	if(!(OpenForm(SQL)))  //��ǰ�����ĵ�
	{
		CString Msg=_T("��")+strFormName+_T("���ݱ�ʧ�ܣ�");
		AfxMessageBox(Msg,MB_TOPMOST);
		return false;
	}

	int temIndex=0;
	for(;!m_pRecordset->adoEOF; m_pRecordset->MoveNext()) //��ȡ����·��
	{
		if (temIndex==nIndex)
		{
			strData=m_pRecordset->GetCollect((const _variant_t)strField);
		}
		temIndex=temIndex+1;
	}


	return true;
}

//�޸����ݿ�
bool CDataAccess::ModifyFormData(CString strPath, CString strFormName, CString strField, CString strData, int nIndex)
{
	_variant_t d_Data = (LPCTSTR)strData;  //CString ת�������ݿ�Ĳ�������

	DataBaseInit(strPath);    //�����ݿ�

	CString SQL = _T("SELECT * FROM ") + strFormName;
	if (!(OpenForm(SQL)))  //��ǰ�����ĵ�
	{
		CString Msg = _T("��") + strFormName + _T("���ݱ�ʧ�ܣ�");
		AfxMessageBox(Msg, MB_TOPMOST);
		return false;
	}
	WriteDataEx((_variant_t)strField, d_Data, nIndex); //д�����
	return true;
}

//������������
//��Ҫ���Ƶĵط���һ���жϴ��������ֶ����Ƿ�С�����ݿ�����ֶ��������Ǵ������������Ƿ�С�����ݿ���������ǰ��ʱ���ݿ��Ѿ����ڣ�
bool  CDataAccess::SaveFormDataAll(CString strPath, CString strFormName, const std::vector<std::map<CString, CString>> &formdata_in)
{

	CString strCurReading = _T("NoReading");
	CString strCurRow = _T("-1");
	CString ErroMsg;
	//ֱ���ڱ��ϸ�(Modify)�����ڿ���дһ��ʾ�̵������������ô����ݿ⣬���Ǹ��������������Ϣ�Զ��������(add)
	try
	{
		DataBaseInit(strPath);
		CString SQL = _T("SELECT * FROM ") + strFormName;
		if (!(OpenForm(SQL)))  //��ǰ�����ĵ�
		{
			ErroMsg = _T("��") + strFormName + _T("���ݱ�ʧ�ܣ�");
			throw std::exception((LPCSTR)(LPSTR)ErroMsg.GetBuffer());
		}

		int num = formdata_in[0].size();//���ݽ�����map���������ֶ���Ϣ��
		std::map<CString, CString> inmap = formdata_in[0];//��ȡ���ݽ�����map�ֶ���
		//�ж��쳣��Ϣ
		if (m_pRecordset->GetFields()->Count < num)
		{
			throw std::exception(("������ֶ����������ݱ�ʵ���ֶ���"));
		}
		unsigned long tempcount = 0;
		GetFormRowSize(strPath, strFormName, tempcount);
		if (tempcount< formdata_in.size())
		{
			throw std::exception("��Ҫ��������������������ݱ��д��ڵ���������");
		}

		//�������ݿ�
		int mapindex = 0;
		for (; !m_pRecordset->adoEOF; m_pRecordset->MoveNext()) //һ������
		{
			for (auto item : formdata_in[mapindex])//ĳһ���ֶ����ݸ���
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
		CString Msg = _T("����") + strFormName + _T("���ݱ�ʧ�ܣ�\n") + _T("��ǰ������") + strCurRow + _T("  ��ǰ�ֶΣ�") + strCurReading + _T("\n�쳣Ϊ:") + erro;
		AfxMessageBox(Msg, MB_TOPMOST);
		return false;
	}
	catch (std::exception e)
	{
		CString erro(e.what());
		CString Msg = _T("����") + strFormName + _T("���ݱ�ʧ�ܣ�") + _T("��ǰ������") + strCurRow + _T("  ��ǰ�ֶΣ�") + strCurReading + _T(" \n") + _T("\n�쳣Ϊ:") + erro;
		AfxMessageBox(Msg, MB_TOPMOST);
		return false;
	}
	catch (...)
	{
		CString Msg = _T("��ȡ") + strFormName + _T("���ݱ�ʧ�ܣ�\n") + _T("δ֪�쳣��") + _T("��ǰ������") + strCurRow + _T("  ��ǰ�ֶΣ�") + strCurReading;
		AfxMessageBox(Msg, MB_TOPMOST);
		return false;
	}
	return true;

}
//�����ض�������
bool CDataAccess::SaveFormData(CString strPath, CString strFormName, const std::map<CString,CString> &savekeys, const std::map<CString, CString> & savedata)
{
	CString strCurReading = _T("NoReading");
	CString strCurRow = _T("-1");
	CString ErroMsg;
	//ֱ���ڱ��ϸ�(Modify)�����ڿ���дһ��ʾ�̵������������ô����ݿ⣬���Ǹ��������������Ϣ�Զ��������(add)
	try
	{
		DataBaseInit(strPath);
		CString SQL = _T("SELECT * FROM ") + strFormName;
		if (!(OpenForm(SQL)))  //��ǰ�����ĵ�
		{
			ErroMsg = _T("��") + strFormName + _T("���ݱ�ʧ�ܣ�");
			throw std::exception((LPCSTR)(LPSTR)ErroMsg.GetBuffer());
		}

		//�������ݿ�
		int mapindex = 0;
		for (; !m_pRecordset->adoEOF; m_pRecordset->MoveNext()) //һ������
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
				throw std::exception("����ʱ��Ҫ���ҡ��ȶԹؼ���ʧ��");				
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
		CString Msg = _T("����") + strFormName + _T("���ݱ�ʧ�ܣ�\n") + _T("��ǰ������") + strCurRow + _T("  ��ǰ�ֶΣ�") + strCurReading + _T("\n�쳣Ϊ:") + erro;
		AfxMessageBox(Msg, MB_TOPMOST);
		return false;
	}
	catch (std::exception e)
	{
		CString erro(e.what());
		CString Msg = _T("����") + strFormName + _T("���ݱ�ʧ�ܣ�") + _T("��ǰ������") + strCurRow + _T("  ��ǰ�ֶΣ�") + strCurReading + _T(" \n") + _T("\n�쳣Ϊ:") + erro;
		AfxMessageBox(Msg, MB_TOPMOST);
		return false;
	}
	catch (...)
	{
		CString Msg = _T("��ȡ") + strFormName + _T("���ݱ�ʧ�ܣ�\n") + _T("δ֪�쳣��") + _T("��ǰ������") + strCurRow + _T("  ��ǰ�ֶΣ�") + strCurReading;
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


#pragma region ɾ��
//�����û�������Ϣ
//bool CDataAccess::AddFormData_UserInfo(CString strPath,CString strFormName,ACSDUserInfo userInfo)
//{
//	CString strTemp;
//
//	DataBaseInit(strPath);
//
//	CString SQL=_T("SELECT * FROM ")+strFormName;
//	if(!(OpenForm(SQL)))  //��ǰ�����ĵ�
//	{
//		CString Msg=_T("��")+strFormName+_T("���ݱ�ʧ�ܣ�");
//		AfxMessageBox(Msg,MB_TOPMOST);
//		return false;
//	}
//	int i=0;
//	while(!m_pRecordset->adoEOF)//�ƶ������
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
//���������ļ���Ϣ
//bool CDataAccess::AddFormData_FileInfo(CString strPath,CString strFormName,ACSDFileMnger fileInfo)
//{
//	CString strTemp;
//
//	DataBaseInit(strPath);
//
//	CString SQL=_T("SELECT * FROM ")+strFormName;
//
//	if(!(OpenForm(SQL)))  //��ǰ�����ĵ�
//	{
//		CString Msg=_T("��")+strFormName+_T("���ݱ�ʧ�ܣ�");
//		AfxMessageBox(Msg,MB_TOPMOST);
//		return false;
//	}
//
//	int i=0;
//	while(!m_pRecordset->adoEOF)//�ƶ������
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
//������ͨ����
//bool CDataAccess::AddFormData_ACSDData(CString strPath,CString strFormName,ACSDData smData)
//{
//	CString strTemp;
//
//	DataBaseInit(strPath);
//
//	CString SQL=_T("SELECT * FROM ")+strFormName;
//
//	if(!(OpenForm(SQL)))  //��ǰ�����ĵ�
//	{
//		CString Msg=_T("��")+strFormName+_T("���ݱ�ʧ�ܣ�");
//		AfxMessageBox(Msg,MB_TOPMOST);
//		return false;
//	}
//
//	int i=0;
//	while(!m_pRecordset->adoEOF)//�ƶ������
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
//������ͨ�������
//bool CDataAccess::AddFormData_ACSDPosData(CString strPath,CString strFormName,ACSDPosData smData)
//{
//	CString strTemp;
//
//	DataBaseInit(strPath);
//
//	CString SQL=_T("SELECT * FROM ")+strFormName;
//
//	if(!(OpenForm(SQL)))  //��ǰ�����ĵ�
//	{
//		CString Msg=_T("��")+strFormName+_T("���ݱ�ʧ�ܣ�");
//		AfxMessageBox(Msg,MB_TOPMOST);
//		return false;
//	}
//
//	int i=0;
//	while(!m_pRecordset->adoEOF)//�ƶ������
//	{
//		m_pRecordset->MoveNext();
//		i++;
//	}
//	m_pRecordset->AddNew();
//	WriteData(_T("ID"),(variant_t)i);
//	WriteData(_T("����"),(variant_t)smData.strName);
//	WriteData(_T("X����"),(variant_t)smData.dwXValue);
//	WriteData(_T("Y����"),(variant_t)smData.dwYValue);
//
//	return true;
//}
//������ͨ˫�������-yqh.2015.03.05
//bool CDataAccess::AddFormData_ACSDCamMotorData(CString strPath,CString strFormName,ACSDCamMotorData smData)
//{
//	CString strTemp;
//
//	DataBaseInit(strPath);
//
//	CString SQL=_T("SELECT * FROM ")+strFormName;
//
//	if(!(OpenForm(SQL)))  //��ǰ�����ĵ�
//	{
//		CString Msg=_T("��")+strFormName+_T("���ݱ�ʧ�ܣ�");
//		AfxMessageBox(Msg,MB_TOPMOST);
//		return false;
//	}
//
//	int i=0;
//	while(!m_pRecordset->adoEOF)//�ƶ������
//	{
//		m_pRecordset->MoveNext();
//		i++;
//	}
//	m_pRecordset->AddNew();
//	WriteData(_T("ID"),(variant_t)i);
//	WriteData(_T("X����"),(variant_t)smData.dwX);
//	WriteData(_T("Y����"),(variant_t)smData.dwY);
//	WriteData(_T("X����ֵ"),(variant_t)smData.dwXplus);
//	WriteData(_T("Y����ֵ"),(variant_t)smData.dwYplus);
//	WriteData(_T("����"),(variant_t)smData.strName);
//	
//	return true;
//}
//�����û�������Ϣ
//bool CDataAccess::AddFormData_UserInfo1D(CString strPath,CString strFormName,ACSDUserInfo1D userInfo)
//{
//	CString strTemp;
//
//	DataBaseInit(strPath);
//
//	CString SQL=_T("SELECT * FROM ")+strFormName;
//	if(!(OpenForm(SQL)))  //��ǰ�����ĵ�
//	{
//		CString Msg=_T("��")+strFormName+_T("���ݱ�ʧ�ܣ�");
//		AfxMessageBox(Msg,MB_TOPMOST);
//		return false;
//	}
//	int i=0;
//	while(!m_pRecordset->adoEOF)//�ƶ������
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
//���������ļ���Ϣ
//bool CDataAccess::AddFormData_FileInfo1D(CString strPath,CString strFormName,ACSDFileMnger1D fileInfo)
//{
//	CString strTemp;
//
//	DataBaseInit(strPath);
//
//	CString SQL=_T("SELECT * FROM ")+strFormName;
//
//	if(!(OpenForm(SQL)))  //��ǰ�����ĵ�
//	{
//		CString Msg=_T("��")+strFormName+_T("���ݱ�ʧ�ܣ�");
//		AfxMessageBox(Msg,MB_TOPMOST);
//		return false;
//	}
//
//	int i=0;
//	while(!m_pRecordset->adoEOF)//�ƶ������
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
//������ͨ����
//bool CDataAccess::AddFormData_ACSDData1D(CString strPath,CString strFormName,ACSDData1D smData)
//{
//	CString strTemp;
//
//	DataBaseInit(strPath);
//
//	CString SQL=_T("SELECT * FROM ")+strFormName;
//
//	if(!(OpenForm(SQL)))  //��ǰ�����ĵ�
//	{
//		CString Msg=_T("��")+strFormName+_T("���ݱ�ʧ�ܣ�");
//		AfxMessageBox(Msg,MB_TOPMOST);
//		return false;
//	}
//
//	int i=0;
//	while(!m_pRecordset->adoEOF)//�ƶ������
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
//������ͨ�������
//bool CDataAccess::AddFormData_ACSDPosData1D(CString strPath,CString strFormName,ACSDPosData1D smData)
//{
//	CString strTemp;
//
//	DataBaseInit(strPath);
//
//	CString SQL=_T("SELECT * FROM ")+strFormName;
//
//	if(!(OpenForm(SQL)))  //��ǰ�����ĵ�
//	{
//		CString Msg=_T("��")+strFormName+_T("���ݱ�ʧ�ܣ�");
//		AfxMessageBox(Msg,MB_TOPMOST);
//		return false;
//	}
//
//	int i=0;
//	while(!m_pRecordset->adoEOF)//�ƶ������
//	{
//		m_pRecordset->MoveNext();
//		i++;
//	}
//	for (size_t z=0;z<smData.size();z++)
//	{
//		m_pRecordset->AddNew();
//		WriteData(_T("ID"),(variant_t)(i+z));
//		WriteData(_T("����"),(variant_t)smData[z].strName);
//		WriteData(_T("X����"),(variant_t)smData[z].dwXValue);
//		WriteData(_T("Y����"),(variant_t)smData[z].dwYValue);
//	}
//
//
//	return true;
//}
//������ͨ˫�������-yqh.2015.03.05
//bool CDataAccess::AddFormData_ACSDCamMotorData1D(CString strPath,CString strFormName,ACSDCamMotorData1D smData)
//{
//	CString strTemp;
//
//	DataBaseInit(strPath);
//
//	CString SQL=_T("SELECT * FROM ")+strFormName;
//
//	if(!(OpenForm(SQL)))  //��ǰ�����ĵ�
//	{
//		CString Msg=_T("��")+strFormName+_T("���ݱ�ʧ�ܣ�");
//		AfxMessageBox(Msg,MB_TOPMOST);
//		return false;
//	}
//
//	int i=0;
//	while(!m_pRecordset->adoEOF)//�ƶ������
//	{
//		m_pRecordset->MoveNext();
//		i++;
//	}
//	for (size_t z=0;z<smData.size();z++)
//	{
//		m_pRecordset->AddNew();
//		WriteData(_T("ID"),(variant_t)(i+z));
//		WriteData(_T("X����"),(variant_t)smData[z].dwX);
//		WriteData(_T("Y����"),(variant_t)smData[z].dwY);
//		WriteData(_T("X����ֵ"),(variant_t)smData[z].dwXplus);
//		WriteData(_T("Y����ֵ"),(variant_t)smData[z].dwYplus);
//		WriteData(_T("����"),(variant_t)smData[z].strName);
//	}
//	
//
//	return true;
//}
//��ͼƬ����
//bool CDataAccess::ModifyFormData_ACSDImageData(CString strPath,CString strFormName,ACSDImageData smData,unsigned long nIndex)
//{
//#define  IMG_DEPTH 8
//#define  IMG_CHANNAL 1
//
//	DataBaseInit(strPath);
//	CString bStr;
//	//-------------------------------------
//	CString SQL=_T("SELECT * FROM ")+strFormName;
//	if(!(OpenForm(SQL)))  //��ǰ�����ĵ�
//	{
//		CString Msg=_T("��")+strFormName+_T("���ݱ�ʧ�ܣ�");
//		AfxMessageBox(Msg,MB_TOPMOST);
//		return false;
//	}
//
//	CString bField=_T("��");
//	bStr.Format(_T("%d"),smData.width);
//	_variant_t d_Data=(LPCTSTR)bStr; 
//	WriteDataEx((_variant_t)bField,d_Data,nIndex); //д�������
//
//	bField=_T("��");
//	bStr.Format(_T("%d"),smData.height);
//	d_Data=(LPCTSTR)bStr; 
//	WriteDataEx((_variant_t)bField,d_Data,nIndex); //д�������
//
//	BYTE			*pBuf = smData.img;        //д��ͼ������
//	VARIANT			varBLOB;
//	SAFEARRAY		*psa;
//	SAFEARRAYBOUND	rgsabound[1];
//
//	unsigned long widthstep=(smData.width*IMG_DEPTH/8+3)/4*4; //�ֽڶ���
//	unsigned long lDataSize=widthstep*smData.height; //������img->width*img->height
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
//		m_pRecordset->MoveFirst();  //�ƶ���ָ������
//		for(unsigned int i = 0; i <nIndex;i++)
//		{
//			m_pRecordset->MoveNext();
//		}
//		m_pRecordset->GetFields()->GetItem(_T("����"))->AppendChunk(varBLOB);
//		m_pRecordset->Update();
//	}
//
//	
//	return true;
//}
//����IO����
//bool CDataAccess::AddFormData_ACSDIOData1D(CString strPath,CString strFormName,ACSDIOData1D ioData1D)
//{
//	CString strTemp;
//
//	DataBaseInit(strPath);
//
//	CString SQL=_T("SELECT * FROM ")+strFormName;
//
//	if(!(OpenForm(SQL)))  //��ǰ�����ĵ�
//	{
//		CString Msg=_T("��")+strFormName+_T("���ݱ�ʧ�ܣ�");
//		AfxMessageBox(Msg,MB_TOPMOST);
//		return false;
//	}
//
//	int i=0;
//	while(!m_pRecordset->adoEOF)//�ƶ������
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