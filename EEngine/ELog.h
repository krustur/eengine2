#pragma once

#include <windows.h>

class ELog
{
public:
	ELog();
	~ELog();

	static void LogErrorHresult(HRESULT hresult);
};

