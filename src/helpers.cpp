#include <cstdarg>
#include <stdio.h>
#include <string>
#include <cassert>

#include "helpers.h"

void _Log(const char* prefix, const char* fmt, va_list args)
{
	char buf[512];
	strcpy(buf, prefix);
	vsprintf(&buf[strlen(buf)], fmt, args);
	printf(buf);
}

void DebugLog(const char* fmt, ...)
{
#ifdef _DEBUG
	va_list args;
	va_start(args, fmt);
	_Log("[DEBUG] ", fmt, args);
	va_end(args);
#endif
}

void WarningLog(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	_Log("[WARNING] ", fmt, args);
	va_end(args);
}

void ErrorLog(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	_Log("[ERROR] ", fmt, args);
	va_end(args);
}

void Log(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	_Log("", fmt, args);
	va_end(args);
}