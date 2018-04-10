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

#ifndef LOG_FILE_H
#define LOG_FILE_H

// standard library
#include <string>

namespace dfs_backupper
{
	class LogFile
	{
	private:
		std::wstring LogFilename;

	public:
		// Constructors
		LogFile();
		LogFile(const LogFile&) = default;
		LogFile(LogFile&&) = default;

		// Operators
		LogFile& operator=(const LogFile&) = default;
		LogFile& operator=(LogFile&&) = default;

		void write(const std::wstring& message);
	};
}

#endif