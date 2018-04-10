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
#include <cstdlib>
#include <vector>
#include <string>
#include <cstring>
#include <exception>
#include <memory>
#include <clocale>

// boost
#include <boost/system/system_error.hpp>
#include <boost/format.hpp>

// header
#include "function.h"
#include "exception.h"
#include "LogFile.h"

// using
using namespace std;
using namespace dfs_backupper;
using namespace boost;

int wmain(int argc, wchar_t** argv)
{
	LogFile log;

	try
	{
		wcout.imbue(locale{""});
		wcerr.imbue(locale{""});
		wcin.imbue(locale{""});
		setlocale(LC_ALL, "");

		if(argc == 1)
		{
			wcerr << wformat{L"usage: %1% [command] <arguments>"} % argv[0] << endl;
			return EXIT_FAILURE;
		}

		CommandProcess(vector<wstring>{argv, argv + argc}, log);

		return EXIT_SUCCESS;
	}
	catch(boost::system::system_error& e)
	{
		const auto		mess_c{e.what()};
		const auto		mess_len{strlen(mess_c)};
		unique_ptr<wchar_t[]>	mess_p{new wchar_t[mess_len + 1]};
		mbstowcs(mess_p.get(), mess_c, mess_len + 1);

		const auto ErrorCode{e.code().value()};
		const auto mess{mess_p.get()};

		wcerr << L"error:" << endl;
		wcerr << mess << endl;
		wcerr << wformat{L"(error code: %1%)"} % ErrorCode << endl;

		log.write((wformat{L"error: %1% (error code: %2%)"} % mess % ErrorCode).str());
	}
	catch(std::exception& e)
	{
		const auto		mess_c{e.what()};
		const auto		mess_len{strlen(mess_c)};
		unique_ptr<wchar_t[]>	mess_p{new wchar_t[mess_len + 1]};
		mbstowcs(mess_p.get(), mess_c, mess_len + 1);

		const auto mess{mess_p.get()};

		wcerr << L"error:" << endl;
		wcerr << mess << endl;

		log.write((wformat{L"error: %1%"} % mess).str());
	}
	catch(dfs_backupper::exception& e)
	{
		const auto mess{e.getMessage()};

		wcerr << L"error:" << endl;
		wcerr << mess << endl;

		log.write((wformat{L"error: %1%"} % mess).str());
	}

	return EXIT_FAILURE;
}
