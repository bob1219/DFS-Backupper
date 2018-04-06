// main.cpp
// Copyright 2018 Daiki Yoshida. All rights reserved.
// This file is a source file in DFS-Backupper project.
// This file and DFS-Backupper project are licensed by GNU-GPL v3.0.
// You can see document of GNU-GPL v3.0 in "LICENSE" file or GNU official website(https://www.gnu.org/licenses/gpl-3.0.en.html).

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
		unique_ptr<wchar_t[]>	mess{new wchar_t[mess_len + 1]};
		mbstowcs(mess.get(), mess_c, mess_len + 1);

		const auto ErrorCode{e.code().value()};

		wcerr << L"error:" << endl;
		wcerr << mess.get() << endl;
		wcerr << wformat{L"(error code: %1%)"} % ErrorCode << endl;

		log.write((wformat{L"error: %1% (error code: %2%)"} % mess.get() % ErrorCode).str());
	}
	catch(std::exception& e)
	{
		const auto		mess_c{e.what()};
		const auto		mess_len{strlen(mess_c)};
		unique_ptr<wchar_t[]>	mess{new wchar_t[mess_len + 1]};
		mbstowcs(mess.get(), mess_c, mess_len + 1);

		wcerr << L"error:" << endl;
		wcerr << mess.get() << endl;

		log.write((wformat{L"error: %1%"} % mess.get()).str());
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
