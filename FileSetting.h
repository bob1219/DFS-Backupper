// Copyright 2018 Daiki Yoshida. All rights reserved.
//
// This file is part of DFS-Backupper.
//
// DFS-Backupper is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// DFS-Backupper is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with DFS-Backupper. If not, see <http://www.gnu.org/license/>.

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
