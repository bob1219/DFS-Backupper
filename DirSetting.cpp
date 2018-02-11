// standard library
#include <cstddef>

// header
#include "class.h"
#include "constant.h"
#include "function.h"

// using
using namespace std;

void dfs_backupper::DirSetting::run()
{
	size_t element_number = FromFiles.size();
	for(unsigned int i = 0; i < element_number; i++)
		dfs_backupper::copy_directory(FromFiles[i], ToFiles[i]);
}

dfs_backupper::DirSetting::DirSetting(SettingFile FromSettingFile, SettingFile ToSettingFile)
{
	open(FromSettingFile, ToSettingFile);
}
