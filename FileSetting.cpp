// standard library
#include <cstddef>
#include <iostream>

// boost
#include <boost/filesystem.hpp>

// header
#include "class.h"

// using
using namespace std;
using namespace boost::filesystem;

void dfs_backupper::FileSetting::run()
{
	size_t element_number = FromFiles.size();
	for(unsigned int i = 0; i < element_number; i++)
	{
		try
		{
			copy_file(FromFiles[i], ToFiles[i], copy_option::overwrite_if_exists);
		}
		catch(...)
		{
			wcerr	<< L"failed:\t"
				<< FromFiles[i]
				<< L" -> "
				<< ToFiles[i]
				<< L'\n';
			continue;
		}

		wcerr	<< L"succeeded:\t"
			<< FromFiles[i]
			<< L" -> "
			<< ToFiles[i]
			<< L'\n';
	}
}

dfs_backupper::FileSetting::FileSetting(SettingFile FromSettingFile, SettingFile ToSettingFile)
{
	open(FromSettingFile, ToSettingFile);
}
