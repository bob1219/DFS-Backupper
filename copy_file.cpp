// standard library
#include <string>
#include <ctime>
#include <iostream>

// boost
#include <boost/filesystem.hpp>
#include <boost/format.hpp>

// header
#include "function.h"

// using
using namespace std;
using namespace boost;
using namespace boost::filesystem;

void dfs_backupper::copy_file(const wstring& from, const wstring& to)
{
	if(is_regular_file(to))
	{
		time_t FromFileLastUpdate	= last_write_time(from);
		time_t ToFileLastUpdate		= last_write_time(to);
		if(difftime(FromFileLastUpdate, ToFileLastUpdate) <= 0)
		{
			wcout << wformat(L"not need update:\t%1% -> %2%") % from % to << endl;
			return;
		}
	}
	
	try
	{
		boost::filesystem::copy_file(from, to, copy_option::overwrite_if_exists);
	}
	catch(...)
	{
		wcerr << wformat(L"failed:\t\t\t%1% -> %2%") % from % to << endl;
		return;
	}
	
	wcout << wformat(L"successful:\t\t%1% -> %2%") % from % to << endl;
}
