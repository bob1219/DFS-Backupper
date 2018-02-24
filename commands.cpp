// standard library
#include <string>
#include <iostream>
#include <memory>

// header
#include "function.h"
#include "class.h"

// using
using namespace std;

void dfs_backupper::command::clear(const wstring& setting_name)
{
	DirSetting dirSetting(setting_name);
	FileSetting fileSetting(setting_name);

	dirSetting.clear();
	fileSetting.clear();
}

void dfs_backupper::command::list(const wstring& setting_name)
{
	DirSetting dirSetting(setting_name);
	dirSetting.read();

	FileSetting fileSetting(setting_name);
	fileSetting.read();

	wcout << L"directory:" << endl;
	dirSetting.list();

	wcout << endl;

	wcout << L"file:" << endl;
	fileSetting.list();
}

void dfs_backupper::command::add(const wstring& setting_name, const wstring& option, const wstring& from, const wstring& to)
{
	unique_ptr<setting> Setting;
	if(option == L"-d")
		Setting.reset(new DirSetting(setting_name));
	else if(option == L"-f")
		Setting.reset(new FileSetting(setting_name));
	else throw dfs_backupper::exception(L"unknown option");

	Setting->read();
	Setting->add(from, to);
}

void dfs_backupper::command::run(const wstring& setting_name)
{
	DirSetting dirSetting(setting_name);
	dirSetting.read();

	FileSetting fileSetting(setting_name);
	fileSetting.read();

	dirSetting.run();
	fileSetting.run();
}

void dfs_backupper::command::remove(const wstring& setting_name, const wstring& option, const wstring& from, const wstring& to)
{
	unique_ptr<setting> Setting;
	if(option == L"-d")
		Setting.reset(new DirSetting(setting_name));
	else if(option == L"-f")
		Setting.reset(new FileSetting(setting_name));
	else throw dfs_backupper::exception(L"unknown command");

	Setting->read();
	Setting->add(from, to);
}
