#pragma once
#include "Machine.h"
//using namespace System;
//using namespace System::Collections::Generic;
//using namespace System::Runtime::InteropServices;

namespace Machine_CLR
{
	 public ref class TeachSet_CS
	 {
	 public:
		 TeachSet_CS() 
		 {
			 m_pTeachSet = &Machine::GetInstance()->m_TeachSetting;		 
		 };

	 public:
		 CTeachSetting  *  m_pTeachSet;
	 };
}

