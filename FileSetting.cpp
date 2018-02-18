// standard library
#include <cstddef>
#include <iostream>

// boost
#include <boost/filesystem.hpp>
#include <boost/format.hpp>

// header
#include "class.h"

// using
using namespace std;
using namespace boost::filesystem;
using namespace boost;

void dfs_backupper::FileSetting::run()
{
	const size_t element_number = FromFiles.size();
	for(unsigned int i = 0; i < element_number; i++)
	{
		try
		{
			copy_file(FromFiles.at(i), ToFiles.at(i), copy_option::overwrite_if_exists);
		}
		catch(...)
		{
			wcerr << wformat(L"failed:\t\t%1% -> %2%\n") % FromFiles.at(i) % ToFiles.at(i);
			continue;
		}

		wcout << wformat(L"succeeded:\t%1% -> %2%\n") % FromFiles.at(i) % ToFiles.at(i);
	}
}

dfs_backupper::FileSetting::FileSetting(const wstring& setting_name)
{
	open(setting_name, SettingType::FILE);
}
