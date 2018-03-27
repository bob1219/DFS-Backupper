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
#include "Time.h"

// using
using namespace std;
using namespace boost;
using namespace boost::filesystem;

void dfs_backupper::copy_file(const wstring& SourceFilename, const wstring& DestFilename)
{
	if(is_regular_file(DestFilename))
	{
		const Time FromFileLastUpdate{last_write_time(SourceFilename)};
		const Time ToFileLastUpdate{last_write_time(DestFilename)};
		if(FromFileLastUpdate >= ToFileLastUpdate) // It's not need update Because It's backed up
		{
			wcout << wformat{L"not need update:\t%1% -> %2%"} % SourceFilename % DestFilename << endl;
			return;
		}
	}
	
	try
	{
		boost::filesystem::copy_file(SourceFilename, DestFilename, copy_option::overwrite_if_exists);
	}
	catch(...)
	{
		wcerr << wformat{L"failed:\t\t\t%1% -> %2%"} % SourceFilename % DestFilename << endl;
		return;
	}
	
	wcout << wformat{L"successful:\t\t%1% -> %2%"} % SourceFilename % DestFilename << endl;
}
