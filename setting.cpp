// standard library
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <locale>

// header
#include "class.h"
#include "constant.h"

// using
using namespace std;

dfs-backupper::setting::setting(SettingFile from, SettingFile to)
{
	// read from setting file
	wstring SettingFilename;
	wostringstream SettingFilename_oss;
	switch(from)
	{
	case DIR_FROM:
		SettingFilename_oss	<< L'.'
					<< PATH_BREAK_CHARACTER
					<< L"DIR_FROM";
		SettingFilename = SettingFilename_oss.str();
		break;

	case DIR_TO:
		SettingFilename_oss	<< L'.'
					<< PATH_BREAK_CHARACTER
					<< L"DIR_TO";
		SettingFilename = SettingFilename_oss.str();
		break;

	case FILE_FROM:
		SettingFilename_oss	<< L'.'
					<< PATH_BREAK_CHARACTER
					<< L"FILE_FROM";
		SettingFilename = SettingFilename_oss.str();
		break;

	case FILE_TO:
		SettingFilename_oss	<< L'.'
					<< PATH_BREAK_CHARACTER
					<< L"FILE_TO";
		SettingFilename = SettingFilename_oss.str();
		break;
	}

	wifstream FromSettingFile;
	FromSettingFile.imbue(locale(""));
	FromSettingFile.open(SettingFilename);
	if(FromSettingFile.fail())
	{
		_isOpen = false;
		return;
	}

	wstring FromFile;
	while(getline(FromSettingFile, FromFile))
		from_vector.push_back(FromFile);

	// read to setting file
	switch(to)
	{
	case DIR_FROM:
		SettingFilename_oss	<< L'.'
					<< PATH_BREAK_CHARACTER
					<< L"DIR_FROM";
		SettingFilename = SettingFilename_oss.str();
		break;

	case DIR_TO:
		SettingFilename_oss	<< L'.'
					<< PATH_BREAK_CHARACTER
					<< L"DIR_TO";
		SettingFilename = SettingFilename_oss.str();
		break;

	case FILE_FROM:
		SettingFilename_oss	<< L'.'
					<< PATH_BREAK_CHARACTER
					<< L"FILE_FROM";
		SettingFilename = SettingFilename_oss.str();
		break;

	case FILE_TO:
		SettingFilename_oss	<< L'.'
					<< PATH_BREAK_CHARACTER
					<< L"FILE_TO";
		SettingFilename = SettingFilename_oss.str();
		break;
	}

	wifstream ToSettingFile;
	ToSettingFile.imbue(locale(""));
	ToSettingFile.open(SettingFilename);
	if(ToSettingFile.fail())
	{
		_isOpen = false;
		return;
	}

	wstring ToFile;
	while(getline(ToSettingFile, ToFile))
		to_vector.push_back(ToFile);
}
