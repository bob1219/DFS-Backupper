// standard library
#include <cstddef>

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
		copy_file(FromFiles[i], ToFiles[i], copy_option::overwrite_if_exists);
}

dfs_backupper::FileSetting::FileSetting(SettingFile FromSettingFile, SettingFile ToSettingFile)
{
	open(FromSettingFile, ToSettingFile);
}
