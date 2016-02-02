#pragma once

#include <windows.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

namespace EEngine
{
	struct ELog
	{
	public:
		ELog::ELog(LPTSTR name);
		~ELog();

		template <typename T> friend ELog& operator<<(ELog& eLog, const T& t)
		{
			eLog.formatStream << t;
			return eLog;
		}

		friend ELog& operator<<(ELog& eLog, std::ostringstream& (*pf)(std::ostringstream&))
		{
			eLog.formatStream << pf;
			return eLog;
		}

		void LogHResult(HRESULT hresult);
		void Log(const char *string);
		void Log(LPTSTR string);
		void LogLine(const char *string);
		void LogLine(LPTSTR string);
		void FormatLine(ELog &eLog);

	private:
		void LogHeader();

		std::string GetDateTimeString();

		void StaticInitialization();
		static FILE *_stream;
		LPTSTR _name;

		std::ostringstream formatStream;
	};
}