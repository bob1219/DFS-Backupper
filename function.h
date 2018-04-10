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

#ifndef FUNCTION_H
#define FUNCTION_H

// standard library
#include <vector>
#include <string>

namespace dfs_backupper
{
	// declaration
	class LogFile;

	void CommandProcess(const std::vector<std::wstring>& args, LogFile& log);
	void copy_directory(const std::wstring& _sourceDirname, const std::wstring& _destDirname, LogFile& log);
	void copy_file(const std::wstring& SourceFilename, const std::wstring& DestFilename, LogFile& log);

	namespace command
	{
		void clear(const std::wstring& setting_name, LogFile& log);
		void list(const std::wstring& setting_name, LogFile& log);
		void add(const std::wstring& setting_name, const std::wstring& option, const std::wstring& source, const std::wstring& dest, LogFile& log);
		void run(const std::wstring& setting_name, LogFile& log);
		void remove(const std::wstring& setting_name, const std::wstring& option, const std::wstring& source, const std::wstring& dest, LogFile& log);
	}
}

#endif
