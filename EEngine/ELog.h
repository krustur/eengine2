#pragma once

#include <windows.h>
#include <stdio.h>

class ELog
{
public:
	ELog();
	~ELog();

	static void LogHResult(HRESULT hresult);
	void Log(char *string);
private:
	FILE *_stream;
};

