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

// header
#include "function.h"
#include "class.h"

// using
using namespace std;
using namespace dfs-backupper;
using namespace boost::system;

int wmain(int argc, wchar_t** argv)
{
	try
	{
		wcout.imbue(locale(""));
		wcerr.imbue(locale(""));
		wcin.imbue(locale(""));

		if(argc == 1)
		{
			wcerr	<< L"usage: "
				<< argv[0]
				<< L" [command] <arguments>\n";
			return EXIT_FAILURE;
		}

		vector<wstring> args;
		for(wchar_t* arg: argv)
			args.push_back(arg);

		if(CommandProcess(argc, args))
			return EXIT_SUCCESS;
		else
		{
			wcerr << L"failed.\n";
			return EXIT_FAILURE;
		}
	}
	catch(system_error& e)
	{
		try
		{
			const char* mess_c = e.what();
			wchar_t* mess = new wchar_t[strlen(mess_c) + 1];
			mbstowcs(mess, mess_c, (sizeof(mess) / sizeof(*mess)));

			wcerr << L"error type:\tboost\n";
			wcerr << L"error code:\t" << e.code().value() << L'\n';
			wcerr << L"error message:\t" << mess << L'\n';

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
			mbstowcs(mess, mess_c, (sizeof(mess) / sizeof(*mess)));

			wcerr << L"error type:\tstandard\n";
			wcerr << L"error message:\t" << mess << L'\n';

			delete [] mess;
		}
		catch(...)
		{
			terminate();
		}
	}
	catch(dfs-backupper::exception& e)
	{
		wcerr << L"error type:\tDFS-Backupper\n";
		wcerr << L"error message:\t" << e.getMessage() << L'\n';
	}

	return EXIT_FAILURE;
}
