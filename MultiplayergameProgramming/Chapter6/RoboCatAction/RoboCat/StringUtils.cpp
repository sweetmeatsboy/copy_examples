#include "stdafx.h"

#if !_WIN32
extern const char** __argv;
extern int __argc;
void OutputDebugString(const char* inString)
{
	printf("%s", inString);
}
#endif

string StringUtils::GetCommandLineArg(int _idx)
{
	if (_idx < __argc)
		return string(__argv[_idx]);
	return string();
}

string StringUtils::Sprintf(const char* _format, ...)
{
	static char temp[4096];
	va_list args;
	va_start(args, _format);
#if _WIN32
	_vsnprintf_s(temp, 4096, 4096, _format, args);
#else
	vsnprintf(temp, 4096, inFormat, args);
#endif
	return string(temp);
}

 void StringUtils::Log( const char* inFormat )
 {
 	OutputDebugString( inFormat );
 	OutputDebugString( "\n" );
 }

 void StringUtils::Log(const char* _format, ...)
 {
	 static char temp[4096];
	 va_list args;
	 va_start(args, _format);

#if _WIN32
	 _vsnprintf_s(temp, 4096, 4096, _format, args);
#else
	 vsnprintf(temp, 4096, _format, args);
#endif // _WIN32
	 OutputDebugString(temp);
	 OutputDebugString("\n");
 }
