/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#include "platform.h"

#if !defined(_WIN32)

#include <cstdio>
#include <cstring>
#include <dirent.h>
#include <fnmatch.h>
#include <string>
#include <sys/stat.h>

namespace
{

struct Finder
{
	DIR * Directory;
	std::string DirectoryPath;
	std::string Pattern;
};


void Fill_Found(WIN32_FIND_DATAA * found, char const * name, struct stat const & info)
{
	std::memset(found, 0, sizeof(*found));
	found->dwFileAttributes = S_ISDIR(info.st_mode) ? FILE_ATTRIBUTE_DIRECTORY : FILE_ATTRIBUTE_NORMAL;
	found->nFileSizeLow = (DWORD)info.st_size;
	found->nFileSizeHigh = (DWORD)((unsigned long long)info.st_size >> 32);
	std::snprintf(found->cFileName, MAX_PATH, "%s", name);
}


std::string Join_Path(std::string const & directory, std::string const & name)
{
	if (directory == ".") {
		return(name);
	}
	if (!directory.empty() && directory.back() == '/') {
		return(directory + name);
	}
	return(directory + "/" + name);
}

}


HANDLE FindFirstFileA(char const * pattern, WIN32_FIND_DATAA * found)
{
	if (pattern == nullptr || found == nullptr) {
		return(INVALID_HANDLE_VALUE);
	}

	std::string text(pattern);
	for (char & character : text) {
		if (character == '\\') {
			character = '/';
		}
	}

	std::string directory = ".";
	std::string name = text;
	std::string::size_type const slash = text.find_last_of('/');
	if (slash != std::string::npos) {
		directory = slash == 0 ? "/" : text.substr(0, slash);
		name = text.substr(slash + 1);
	}

	bool const wild = name.find_first_of("*?") != std::string::npos;
	if (!wild) {
		std::string const path = (directory == ".") ? name : directory + "/" + name;
		struct stat info;
		if (stat(path.c_str(), &info) != 0) {
			return(INVALID_HANDLE_VALUE);
		}
		Fill_Found(found, name.c_str(), info);
		return(new Finder{nullptr, directory, {}});
	}

	DIR * opened = opendir(directory.c_str());
	if (opened == nullptr) {
		return(INVALID_HANDLE_VALUE);
	}
	Finder * finder = new Finder{opened, directory, name};
	if (!FindNextFileA(finder, found)) {
		FindClose(finder);
		return(INVALID_HANDLE_VALUE);
	}
	return(finder);
}


HANDLE FindFirstFile(char const * pattern, WIN32_FIND_DATAA * found)
{
	return(FindFirstFileA(pattern, found));
}


int FindNextFileA(HANDLE handle, WIN32_FIND_DATAA * found)
{
	Finder * finder = static_cast<Finder *>(handle);
	if (finder == nullptr || finder->Directory == nullptr || found == nullptr) {
		return(0);
	}

	while (dirent * entry = readdir(finder->Directory)) {
		if (fnmatch(finder->Pattern.c_str(), entry->d_name, 0) != 0) {
			continue;
		}
		std::string const path = Join_Path(finder->DirectoryPath, entry->d_name);
		struct stat info;
		if (stat(path.c_str(), &info) != 0) {
			continue;
		}
		Fill_Found(found, entry->d_name, info);
		return(1);
	}
	return(0);
}


int FindNextFile(HANDLE handle, WIN32_FIND_DATAA * found)
{
	return(FindNextFileA(handle, found));
}


int FindClose(HANDLE handle)
{
	Finder * finder = static_cast<Finder *>(handle);
	if (finder == nullptr) {
		return(0);
	}
	if (finder->Directory != nullptr) {
		closedir(finder->Directory);
	}
	delete finder;
	return(1);
}

#endif
