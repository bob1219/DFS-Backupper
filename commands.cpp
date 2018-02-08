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

bool dfs-backupper::command::clear()
{
	DirSetting dirSetting(DIR_FROM, DIR_TO);
	if(!dirSetting.isOpen())
		return false;

	FileSetting fileSetting(FILE_FROM, FILE_TO);
	if(!fileSetting.isOpen())
		return false;

	if(!dirSetting.clear())
		return false;
	if(!fileSetting.clear())
		return false;

	return true;
}

bool dfs-backupper::command::list()
{
	DirSetting dirSetting(DIR_FROM, DIR_TO);
	if(!dirSetting.isOpen())
		return false;

	FileSetting fileSetting(FILE_FROM, FILE_TO);
	if(!fileSetting.isOpen())
		return false;

	wcout << L"directory:\n";
	dirSetting.list();

	wcout << L'\n';

	wcout << L"file:\n";
	fileSetting.list();

	return true;
}

bool dfs-backupper::command::add(const wstring& option, const wstring& from, const wstring& to)
{
	if(option == L"-d")
	{
		DirSetting dirSetting(DIR_FROM, DIR_TO);
		if(!dirSetting.isOpen())
			return false;

		if(!dirSetting.add(from, to))
			return false;

		return true;
	}
	else if(option == L"-f")
	{
		FileSetting fileSetting(FILE_FROM, FILE_TO);
		if(!fileSetting.isOpen())
			return false;

		if(!fileSetting.add(from, to))
			return false;

		return true;
	}
	else throw dfs-backupper::exception("unknown option");
}

bool dfs-backupper::command::run()
{
	DirSetting dirSetting(DIR_FROM, DIR_TO);
	if(!dirSetting.isOpen())
		return false;

	FileSetting fileSetting(FILE_FROM, FILE_TO);
	if(!fileSetting.isOpen())
		return false;

	dirSetting.run();
	fileSetting.run();

	return true;
}
