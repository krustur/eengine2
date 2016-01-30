#pragma once

#include <windows.h>
#include <stdio.h>
#include <string>

class ELog
{
public:
	ELog(LPTSTR name);
	~ELog();

	void LogHResult(HRESULT hresult);
	void Log(char *string);
	void Log(LPTSTR string);
	void LogLine(char *string);
	void LogLine(LPTSTR string);
private:
	void LogHeader();

	std::string GetDateTimeString();

	void StaticInitialization();
	static FILE *_stream;
	LPTSTR _name;
};

