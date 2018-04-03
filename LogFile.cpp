// main.cpp
// Copyright 2018 Daiki Yoshida. All rights reserved.
// This file is a source file in DFS-Backupper project.
// This file and DFS-Backupper project are licensed by GNU-GPL v3.0.
// You can see document of GNU-GPL v3.0 in "LICENSE" file or GNU official website(https://www.gnu.org/licenses/gpl-3.0.en.html).

// standard library
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdio>
#include <sstream>

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
	LogFilename = (wformat{L".%1%logs%1%%2%-%3%-%4%.log"} % PATH_BREAK_CHARACTER % data->tm_mon + 1 % data->tm_mday % data->tm_year + 1900).str();
}

template<typename T>
LogFile& dfs_backupper::LogFile::operator<<(const T& data)
{
	static wostringstream stream;
	if(data == flush || data == endl)
	{
		wofstream file;
		file.imbue(locale{""});
		file.open(LogFilename, ios_base::out | ios_base::app);
		if(file.fail())
			throw dfs_backupper::exception{L"failed open log-file"};

		const auto timer{time(nullptr)};
		const auto* TimeData{localtime(&timer)};

		file << wformat{L"[%1$02d/%2$02d/%3% %4$02d:%5$02d:%6$02d] %7%"}	% TimeData->tm_mon + 1
											% TimeData->tm_mday
											% TimeData->tm_year + 1900
											% TimeData->tm_hour
											% TimeData->tm_min
											% TimeData->tm_sec
											% stream.str() << endl;

		stream.str("");
		stream.clear(wostringstream::goodbit);
	}
	else stream << data;

	return *this;
}
