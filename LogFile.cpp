// main.cpp
// Copyright 2018 Daiki Yoshida. All rights reserved.
// This file is a source file in DFS-Backupper project.
// This file and DFS-Backupper project are licensed by GNU-GPL v3.0.
// You can see document of GNU-GPL v3.0 in "LICENSE" file or GNU official website(https://www.gnu.org/licenses/gpl-3.0.en.html).

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
	const tm* data{localtime(&timer)};
	LogFilename = (wformat{L".%1%logs%1%%2$02d-%3$02d-%4$02d.log"} % PATH_BREAK_CHARACTER % (data->tm_mon + 1) % data->tm_mday % (data->tm_year + 1900)).str();
}

void dfs_backupper::LogFile::write(const wstring& message)
{
	const auto timer{time(nullptr)};
	const tm* data{localtime(&timer)};

	wofstream file;
	file.imbue(locale{""});
	file.open(LogFilename);
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
