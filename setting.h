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

#ifndef SETTING_H
#define SETTING_H

// standard library
#include <string>
#include <vector>
#include <utility>

// header
#include "constant.h"

namespace dfs_backupper
{
	// declaration
	class LogFile;

	class setting
	{
	public:
		void open(const std::wstring& setting_name, SettingType type);
		void list() const;
		virtual void run(LogFile& log) const = 0;
		virtual void read(LogFile& log) = 0;
		virtual void clear(LogFile& log) = 0;
		virtual void remove(const std::wstring& source, const std::wstring& dest, LogFile& log) = 0;
		virtual void add(const std::wstring& source, const std::wstring& dest, LogFile& log) = 0;

	private:
		std::wstring SourceSettingFilename;
		std::wstring DestSettingFilename;
		void write(LogFile& log, SettingType type) const;

	protected:
		std::vector<std::pair<std::wstring, std::wstring>> BackupFilePairs;
		void base_read(LogFile& log, SettingType type);
		void base_clear(LogFile& log, SettingType type);
		void base_remove(const std::wstring& source, const std::wstring& dest, LogFile& log, SettingType type);
		void base_add(const std::wstring& source, const std::wstring& dest, LogFile& log, SettingType type);
	};
}

#endif
