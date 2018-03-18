// standard library
#include <string>
#include <iostream>
#include <memory>

// header
#include "function.h"
#include "DirSetting.h"
#include "FileSetting.h"
#include "exception.h"

// using
using namespace std;

void dfs_backupper::command::clear(const wstring& setting_name)
{
	DirSetting dirSetting{setting_name};	// Initialize directory setting
	FileSetting fileSetting{setting_name};	// Initialize file setting

	// clear
	dirSetting.clear();
	fileSetting.clear();
}

void dfs_backupper::command::list(const wstring& setting_name)
{
	DirSetting dirSetting{setting_name};	// Initialize directory setting
	dirSetting.read();			// Read setting file

	FileSetting fileSetting{setting_name};	// Initialize file setting
	fileSetting.read();			// Read setting file

	// Output list of directory settings
	wcout << L"directory:" << endl;
	dirSetting.list();

	wcout << endl;

	// Output list of file settings
	wcout << L"file:" << endl;
	fileSetting.list();
}

void dfs_backupper::command::add(const wstring& setting_name, const wstring& option, const wstring& from, const wstring& to)
{
	unique_ptr<setting> Setting;
	if(option == L"-d")		// directory setting
		Setting.reset(new DirSetting{setting_name});
	else if(option == L"-f")	// file setting
		Setting.reset(new FileSetting{setting_name});
	else throw dfs_backupper::exception{L"unknown option"};

	// Run
	Setting->read();
	Setting->add(from, to);
}

void dfs_backupper::command::run(const wstring& setting_name)
{
	DirSetting dirSetting{setting_name};	// Initialize directory setting
	dirSetting.read();			// Read setting file

	FileSetting fileSetting{setting_name};	// Initialize file setting
	fileSetting.read();			// Read setting file

	// Run backup
	dirSetting.run();
	fileSetting.run();
}

void dfs_backupper::command::remove(const wstring& setting_name, const wstring& option, const wstring& from, const wstring& to)
{
	unique_ptr<setting> Setting;
	if(option == L"-d")		// directory setting
		Setting.reset(new DirSetting{setting_name});
	else if(option == L"-f")	// file setting
		Setting.reset(new FileSetting{setting_name});
	else throw dfs_backupper::exception{L"unknown command"};

	// Run
	Setting->read();
	Setting->remove(from, to);
}
