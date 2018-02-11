// standard library
#include <cstddef>
#include <string>

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

dfs_backupper::DirSetting::DirSetting(const wstring& setting_name, SettingFile FromSettingFile, SettingFile ToSettingFile)
{
	open(setting_name, FromSettingFile, ToSettingFile);
}
