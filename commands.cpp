// standard library
#include <sstream>
#include <iostream>
#include <fstream>
#include <locale>

// header
#include "function.h"
#include "constant.h"
#include "class.h"

// using
using namespace std;

bool dfs-backupper::command::clear()
{
	setting DirSetting(DIR_FROM, DIR_TO);
	if(!DirSetting.isOpen())
		return false;
	if(!DirSetting.clear())
		return false;

	setting FileSetting(FILE_FROM, FILE_TO);
	if(!FileSetting.isOpen())
		return false;
	if(!FileSetting.clear())
		return false;

	return true;
}

bool dfs-backupper::command::list()
{
	setting DirSetting(DIR_FROM, DIR_TO);
	if(!DirSetting.isOpen())
		return false;

	setting FileSetting(FILE_FROM, FILE_TO);
	if(!FileSetting.isOpen())
		return false;

	wcout << L"directory:\n";
	DirSetting.list();

	wcout << L'\n';

	wcout << L"file:\n";
	FileSetting.list();

	return true;
}
