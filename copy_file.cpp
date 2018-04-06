// copy_file.cpp
// Copyright 2018 Daiki Yoshida. All rights reserved.
// This file is a source file in DFS-Backupper project.
// This file and DFS-Backupper project are licensed by GNU-GPL v3.0.
// You can see document of GNU-GPL v3.0 in "LICENSE" file or GNU official website(https://www.gnu.org/licenses/gpl-3.0.en.html).

// standard library
#include <string>
#include <ctime>
#include <iostream>

// boost
#include <boost/filesystem.hpp>
#include <boost/format.hpp>

// header
#include "function.h"
#include "LogFile.h"

// using
using namespace std;
using namespace boost;
using namespace boost::filesystem;

void dfs_backupper::copy_file(const wstring& SourceFilename, const wstring& DestFilename, LogFile& log)
{
	if(is_regular_file(DestFilename))
	{
		const auto FromFileLastUpdate{last_write_time(SourceFilename)};
		const auto ToFileLastUpdate{last_write_time(DestFilename)};
		if(difftime(ToFileLastUpdate, FromFileLastUpdate) >= 0)
		{
			log.write((wformat{L"not need update: %1% -> %2%"} % SourceFilename % DestFilename).str());
			wcout << wformat{L"not need update:\t%1% -> %2%"} % SourceFilename % DestFilename << endl;
			return;
		}
	}
	
	try
	{
		boost::filesystem::copy_file(SourceFilename, DestFilename, copy_option::overwrite_if_exists);
	}
	catch(filesystem_error)
	{
		log.write((wformat{L"failed update: %1% -> %2%"} % SourceFilename % DestFilename).str());
		wcerr << wformat{L"failed:\t\t\t%1% -> %2%"} % SourceFilename % DestFilename << endl;
		return;
	}
	
	log.write((wformat{L"successful update: %1% -> %2%"} % SourceFilename % DestFilename).str());
	wcout << wformat{L"successful:\t\t%1% -> %2%"} % SourceFilename % DestFilename << endl;
}
