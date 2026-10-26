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

#define CALLBACK
#define WINAPI
#define APIENTRY
