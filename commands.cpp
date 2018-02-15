// standard library
#include <string>
#include <iostream>

// header
#include "function.h"
#include "class.h"

// using
using namespace std;

bool dfs_backupper::command::clear(const wstring& setting_name)
{
	DirSetting dirSetting(setting_name);
	FileSetting fileSetting(setting_name);

	if(!dirSetting.clear())
		return false;
	if(!fileSetting.clear())
		return false;

	return true;
}

bool dfs_backupper::command::list(const wstring& setting_name)
{
	DirSetting dirSetting(setting_name);
	if(!dirSetting.read())
		return false;

	FileSetting fileSetting(setting_name);
	if(!fileSetting.read())
		return false;

	wcout << L"directory:\n";
	dirSetting.list();

	wcout << L'\n';

	wcout << L"file:\n";
	fileSetting.list();

	return true;
}

bool dfs_backupper::command::add(const wstring& setting_name, const wstring& option, const wstring& from, const wstring& to)
{
	if(option == L"-d")
	{
		DirSetting dirSetting(setting_name);
		if(!dirSetting.read())
			return false;

		return dirSetting.add(from, to);
	}
	else if(option == L"-f")
	{
		FileSetting fileSetting(setting_name);
		if(!fileSetting.read())
			return false;

		return fileSetting(from, to);
	}
	else throw dfs_backupper::exception(L"unknown option");
}

bool dfs_backupper::command::run(const wstring& setting_name)
{
	DirSetting dirSetting(setting_name);
	if(!dirSetting.read())
		return false;

	FileSetting fileSetting(setting_name);
	if(!fileSetting.read())
		return false;

	dirSetting.run();
	fileSetting.run();

	return true;
}

bool dfs_backupper::command::remove(const wstring& setting_name, const wstring& option, const wstring& from, const wstring& to)
{
	if(option == L"-d")
	{
		DirSetting dirSetting(setting_name);
		if(!dirSetting.read())
			return false;

		return dirSetting.remove(from, to);
	}
	else if(option == L"-f")
	{
		FileSetting fileSetting(setting_name);
		if(!fileSetting.read())
			return false;

		return fileSetting.remove(from, to);
	}
	else throw dfs_backupper::exception(L"unknown option");
}
