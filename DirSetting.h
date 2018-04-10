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

#ifndef DIR_SETTING_H
#define DIR_SETTING_H

// standard library
#include <string>

// header
#include "constant.h"
#include "setting.h"

namespace dfs_backupper
{
	// declaration
	class LogFile;

	class DirSetting : public setting
	{
	public:
		// Constructors
		DirSetting() = default;
		explicit DirSetting(const std::wstring& setting_name) { open(setting_name, SettingType::DIRECTORY); }
		DirSetting(const DirSetting&) = default;
		DirSetting(DirSetting&&) = default;

		// Operators
		DirSetting& operator=(const DirSetting&) = default;
		DirSetting& operator=(DirSetting&&) = default;

		void run(LogFile& log) const override;
		void read(LogFile& log) override { base_read(log, SettingType::DIRECTORY); }
		void clear(LogFile& log) override { base_clear(log, SettingType::DIRECTORY); }
		void remove(const std::wstring& source, const std::wstring& dest, LogFile& log) override { base_remove(source, dest, log, SettingType::DIRECTORY); }
		void add(const std::wstring& source, const std::wstring& dest, LogFile& log) override { base_add(source, dest, log, SettingType::DIRECTORY); }
	};
}

#endif
