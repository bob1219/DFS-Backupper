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

void dfs_backupper::copy_directory(const wstring& _from, const wstring& _to)
{
	// Remove last character of to-filename If it's path-break-character
	const auto to = _to;
	if(*(std::end(to) - 1) == PATH_BREAK_CHARACTER)
		to = to.substr(0, distance(std::begin(to), std::end(to) - 2));

	// Remove last character of from-filename If it's path-break-character
	const auto from = _from;
	if(*(std::end(from) - 1) == PATH_BREAK_CHARACTER)
		from = from.substr(0, distance(std::begin(from), std::end(from) - 2));

	// Create to-directory If it's not exists
	if(!is_directory(to))
		copy_directory(from, to);

	// Remove not exists in from-directory files on to-directiry
	unordered_set<wstring> FromDirectoryFiles;
	for_each(directory_iterator{from}, directory_iterator{}, [&](const wpath& p){ FromDirectoryFiles.insert(p.filename().wstring()); });
	for_each(directory_iterator{to}, directory_iterator{}, [&](const wpath& p)
	{
		if(FromDirectoryFiles.find(p.filename().wstring()) == FromDirectoryFiles.end())
			remove(p);
	});

	// Copy other files
	for(const auto& FromDirectoryFile: FromDirectoryFiles)
		dfs_backupper::copy_file(from + PATH_BREAK_CHARACTER + FromDirectoryFile, to + PATH_BREAK_CHARACTER + FromDirectoryFile);
}
