#pragma once

#include <windows.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

namespace EEngine
{
	struct Logger
	{
	public:
		Logger::Logger(LPTSTR name);
		~Logger();

		template <typename T> friend Logger& operator<<(Logger& logger, const T& t)
		{
			logger.formatStream << t;
			return logger;
		}

		friend Logger& operator<<(Logger& logger, std::ostringstream& (*pf)(std::ostringstream&))
		{
			logger.formatStream << pf;
			return logger;
		}

		void LogHResult(HRESULT hresult);
		void Log(const char *string);
		void Log(LPTSTR string);
		void LogLine(const char *string);
		void LogLine(LPTSTR string);
		void FormatLine(Logger &logger);

	private:
		void LogHeader();

		std::string GetDateTimeString();

		void StaticInitialization();
		static FILE *_stream;
		LPTSTR _name;

		std::ostringstream formatStream;
	};
}