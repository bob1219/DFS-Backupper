// standard library
#include <cstddef>
#include <string>

// header
#include "class.h"
#include "function.h"

// using
using namespace std;

void dfs_backupper::FileSetting::run() const
{
	const size_t element_number = FromFiles.size();
	for(unsigned int i = 0; i < element_number; ++i)
		dfs_backupper::copy_file(FromFiles.at(i), ToFiles.at(i));
}

dfs_backupper::FileSetting::FileSetting(const wstring& setting_name)
{
	open(setting_name, SettingType::FILE);
}
