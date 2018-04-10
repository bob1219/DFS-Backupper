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

	log.write(L"backup was successful");
}

void dfs_backupper::command::remove(const wstring& setting_name, const wstring& option, const wstring& source, const wstring& dest, LogFile& log)
{
	unique_ptr<setting> Setting;
	if(option == L"-d")
		Setting.reset(new DirSetting{setting_name});
	else if(option == L"-f")
		Setting.reset(new FileSetting{setting_name});
	else throw dfs_backupper::exception{L"unknown option"};

	Setting->read(log);
	Setting->remove(source, dest, log);
}
