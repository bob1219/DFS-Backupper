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
	wostringstream DirFromFilename;
	DirFromFilename	<< L'.'
			<< PATH_BREAK_CHARACTER
			<< L"DIR_FROM";
	wofstream DirFromFile(DirFromFilename.str());
	if(DirFromFile.fail())
		return false;

	wostringstream DirToFilename;
	DirToFilename	<< L'.'
			<< PATH_BREAK_CHARACTER
			<< L"DIR_TO";
	wofstream DirToFile(DirToFilename.str());
	if(DirToFile.fail())
		return false;

	wostringstream FileFromFilename;
	FileFromFilename	<< L'.'
				<< PATH_BREAK_CHARACTER
				<< L"FILE_FROM";
	wofstream FileFromFile(FileFromFilename.str());
	if(FileFromFile.fail())
		return false;

	wostringstream FileToFilename;
	FileToFilename	<< L'.'
			<< PATH_BREAK_CHARACTER
			<< L"FILE_TO";
	wofstream FileToFile(FileToFilename.str());
	if(FileToFile.fail())
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
