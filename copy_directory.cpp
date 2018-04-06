// copy_directory.cpp
// Copyright 2018 Daiki Yoshida. All rights reserved.
// This file is a source file in DFS-Backupper project.
// This file and DFS-Backupper project are licensed by GNU-GPL v3.0.
// You can see document of GNU-GPL v3.0 in "LICENSE" file or GNU official website(https://www.gnu.org/licenses/gpl-3.0.en.html).

// standard library
#include <string>
#include <algorithm>
#include <unordered_set>
#include <iterator>
#include <iostream>

// boost
#include <boost/filesystem.hpp>

// header
#include "function.h"
#include "constant.h"
#include "LogFile.h"

// using
using namespace std;
using namespace boost::filesystem;
using namespace boost;

void dfs_backupper::copy_directory(const wstring& sourceDirname, const wstring& destDirname, LogFile& log)
{
	// Delete end character if it's path-break-character
	const auto EndOfDestDirname{std::end(destDirname)};
	const wstring DestDirname{std::begin(destDirname),
		(*(EndOfDestDirname - 1) == PATH_BREAK_CHARACTER)
			? (EndOfDestDirname - 1)
			: EndOfDestDirname};

	// Delete end character if it's path-break-character
	const auto EndOfSourceDirname{std::end(sourceDirname)};
	const wstring SourceDirname{std::begin(sourceDirname),
		(*(EndOfSourceDirname - 1) == PATH_BREAK_CHARACTER)
			? (EndOfSourceDirname - 1)
			: EndOfSourceDirname};

	if(!is_directory(DestDirname))
		boost::filesystem::copy_directory(SourceDirname, DestDirname);

	// Remove files in destination-directory what don't exists in source-directory
	unordered_set<wstring> SourceDirectoryFiles;
	for_each(directory_iterator{SourceDirname}, directory_iterator{}, [&](const wpath& p){ SourceDirectoryFiles.insert(p.filename().wstring()); });
	for_each(directory_iterator{DestDirname}, directory_iterator{}, [&](const wpath& p)
	{
		if(SourceDirectoryFiles.find(p.filename().wstring()) == std::end(SourceDirectoryFiles))
			remove(p);
	});

	// Copy other files and directories
	for(const auto& SourceDirectoryFile: SourceDirectoryFiles)
	{
		if(is_regular_file(SourceDirname + PATH_BREAK_CHARACTER + SourceDirectoryFile))
			dfs_backupper::copy_file(SourceDirname + PATH_BREAK_CHARACTER + SourceDirectoryFile, DestDirname + PATH_BREAK_CHARACTER + SourceDirectoryFile, log);
		else
			dfs_backupper::copy_directory(SourceDirname + PATH_BREAK_CHARACTER + SourceDirectoryFile, DestDirname + PATH_BREAK_CHARACTER + SourceDirectoryFile, log);
	}
}
