// FileSetting.cpp
// Copyright 2018 Daiki Yoshida. All rights reserved.
// This file is a source file in DFS-Backupper project.
// This file and DFS-Backupper project are licensed by GNU-GPL v3.0.
// You can see document of GNU-GPL v3.0 in "LICENSE" file or GNU official website(https://www.gnu.org/licenses/gpl-3.0.en.html).

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
