// standard library
#include <sstream>
#include <iostream>
#include <fstream>

// header
#include "function.h"
#include "constant.h"

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
