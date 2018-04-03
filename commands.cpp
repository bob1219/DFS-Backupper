// commands.cpp
// Copyright 2018 Daiki Yoshida. All rights reserved.
// This file is a source file in DFS-Backupper project.
// This file and DFS-Backupper project are licensed by GNU-GPL v3.0.
// You can see document of GNU-GPL v3.0 in "LICENSE" file or GNU official website(https://www.gnu.org/licenses/gpl-3.0.en.html).

// standard library
#include <string>
#include <iostream>
#include <memory>

// header
#include "function.h"
#include "DirSetting.h"
#include "FileSetting.h"
#include "exception.h"
#include "LogFile.h"

// using
using namespace std;

void dfs_backupper::command::clear(const wstring& setting_name, LogFile& log)
{
	DirSetting dirSetting{setting_name};
	FileSetting fileSetting{setting_name};

	dirSetting.clear(log);
	fileSetting.clear(log);
}

void dfs_backupper::command::list(const wstring& setting_name, LogFile& log)
{
	DirSetting dirSetting{setting_name};
	dirSetting.read(log);

	FileSetting fileSetting{setting_name};
	fileSetting.read(log);

	// Print directory settings
	wcout << L"directory:" << endl;
	dirSetting.list();

	wcout << endl;

	// Print file settings
	wcout << L"file:" << endl;
	fileSetting.list();
}

void dfs_backupper::command::add(const wstring& setting_name, const wstring& option, const wstring& source, const wstring& dest, LogFile& log)
{
	unique_ptr<setting> Setting;
	if(option == L"-d")
		Setting.reset(new DirSetting{setting_name});
	else if(option == L"-f")
		Setting.reset(new FileSetting{setting_name});
	else throw dfs_backupper::exception{L"unknown option"};

	Setting->read(log);
	Setting->add(source, dest, log);
}

void dfs_backupper::command::run(const wstring& setting_name, LogFile& log)
{
	DirSetting dirSetting{setting_name};
	dirSetting.read(log);

	FileSetting fileSetting{setting_name};
	fileSetting.read(log);

	dirSetting.run(log);
	fileSetting.run(log);
}

void dfs_backupper::command::remove(const wstring& setting_name, const wstring& option, const wstring& source, const wstring& dest, LogFile& log)
{
	unique_ptr<setting> Setting;
	if(option == L"-d")
		Setting.reset(new DirSetting{setting_name});
	else if(option == L"-f")
		Setting.reset(new FileSetting{setting_name});
	else throw dfs_backupper::exception{L"unknown command"};

	Setting->read(log);
	Setting->remove(source, dest, log);
}
