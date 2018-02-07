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

dfs-backupper::setting::setting(SettingFile _from, SettingFile _to)
{
	// read _from setting file
	wostringstream SettingFilename_oss;
	switch(_from)
	{
	case DIR_FROM:
		SettingFilename_oss	<< L'.'
					<< PATH_BREAK_CHARACTER
					<< L"DIR_FROM";
		from = SettingFilename_oss.str();
		break;

	case DIR_TO:
		SettingFilename_oss	<< L'.'
					<< PATH_BREAK_CHARACTER
					<< L"DIR_TO";
		from = SettingFilename_oss.str();
		break;

	case FILE_FROM:
		SettingFilename_oss	<< L'.'
					<< PATH_BREAK_CHARACTER
					<< L"FILE_FROM";
		from = SettingFilename_oss.str();
		break;

	case FILE_TO:
		SettingFilename_oss	<< L'.'
					<< PATH_BREAK_CHARACTER
					<< L"FILE_TO";
		from = SettingFilename_oss.str();
		break;
	}

	wifstream FromSettingFile;
	FromSettingFile.imbue(locale(""));
	FromSettingFile.open(from);
	if(FromSettingFile.fail())
	{
		_isOpen = false;
		return;
	}

	wstring FromFile;
	while(getline(FromSettingFile, FromFile))
		from_vector.push_back(FromFile);

	// read _to setting file
	switch(_to)
	{
	case DIR_FROM:
		SettingFilename_oss	<< L'.'
					<< PATH_BREAK_CHARACTER
					<< L"DIR_FROM";
		to = SettingFilename_oss.str();
		break;

	case DIR_TO:
		SettingFilename_oss	<< L'.'
					<< PATH_BREAK_CHARACTER
					<< L"DIR_TO";
		to = SettingFilename_oss.str();
		break;

	case FILE_FROM:
		SettingFilename_oss	<< L'.'
					<< PATH_BREAK_CHARACTER
					<< L"FILE_FROM";
		to = SettingFilename_oss.str();
		break;

	case FILE_TO:
		SettingFilename_oss	<< L'.'
					<< PATH_BREAK_CHARACTER
					<< L"FILE_TO";
		to = SettingFilename_oss.str();
		break;
	}

	wifstream ToSettingFile;
	ToSettingFile.imbue(locale(""));
	ToSettingFile.open(to);
	if(ToSettingFile.fail())
	{
		_isOpen = false;
		return;
	}

	wstring ToFile;
	while(getline(ToSettingFile, ToFile))
		to_vector.push_back(ToFile);

	_isOpen = true;
}

bool dfs-backupper::setting::clear()
{
	wofstream FromFile(from);
	if(FromFile.fail())
		return false;

	wofstream ToFile(to);
	if(ToFile.fail())
		return false;

	from_vector.clear();
	to_vector.clear();

	return true;
}

void dfs-backupper::setting::list()
{
	size_t element_number = from_vector.size();
	for(unsigned int i = 0; i < element_number; i++)
		wcout	<< from_vector[i]
			<< L" -> "
			<< to_vector[i]
			<< L'\n';
}

void dfs-backupper::setting::add(const wstring& from, const wstring& to)
{
	from_vector.push_back(from);
	to_vector.push_back(to);

	if(!write())
		throw dfs-backupper::exception("cannot open file");
}
