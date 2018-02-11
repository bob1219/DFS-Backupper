// standard library
#include <iostream>
#include <locale>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstring>
#include <exception>

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
			wcerr << wformat(L"usage: %1% [command] <arguments>\n") % argv[0];
			return EXIT_FAILURE;
		}

		vector<wstring> args;
		for(unsigned int i = 0; i < argc; i++)
			args.push_back(argv[i]);

		if(CommandProcess(argc, args))
			return EXIT_SUCCESS;
		else
		{
			wcerr << L"failed.\n";
			return EXIT_FAILURE;
		}
	}
	catch(boost::system::system_error& e)
	{
		try
		{
			const char* mess_c = e.what();
			wchar_t* mess = new wchar_t[strlen(mess_c) + 1];
			mbstowcs(mess, mess_c, strlen(mess_c));

			wcerr << L"error type:\tboost\n";
			wcerr << wformat(L"error code:\t%1%\n") % e.code().value();
			wcerr << wformat(L"error message:\t%1%\n") % mess;

			delete [] mess;
		}
		catch(...)
		{
			terminate();
		}
	}
	catch(std::exception& e)
	{
		try
		{
			const char* mess_c = e.what();
			wchar_t* mess = new wchar_t[strlen(mess_c) + 1];
			mbstowcs(mess, mess_c, strlen(mess_c));

			wcerr << L"error type:\tstandard\n";
			wcerr << wformat(L"error message:\t%1%\n") % mess;

			delete [] mess;
		}
		catch(...)
		{
			terminate();
		}
	}
	catch(dfs_backupper::exception& e)
	{
		wcerr << L"error type:\tDFS-Backupper\n";
		wcerr << wformat(L"error message:\t%1%\n") % e.getMessage();
	}

	return EXIT_FAILURE;
}
