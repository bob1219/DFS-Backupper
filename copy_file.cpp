// Copyright 2018 Daiki Yoshida. All rights reserved.
//
// This file is part of DFS-Backupper.
//
// DFS-Backupper is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// DFS-Backupper is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with DFS-Backupper. If not, see <http://www.gnu.org/license/>.

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
		log.write((wformat{L"failed: %1% -> %2%"} % SourceFilename % DestFilename).str());
		wcerr << wformat{L"failed:\t\t\t%1% -> %2%"} % SourceFilename % DestFilename << endl;
		return;
	}
	
	log.write((wformat{L"successful: %1% -> %2%"} % SourceFilename % DestFilename).str());
	wcout << wformat{L"successful:\t\t%1% -> %2%"} % SourceFilename % DestFilename << endl;
}
