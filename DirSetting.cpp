// standard library
#include <cstddef>
#include <string>

// header
#include "DirSetting.h"
#include "constant.h"
#include "function.h"

// using
using namespace std;

void dfs_backupper::DirSetting::run() const
{
	for(const auto& BackupFilePair: BackupFilePairs)
		copy_directory(BackupFilePair.first, BackupFilePair.second);
}

dfs_backupper::DirSetting::DirSetting(const wstring& setting_name)
{
	open(setting_name, SettingType::DIRECTORY);
}
