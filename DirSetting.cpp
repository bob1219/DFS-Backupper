// standard library
#include <cstddef>
#include <string>

// header
#include "DirSetting.h"
#include "function.h"

// using
using namespace std;

void dfs_backupper::DirSetting::run() const
{
	for(const auto& BackupFilePair: BackupFilePairs)
		copy_directory(BackupFilePair.first, BackupFilePair.second);
}
