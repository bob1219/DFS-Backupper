// FileSetting.h
// Copyright 2018 Daiki Yoshida. All rights reserved.
// This file is a header file in DFS-Backupper project.
// This file and DFS-Backupper project are licensed by GNU-GPL v3.0.
// You can see document of GNU-GPL v3.0 in "LICENSE" file or GNU official website(https://www.gnu.org/licenses/gpl-3.0.en.html).

#ifndef FILE_SETTING_H
#define FILE_SETTING_H

// standard library
#include <string>

// header
#include "constant.h"
#include "setting.h"

namespace dfs_backupper
{
	// declaration
	class LogFile;

	class FileSetting : public setting
	{
	public:
		// Constructors
		FileSetting() = default;
		explicit FileSetting(const std::wstring& setting_name) { open(setting_name, SettingType::FILE); }
		FileSetting(const FileSetting&) = default;
		FileSetting(FileSetting&&) = default;

		// Operator
		FileSetting& operator=(const FileSetting&) = default;
		FileSetting& operator=(FileSetting&&) = default;

		void run(LogFile& log) const override;
		void read(LogFile& log) override { base_read(log, SettingType::FILE); }
		void clear(LogFile& log) override { base_clear(log, SettingType::FILE); }
		void remove(const std::wstring& source, const std::wstring& dest, LogFile& log) override { base_remove(source, dest, log, SettingType::FILE); }
		void add(const std::wstring& source, const std::wstring& dest, LogFile& log) override { base_add(source, dest, log, SettingType::FILE); }
	};
}

#endif
