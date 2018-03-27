// constant.h
// Copyright 2018 Daiki Yoshida. All rights reserved.
// This file is a header file in DFS-Backupper project.
// This file and DFS-Backupper project are licensed by GNU-GPL v3.0.
// You can see document of GNU-GPL v3.0 in "LICENSE" file or GNU official website(https://www.gnu.org/licenses/gpl-3.0.en.html).

#ifndef CONSTANT_H
#define CONSTANT_H

namespace dfs_backupper
{
	enum class SettingType
	{
		DIRECTORY,
		FILE
	};

	static constexpr auto PATH_BREAK_CHARACTER = L'\\';
}

#endif
