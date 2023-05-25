#pragma once
#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>

#define _W(x)  __W(x)
#define __W(x)  L##x

#define VA_PRINTS(s) {				\
		va_list argp;				\
		va_start(argp, fmt);		\
		vswprintf_s(s, fmt, argp);	\
		va_end(argp);				\
}

void DebugOut(const wchar_t* fmt, ...);

void DebugOutTitle(const wchar_t* fmt, ...);

void SetDebugWindow(HWND hwnd);

#endif // !_DEBUG_H_