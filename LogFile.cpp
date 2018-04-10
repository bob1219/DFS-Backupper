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
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>

// boost
#include <boost/format.hpp>

// header
#include "LogFile.h"
#include "constant.h"
#include "exception.h"

// using
using namespace std;
using namespace boost;

dfs_backupper::LogFile::LogFile()
{
	const auto timer{time(nullptr)};
	const auto* data{localtime(&timer)};
	LogFilename = (wformat{L".%1%logs%1%%2$02d-%3$02d-%4$02d.log"} % PATH_BREAK_CHARACTER % (data->tm_mon + 1) % data->tm_mday % (data->tm_year + 1900)).str();
}

void dfs_backupper::LogFile::write(const wstring& message)
{
	const auto timer{time(nullptr)};
	const auto* data{localtime(&timer)};

	wofstream file;
	file.imbue(locale{""});
	file.open(LogFilename, ios_base::out | ios_base::app);
	if(file.fail())
		throw dfs_backupper::exception{L"failed open log-file"};

	file << wformat{L"[%1$02d/%2$02d/%3% %4$02d:%5$02d:%6$02d] %7%"}	% (data->tm_mon + 1)
										% data->tm_mday
										% (data->tm_year + 1900)
										% data->tm_hour
										% data->tm_min
										% data->tm_sec
										% message << endl;
}
