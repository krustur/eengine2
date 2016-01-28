#include <iostream>
#include <stdio.h>

#include "ELog.h"

ELog::ELog() :
	_stream(nullptr)
{
	freopen_s(&_stream, "EEngine.log", "w", stdout);
	std::cout << "EEngine log start" << std::endl;
}


ELog::~ELog()
{
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
		std::cout << "ERROR: " << errorText << std::endl;

		// release memory allocated by FormatMessage()
		LocalFree(errorText);
		errorText = NULL;
	}
}

void ELog::Log(char *string)
{
	printf(string);
	std::cout << string << std::endl;
}