// standard library
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <locale>
#include <cstddef>

// header
#include "class.h"
#include "constant.h"

// using
using namespace std;

void dfs_backupper::setting::open(SettingFile FromSettingFile, SettingFile ToSettingFile)
{
	// read FromSettingFile setting file
	wostringstream FromSettingFilename_oss;
	switch(FromSettingFile)
	{
	case DIR_FROM:
		FromSettingFilename_oss	<< L'.'
					<< PATH_BREAK_CHARACTER
					<< L"DIR_FROM";
		FromSettingFilename = FromSettingFilename_oss.str();
		break;

	case DIR_TO:
		FromSettingFilename_oss	<< L'.'
					<< PATH_BREAK_CHARACTER
					<< L"DIR_TO";
		FromSettingFilename = FromSettingFilename_oss.str();
		break;

	case FILE_FROM:
		FromSettingFilename_oss	<< L'.'
					<< PATH_BREAK_CHARACTER
					<< L"FILE_FROM";
		FromSettingFilename = FromSettingFilename_oss.str();
		break;

	case FILE_TO:
		FromSettingFilename_oss	<< L'.'
					<< PATH_BREAK_CHARACTER
					<< L"FILE_TO";
		FromSettingFilename = FromSettingFilename_oss.str();
		break;
	}

	// read ToSettingFile_ifs setting file
	wostringstream ToSettingFilename_oss;
	switch(ToSettingFile)
	{
	case DIR_FROM:
		ToSettingFilename_oss	<< L'.'
					<< PATH_BREAK_CHARACTER
					<< L"DIR_FROM";
		ToSettingFilename = ToSettingFilename_oss.str();
		break;

	case DIR_TO:
		ToSettingFilename_oss	<< L'.'
					<< PATH_BREAK_CHARACTER
					<< L"DIR_TO";
		ToSettingFilename = ToSettingFilename_oss.str();
		break;

	case FILE_FROM:
		ToSettingFilename_oss	<< L'.'
					<< PATH_BREAK_CHARACTER
					<< L"FILE_FROM";
		ToSettingFilename = ToSettingFilename_oss.str();
		break;

	case FILE_TO:
		ToSettingFilename_oss	<< L'.'
					<< PATH_BREAK_CHARACTER
					<< L"FILE_TO";
		ToSettingFilename = ToSettingFilename_oss.str();
		break;
	}
}

bool dfs_backupper::setting::clear()
{
	wofstream FromFile(FromSettingFilename);
	if(FromFile.fail())
		return false;

	wofstream ToFile(ToSettingFilename);
	if(ToFile.fail())
		return false;

	FromFiles.clear();
	ToFiles.clear();

	return true;
}

void dfs_backupper::setting::list()
{
	size_t element_number = FromFiles.size();
	for(unsigned int i = 0; i < element_number; i++)
		wcout	<< FromFiles[i]
			<< L" -> "
			<< ToFiles[i]
			<< L'\n';
}

void dfs_backupper::setting::add(const wstring& FromSettingFilename, const wstring& ToSettingFilename)
{
	FromFiles.push_back(FromSettingFilename);
	ToFiles.push_back(ToSettingFilename);

	if(!write())
		throw dfs_backupper::exception(L"cannot open file");
}

bool dfs_backupper::setting::write()
{
	wofstream FromSettingFile;
	FromSettingFile.imbue(locale(""));
	FromSettingFile.open(FromSettingFilename);
	if(FromSettingFile.fail())
		return false;

	wofstream ToSettingFile;
	ToSettingFile.imbue(locale(""));
	ToSettingFile.open(ToSettingFilename);
	if(ToSettingFile.fail())
		return false;

	for(wstring setting: FromFiles)
		FromSettingFile << setting << L'\n';

	for(wstring setting: ToFiles)
		ToSettingFile << setting << L'\n';

	return true;
}

bool dfs_backupper::setting::read()
{
	wifstream FromSettingFile_ifs;
	FromSettingFile_ifs.imbue(locale(""));
	FromSettingFile_ifs.open(FromSettingFilename);
	if(FromSettingFile_ifs.fail())
		return false;

	wstring FromFile;
	while(getline(FromSettingFile_ifs, FromFile))
		FromFiles.push_back(FromFile);

	wifstream ToSettingFile_ifs;
	ToSettingFile_ifs.imbue(locale(""));
	ToSettingFile_ifs.open(ToSettingFilename);
	if(ToSettingFile_ifs.fail())
		return false;

	wstring ToFile;
	while(getline(ToSettingFile_ifs, ToFile))
		ToFiles.push_back(ToFile);
}
