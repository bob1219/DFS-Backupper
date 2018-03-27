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

// boost
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <boost/format.hpp>

// header
#include "function.h"
#include "constant.h"

// using
using namespace std;
using namespace boost::filesystem;
using namespace boost;

void dfs_backupper::copy_directory(const wstring& _sourceDirname, const wstring& _destDirname)
{
	// Remove last character of to-dirname If it's path-break-character
	const auto EndOfDestDirname = std::end(_destDirname);
	const wstring DestDirname{std::begin(_destDirname), (*(EndOfDestDirname - 1) == PATH_BREAK_CHARACTER) ? (EndOfDestDirname - 1) : EndOfDestDirname};

	// Remove last character of source-dirname If it's path-break-character
	const auto EndOfSourceDirname = std::end(_sourceDirname);
	const wstring SourceDirname{std::begin(_sourceDirname), (*(EndOfSourceDirname - 1) == PATH_BREAK_CHARACTER) ? (EndOfSourceDirname - 1) : EndOfSourceDirname};

	// Create to-directory If it's not exists
	if(!is_directory(to))
		copy_directory(SourceDirname, DestDirname);

	// Remove not exists in source-directory files on to-directiry
	unordered_set<wstring> FromDirectoryFiles;
	for_each(directory_iterator{SourceDirname}, directory_iterator{}, [&](const wpath& p){ FromDirectoryFiles.insert(p.filename().wstring()); });
	for_each(directory_iterator{DestDirname}, directory_iterator{}, [&](const wpath& p)
	{
		if(FromDirectoryFiles.find(p.filename().wstring()) == FromDirectoryFiles.end())
			remove(p);
	});

	// Copy other files
	for(const auto& FromDirectoryFile: FromDirectoryFiles)
		dfs_backupper::copy_file(SourceDirname + PATH_BREAK_CHARACTER + FromDirectoryFile, DestDirname + PATH_BREAK_CHARACTER + FromDirectoryFile);
}
