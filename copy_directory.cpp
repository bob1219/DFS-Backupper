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

void dfs_backupper::copy_directory(const wstring& sourceDirname, const wstring& destDirname)
{
	const auto EndOfDestDirname{std::end(destDirname)};
	const wstring DestDirname{std::begin(destDirname),
		(*(EndOfDestDirname - 1) == PATH_BREAK_CHARACTER)
			? (EndOfDestDirname - 1)
			: EndOfDestDirname};

	const auto EndOfSourceDirname{std::end(sourceDirname)};
	const wstring SourceDirname{std::begin(sourceDirname),
		(*(EndOfSourceDirname - 1) == PATH_BREAK_CHARACTER)
			? (EndOfSourceDirname - 1)
			: EndOfSourceDirname};

	if(!is_directory(DestDirname))
		copy_directory(SourceDirname, DestDirname);

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
