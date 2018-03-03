// standard library
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstring>
#include <exception>
#include <cstddef>
#include <memory>

// boost
#include <boost/system/system_error.hpp>
#include <boost/format.hpp>

// header
#include "function.h"
#include "class.h"

// using
using namespace std;
using namespace dfs_backupper;
using namespace boost;

int wmain(int argc, wchar_t** argv)
{
	try
	{
		wcout.imbue(locale(""));
		wcerr.imbue(locale(""));
		wcin.imbue(locale(""));

		if(argc == 1)
		{
			wcerr << wformat(L"usage: %1% [command] <arguments>") % argv[0] << endl;
			return EXIT_FAILURE;
		}

		vector<wstring> args;
		args.assign(argv, argv + argc);

		CommandProcess(args);

		return EXIT_SUCCESS;
	}
	catch(boost::system::system_error& e)
	{
		const char*		mess_c		= e.what();
		size_t			mess_len	= strlen(mess_c);
		unique_ptr<wchar_t[]>	mess(new wchar_t[mess_len + 1]);
		mbstowcs(mess.get(), mess_c, mess_len);

		wcerr << L"error:" << endl;
		wcerr << mess.get() << endl;
		wcerr << wformat(L"(error code: %1%)") % e.code().value() << endl;
	}
	catch(std::exception& e)
	{
		const char*		mess_c		= e.what();
		size_t			mess_len	= strlen(mess_c);
		unique_ptr<wchar_t[]>	mess(new wchar_t[mess_len + 1]);
		mbstowcs(mess.get(), mess_c, mess_len);

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
