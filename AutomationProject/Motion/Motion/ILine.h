#pragma once
#include <afx.h>
 class  ILine
{
	CString Name;

	CString DisplayName;

	unsigned short Port;

	unsigned short Index;

	unsigned short Card;

	CString CardType;

	bool Reversed;

	virtual void SetState(bool state) = 0;
 };