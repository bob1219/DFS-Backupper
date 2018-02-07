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
	wcout << L"directory:\n";
	wostringstream DirFromFilename;
	DirFromFilename	<< L'.'
			<< PATH_BREAK_CHARACTER
			<< L"DIR_FROM";
	wostringstream DirToFilename;
	DirToFilename	<< L'.'
			<< PATH_BREAK_CHARACTER
			<< L"DIR_TO";
	setting DirSetting(DirFromFilename.str(), DirToFilename.str());
	if(!DirSetting.isOpen())
		return false;
	DirSetting.list();

	wcout << L"file:\n";
	wostringstream FileFromFilename;
	FileFromFilename	<< L'.'
				<< PATH_BREAK_CHARACTER
				<< L"FILE_FROM";
	wostringstream FileToFilename;
	FileToFilename	<< L'.'
			<< PATH_BREAK_CHARACTER
			<< L"FILE_TO";
	setting FileSetting(FileFromFilename.str(), FileToFilename.str());
	if(!FileSetting.isOpen())
		return false;
	FileSetting.list();

	return true;
}
