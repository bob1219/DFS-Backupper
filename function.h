// function.h
// Copyright 2018 Daiki Yoshida. All rights reserved.
// This file is a header file in DFS-Backupper project.
// This file and DFS-Backupper project are licensed by GNU-GPL v3.0.
// You can see document of GNU-GPL v3.0 in "LICENSE" file or GNU official website(https://www.gnu.org/licenses/gpl-3.0.en.html).

#ifndef FUNCTION_H
#define FUNCTION_H

// standard library
#include <vector>
#include <string>

namespace dfs_backupper
{
	// declaration
	class LogFile;

	void CommandProcess(const std::vector<std::wstring>& args);
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
