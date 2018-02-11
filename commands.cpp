// standard library
#include <sstream>
#include <iostream>
#include <fstream>
#include <locale>
#include <string>

// header
#include "function.h"
#include "constant.h"
#include "class.h"

// using
using namespace std;

bool dfs_backupper::command::clear(const wstring& setting_name)
{
	DirSetting dirSetting(setting_name, DIR_FROM, DIR_TO);
	FileSetting fileSetting(setting_name, FILE_FROM, FILE_TO);

	if(!dirSetting.clear())
		return false;
	if(!fileSetting.clear())
		return false;

	return true;
}

bool dfs_backupper::command::list(const wstring& setting_name)
{
	DirSetting dirSetting(setting_name, DIR_FROM, DIR_TO);
	if(!dirSetting.read())
		return false;

	FileSetting fileSetting(setting_name, FILE_FROM, FILE_TO);
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
		DirSetting dirSetting(setting_name, DIR_FROM, DIR_TO);
		if(!dirSetting.read())
			return false;

		dirSetting.add(from, to);

		return true;
	}
	else if(option == L"-f")
	{
		FileSetting fileSetting(setting_name, FILE_FROM, FILE_TO);
		if(!fileSetting.read())
			return false;

		fileSetting.add(from, to);

		return true;
	}
	else throw dfs_backupper::exception(L"unknown option");
}

bool dfs_backupper::command::run(const wstring& setting_name)
{
	DirSetting dirSetting(setting_name, DIR_FROM, DIR_TO);
	if(!dirSetting.read())
		return false;

	FileSetting fileSetting(setting_name, FILE_FROM, FILE_TO);
	if(!fileSetting.read())
		return false;

	dirSetting.run();
	fileSetting.run();

	return true;
}
