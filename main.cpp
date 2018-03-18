// standard library
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstring>
#include <exception>
#include <cstddef>
#include <memory>
#include <clocale>
#include <iterator>

// boost
#include <boost/system/system_error.hpp>
#include <boost/format.hpp>

// header
#include "function.h"
#include "exception.h"

// using
using namespace std;
using namespace dfs_backupper;
using namespace boost;

int wmain(int argc, wchar_t** argv)
{
	try
	{
		// Setting locale
		wcout.imbue(locale{""});
		wcerr.imbue(locale{""});
		wcin.imbue(locale{""});
		setlocale(LC_ALL, "");

		// Usage
		if(argc == 1)
		{
			wcerr << wformat{L"usage: %1% [command] <arguments>"} % argv[0] << endl;
			return EXIT_FAILURE;
		}

		vector<wstring> args;
		args.assign(begin(argv), end(argv));
		CommandProcess(args);

		return EXIT_SUCCESS;
	}
	catch(boost::system::system_error& e)
	{
		// Convert error message from Multi-Byte-String to Wide-String
		const auto		mess_c		= e.what();
		const auto		mess_len	= strlen(mess_c);
		unique_ptr<wchar_t[]>	mess{new wchar_t[mess_len + 1]};
		mbstowcs(mess.get(), mess_c, mess_len + 1);

		wcerr << L"error:" << endl;
		wcerr << mess.get() << endl;
		wcerr << wformat{L"(error code: %1%)"} % e.code().value() << endl;
	}
	catch(std::exception& e)
	{
		// Convert error message from Multi-Byte-String to Wide-String
		const auto		mess_c		= e.what();
		const auto		mess_len	= strlen(mess_c);
		unique_ptr<wchar_t[]>	mess{new wchar_t[mess_len + 1]};
		mbstowcs(mess.get(), mess_c, mess_len + 1);

		wcerr << L"error:" << endl;
		wcerr << mess.get() << endl;
	}
	catch(dfs_backupper::exception& e)
	{
		wcerr << L"error:" << endl;
		wcerr << e.getMessage() << endl;
	}

	return EXIT_FAILURE;
}
