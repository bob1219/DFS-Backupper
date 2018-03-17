// standard library
#include <cstddef>
#include <string>

// header
#include "FileSetting.h"
#include "function.h"

// using
using namespace std;

void dfs_backupper::FileSetting::run() const
{
	for(const auto& BackupFilePair: BackupFilePairs)
		copy_file(BackupFilePair.first, BackupFilePair.second);
}
