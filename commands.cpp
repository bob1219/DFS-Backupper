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

bool dfs_backupper::command::clear()
{
	DirSetting dirSetting(DIR_FROM, DIR_TO);
	FileSetting fileSetting(FILE_FROM, FILE_TO);

	if(!dirSetting.clear())
		return false;
	if(!fileSetting.clear())
		return false;

	return true;
}

bool dfs_backupper::command::list()
{
	DirSetting dirSetting(DIR_FROM, DIR_TO);
	if(!dirSetting.read())
		return false;

	FileSetting fileSetting(FILE_FROM, FILE_TO);
	if(!fileSetting.read())
		return false;

	wcout << L"directory:\n";
	dirSetting.list();

	wcout << L'\n';

	wcout << L"file:\n";
	fileSetting.list();

	return true;
}

bool dfs_backupper::command::add(const wstring& option, const wstring& from, const wstring& to)
{
	if(option == L"-d")
	{
		DirSetting dirSetting(DIR_FROM, DIR_TO);
		if(!dirSetting.read())
			return false;

		dirSetting.add(from, to);

		return true;
	}
	else if(option == L"-f")
	{
		FileSetting fileSetting(FILE_FROM, FILE_TO);
		if(!fileSetting.read())
			return false;

		fileSetting.add(from, to);

		return true;
	}
	else throw dfs_backupper::exception(L"unknown option");
}

bool dfs_backupper::command::run()
{
	DirSetting dirSetting(DIR_FROM, DIR_TO);
	if(!dirSetting.read())
		return false;

	FileSetting fileSetting(FILE_FROM, FILE_TO);
	if(!fileSetting.read())
		return false;

	dirSetting.run();
	fileSetting.run();

	return true;
}
