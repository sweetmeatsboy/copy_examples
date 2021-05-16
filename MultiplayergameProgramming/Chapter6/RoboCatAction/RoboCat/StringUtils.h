#pragma once


namespace StringUtils
{
	string GetCommandLineArg(int _idx);

	string Sprint(const char* _format, ...);

	void Log(const char* _format);
	void Log(const char* _format, ...);
}

#define LOG(...) StringUtils::Log(__VA_ARGS__);