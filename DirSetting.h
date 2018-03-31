// DirSetting.h
// Copyright 2018 Daiki Yoshida. All rights reserved.
// This file is a header file in DFS-Backupper project.
// This file and DFS-Backupper project are licensed by GNU-GPL v3.0.
// You can see document of GNU-GPL v3.0 in "LICENSE" file or GNU official website(https://www.gnu.org/licenses/gpl-3.0.en.html).

#ifndef DIR_SETTING_H
#define DIR_SETTING_H

// standard library
#include <string>

// header
#include "constant.h"
#include "setting.h"

namespace dfs_backupper
{
	class DirSetting : public setting
	{
	public:
		// Constructors
		explicit DirSetting(const std::wstring& setting_name) { open(setting_name, SettingType::DIRECTORY); }
		DirSetting(const DirSetting&) = default;
		DirSetting(DirSetting&&) = default;

		// Operators
		DirSetting& operator=(const DirSetting&) = default;
		DirSetting& operator=(DirSetting&&) = default;

		void run() const override;
	};
}

#endif
