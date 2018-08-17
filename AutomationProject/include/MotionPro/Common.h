#pragma once
#include <afx.h>
#include <memory>

#ifdef  _COMMON_FUNCTION_DLL
#define COMMON_FUNCTION __declspec(dllexport)
#else
#define COMMON_FUNCTION __declspec(dllimport)
#endif


COMMON_FUNCTION CString GetExeDirectory();

COMMON_FUNCTION std::unique_ptr<char[]> CStringToCharIndicator(CString strtemp);

COMMON_FUNCTION CString  SetIntToCString(int value);
COMMON_FUNCTION CString  SetDoubleToCString(double value);

COMMON_FUNCTION CString  SetCurrentTimeToCString();

