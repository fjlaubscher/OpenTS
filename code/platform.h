/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#pragma once

#include <cstddef>
#include <cstdint>

#if defined(__APPLE__)
#include <objc/objc.h>
#else
using BOOL = int;
#endif

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

// Widths match the Windows x64 build, where long is 32 bits.
using BYTE = std::uint8_t;
using WORD = std::uint16_t;
using DWORD = std::uint32_t;
using COLORREF = DWORD;
using LONG = std::int32_t;
using ULONG = std::uint32_t;
using LONGLONG = std::int64_t;
using ULONGLONG = std::uint64_t;
using INT = int;
using UINT = unsigned int;
using SHORT = std::int16_t;
using USHORT = std::uint16_t;
using HRESULT = std::int32_t;
using LRESULT = std::intptr_t;
using LPARAM = std::intptr_t;
using WPARAM = std::uintptr_t;
using INT_PTR = std::intptr_t;
using UINT_PTR = std::uintptr_t;
using LONG_PTR = std::intptr_t;
using ULONG_PTR = std::uintptr_t;
using DWORD_PTR = std::uintptr_t;
using SIZE_T = std::size_t;

using HANDLE = void *;
using HWND = void *;
using HINSTANCE = void *;
using HMODULE = void *;
using HICON = void *;
using HCURSOR = void *;
using HBRUSH = void *;
using HMENU = void *;
using HDC = void *;
using HFONT = void *;
using HBITMAP = void *;
using HGDIOBJ = void *;
using HKL = void *;
using HRGN = void *;
using HPEN = void *;
using HKEY = void *;

using LPVOID = void *;
using LPCVOID = void const *;
using LPSTR = char *;
using LPCSTR = char const *;
using LPWSTR = wchar_t *;
using LPCWSTR = wchar_t const *;
using LPBYTE = BYTE *;
using LPDWORD = DWORD *;

struct POINT
{
	LONG x;
	LONG y;
};

struct RECT
{
	LONG left;
	LONG top;
	LONG right;
	LONG bottom;
};

struct SIZE
{
	LONG cx;
	LONG cy;
};

struct FILETIME
{
	DWORD dwLowDateTime;
	DWORD dwHighDateTime;
};

#ifndef MAX_PATH
#define MAX_PATH 260
#endif

#define IDOK 1
#define IDCANCEL 2
#define IDABORT 3
#define IDRETRY 4
#define IDIGNORE 5
#define IDYES 6
#define IDNO 7

#define FILE_ATTRIBUTE_READONLY 0x00000001
#define FILE_ATTRIBUTE_HIDDEN 0x00000002
#define FILE_ATTRIBUTE_SYSTEM 0x00000004
#define FILE_ATTRIBUTE_DIRECTORY 0x00000010
#define FILE_ATTRIBUTE_ARCHIVE 0x00000020
#define FILE_ATTRIBUTE_NORMAL 0x00000080
#define FILE_ATTRIBUTE_TEMPORARY 0x00000100
#define INVALID_FILE_ATTRIBUTES ((DWORD)-1)
#define INVALID_HANDLE_VALUE ((HANDLE)(intptr_t)-1)

#define LOWORD(value) ((WORD)((DWORD_PTR)(value) & 0xFFFF))
#define HIWORD(value) ((WORD)(((DWORD_PTR)(value) >> 16) & 0xFFFF))
#define RGB(red, green, blue) ((DWORD)(((BYTE)(red)) | ((WORD)((BYTE)(green)) << 8) | ((DWORD)((BYTE)(blue)) << 16)))

#define VK_SHIFT 0x10
#define VK_CONTROL 0x11
#define VK_MENU 0x12
#define VK_LSHIFT 0xA0
#define VK_RSHIFT 0xA1
#define VK_LCONTROL 0xA2
#define VK_RCONTROL 0xA3
#define VK_LMENU 0xA4
#define VK_RMENU 0xA5

#define CALLBACK
#define WINAPI
#define APIENTRY

struct WIN32_FIND_DATAA
{
	DWORD dwFileAttributes;
	FILETIME ftCreationTime;
	FILETIME ftLastAccessTime;
	FILETIME ftLastWriteTime;
	DWORD nFileSizeHigh;
	DWORD nFileSizeLow;
	DWORD dwReserved0;
	DWORD dwReserved1;
	char cFileName[MAX_PATH];
	char cAlternateFileName[14];
};

struct SYSTEMTIME
{
	WORD wYear;
	WORD wMonth;
	WORD wDayOfWeek;
	WORD wDay;
	WORD wHour;
	WORD wMinute;
	WORD wSecond;
	WORD wMilliseconds;
};

union LARGE_INTEGER
{
	struct
	{
		DWORD LowPart;
		LONG HighPart;
	};
	std::int64_t QuadPart;
};

inline int CompareFileTime(FILETIME const * left, FILETIME const * right)
{
	unsigned long long const a = ((unsigned long long)left->dwHighDateTime << 32) | left->dwLowDateTime;
	unsigned long long const b = ((unsigned long long)right->dwHighDateTime << 32) | right->dwLowDateTime;
	if (a < b) return(-1);
	if (a > b) return(1);
	return(0);
}

HANDLE FindFirstFileA(char const * pattern, WIN32_FIND_DATAA * found);
HANDLE FindFirstFile(char const * pattern, WIN32_FIND_DATAA * found);
int FindNextFileA(HANDLE handle, WIN32_FIND_DATAA * found);
int FindNextFile(HANDLE handle, WIN32_FIND_DATAA * found);
int FindClose(HANDLE handle);

#include <arpa/inet.h>
#include <chrono>
#include <cstring>
#include <strings.h>
#include <unistd.h>

#ifdef stricmp
#undef stricmp
#endif
#ifdef _stricmp
#undef _stricmp
#endif

inline void Sleep(DWORD milliseconds)
{
	usleep((useconds_t)milliseconds * 1000u);
}

inline DWORD timeGetTime(void)
{
	auto const now = std::chrono::steady_clock::now().time_since_epoch();
	return((DWORD)std::chrono::duration_cast<std::chrono::milliseconds>(now).count());
}

inline int stricmp(char const * left, char const * right)
{
	return(strcasecmp(left == nullptr ? "" : left, right == nullptr ? "" : right));
}

inline int _stricmp(char const * left, char const * right)
{
	return(stricmp(left, right));
}
