// standard library
#include <string>
#include <ctime>
#include <iostream>

// boost
#include <boost/filesystem.hpp>
#include <boost/format.hpp>

// header
#include "function.h"
#include "Time.h"

// using
using namespace std;
using namespace boost;
using namespace boost::filesystem;

void dfs_backupper::copy_file(const wstring& from, const wstring& to)
{
	if(is_regular_file(to))
	{
		const Time FromFileLastUpdate{last_write_time(from)};
		const Time ToFileLastUpdate{last_write_time(to)};
		if(FromFileLastUpdate >= ToFileLastUpdate) // It's not need update Because It's backed up
		{
			wcout << wformat{L"not need update:\t%1% -> %2%"} % from % to << endl;
			return;
		}
	}
	
	try
	{
		boost::filesystem::copy_file(from, to, copy_option::overwrite_if_exists);
	}
	catch(...)
	{
		wcerr << wformat{L"failed:\t\t\t%1% -> %2%"} % from % to << endl;
		return;
	}
	
	wcout << wformat{L"successful:\t\t%1% -> %2%"} % from % to << endl;
}
