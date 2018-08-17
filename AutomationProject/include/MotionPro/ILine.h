#pragma once
#include <afx.h>
#include <list>
#include <functional>
 typedef struct  tagLineConfig
{
public:
	CString Name;

	CString DisplayName;

	CString CardName;

	unsigned short Index;

	bool Reversed;

	int CardID;
	int CardPort;


 }LineConfig;
	
 class ILine
 {
 public:
	 ILine(LineConfig config) :m_LineConfig(config)
	 {

	 }
	 ILine()
	 {
		 MessageBox(NULL, _T("ILine����Ĭ�Ϲ��캯����������"), _T("�쳣"), MB_TOPMOST);
	 }

 public:
	 bool m_bInExtendCard;

 public:
	 LineConfig m_LineConfig;
	 bool  m_bState;
	 std::list<std::function<void()>> TransitionList;

 protected:
	  void  SetState(bool  state)
	  { 
		  if (m_LineConfig.Reversed)
		  {
			  m_bState = !state;
		  }
		  bool pre = m_bState;
		  m_bState = state;
		  if (pre != m_bState)
		  {
			  for (auto item : TransitionList)
			  {
				  item();
			  }
		  }
	  };
 public:
	  bool GetState() { return m_bState; };

 };

 class IInputLine : public ILine
 {
 public:
	 IInputLine(LineConfig config) :ILine(config)
	 {

	 }
	 IInputLine()
	 {
		// AfxMessageBox(_T("IInputLine����Ĭ�Ϲ��캯����������"), MB_TOPMOST);
		 MessageBox(NULL, _T("IInputLine����Ĭ�Ϲ��캯����������"), _T("�쳣"), MB_TOPMOST);
	 }
	 virtual ~IInputLine() {};
 };

 class IOutputLine : public ILine
 {
 public:
	 IOutputLine(LineConfig config) :ILine(config)
	 {

	 }
	 IOutputLine()
	 {
		 //AfxMessageBox(_T("IOutputLine����Ĭ�Ϲ��캯����������"), MB_TOPMOST);
		 MessageBox(NULL, _T("IOutputLine����Ĭ�Ϲ��캯����������"), _T("�쳣"), MB_TOPMOST);

	 }
 public:
	 virtual ~IOutputLine() {};


 public:
	 virtual void WriteState(bool state)  = 0;
	 virtual void PWM(unsigned int frequency, unsigned int cycles)  = 0;


 };