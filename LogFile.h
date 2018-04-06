// LogFile.h
// Copyright 2018 Daiki Yoshida. All rights reserved.
// This file is a header file in DFS-Backupper project.
// This file and DFS-Backupper project are licensed by GNU-GPL v3.0.
// You can see document of GNU-GPL v3.0 in "LICENSE" file or GNU official website(https://www.gnu.org/licenses/gpl-3.0.en.html).

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
