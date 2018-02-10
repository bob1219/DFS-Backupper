// standard library
#include <cstddef>

// boost
#include <boost/filesystem.hpp>

// header
#include "class.h"
#include "constant.h"

// using
using namespace std;
using namespace boost::filesystem;

void dfs_backupper::DirSetting::run()
{
	size_t element_number = FromFiles.size();
	for(unsigned int i = 0; i < element_number; i++)
		copy_directory(FromFiles[i], ToFiles[i]);
}

dfs_backupper::DirSetting::DirSetting(SettingFile FromSettingFile, SettingFile ToSettingFile)
{
	open(FromSettingFile, ToSettingFile);
}
