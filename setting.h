// setting.h
// Copyright 2018 Daiki Yoshida. All rights reserved.
// This file is a header file in DFS-Backupper project.
// This file and DFS-Backupper project are licensed by GNU-GPL v3.0.
// You can see document of GNU-GPL v3.0 in "LICENSE" file or GNU official website(https://www.gnu.org/licenses/gpl-3.0.en.html).

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
	class setting
	{
	public:
		void open(const std::wstring& setting_name, SettingType type);
		void read();
		void clear();
		void list() const;
		void add(const std::wstring& from, const std::wstring& to);
		void remove(const std::wstring& from, const std::wstring& to);
		virtual void run() const = 0;

	private:
		std::wstring FromSettingFilename;
		std::wstring ToSettingFilename;
		void write() const;

	protected:
		std::vector<std::pair<std::wstring, std::wstring>> BackupFilePairs;
	};
}

#endif
