// standard library
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstring>
#include <exception>
#include <cstddef>

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
		for(unsigned int i = 0; i < argc; i++)
			args.push_back(argv[i]);

		CommandProcess(args);

		return EXIT_SUCCESS;
	}
	catch(boost::system::system_error& e)
	{
		const char*	mess_c		= e.what();
		size_t		mess_len	= strlen(mess_c);
		wchar_t*	mess		= new wchar_t[mess_len + 1];
		mbstowcs(mess, mess_c, mess_len);

		wcerr << L"error:" << endl;
		wcerr << mess << endl;
		wcerr << wformat(L"(error code: %1%)") % e.code().value() << endl;

		delete [] mess;
	}
	catch(std::exception& e)
	{
		const char*	mess_c		= e.what();
		size_t		mess_len	= strlen(mess_c);
		wchar_t*	mess		= new wchar_t[mess_len + 1];
		mbstowcs(mess, mess_c, mess_len);

		wcerr << L"error:" << endl;
		wcerr << mess << endl;

		delete [] mess;
	}
	catch(dfs_backupper::exception& e)
	{
		wcerr << L"error:" << endl;
		wcerr << e.getMessage() << endl;
	}

	return EXIT_FAILURE;
}
