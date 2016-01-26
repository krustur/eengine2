#pragma once

#include <windows.h>

class ELog
{
public:
	ELog();
	~ELog();

	static void LogHResult(HRESULT hresult);
	void Log(char *string);
};

