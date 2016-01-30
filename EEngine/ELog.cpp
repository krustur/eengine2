#include <ctime>
#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <chrono>
#include <sstream>
#include <string>

#include "ELog.h"

FILE *ELog::_stream;

ELog::ELog(LPTSTR name) :
	_name(name)
{
	StaticInitialization();
}


ELog::~ELog()
{
}

void ELog::StaticInitialization()
{
	static bool isStaticInitialized = false;
	if (isStaticInitialized)
	{ 
		return;
	}
	freopen_s(&_stream, "EEngine.log", "w", stdout);
	std::cout << "EEngine log start" << std::endl;
	isStaticInitialized = true;
}

void ELog::LogHResult(HRESULT hresult)
{
	LPTSTR errorText = NULL;

	FormatMessage(
		// use system message tables to retrieve error text
		FORMAT_MESSAGE_FROM_SYSTEM
		// allocate buffer on local heap for error text
		| FORMAT_MESSAGE_ALLOCATE_BUFFER
		// Important! will fail otherwise, since we're not 
		// (and CANNOT) pass insertion parameters
		| FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,    // unused with FORMAT_MESSAGE_FROM_SYSTEM
		hresult,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&errorText,  // output 
		0, // minimum size for output buffer
		NULL);   // arguments - see note 

	if (NULL != errorText)
	{		
		LogLine(errorText);

		// release memory allocated by FormatMessage()
		LocalFree(errorText);
		errorText = NULL;
	}
}

void ELog::Log(char *string)
{
	std::cout << string;
}

void ELog::Log(LPTSTR string)
{
	std::wcout << string;
}

void ELog::LogLine(char *string)
{
	LogHeader();	
	std::cout << string << std::endl;
}

void ELog::LogLine(LPTSTR string)
{
	LogHeader();
	std::wcout << string << std::endl;
}

void ELog::LogHeader()
{
	std::cout << GetDateTimeString().c_str();
	std::wcout << L" [" << _name << L"] ";
}

std::string ELog::GetDateTimeString()
{
	auto now = std::chrono::system_clock::now();
	auto nowTime = std::chrono::system_clock::to_time_t(now);

	std::stringstream stringStream;
	stringStream << std::put_time(std::localtime(&nowTime), "%Y-%m-%d %X");

	auto duration = now.time_since_epoch();
	auto micros = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
	micros = micros % 1000000;
	stringStream << ":" << std::setw(6) << std::setfill('0') << micros << " ";

	return stringStream.str();
}
