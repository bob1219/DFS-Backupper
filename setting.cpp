// setting.cpp
// Copyright 2018 Daiki Yoshida. All rights reserved.
// This file is a source file in DFS-Backupper project.
// This file and DFS-Backupper project are licensed by GNU-GPL v3.0.
// You can see document of GNU-GPL v3.0 in "LICENSE" file or GNU official website(https://www.gnu.org/licenses/gpl-3.0.en.html).

// standard library
#include <string>
#include <iostream>
#include <fstream>
#include <locale>
#include <cstddef>
#include <algorithm>
#include <iterator>
#include <utility>
#include <vector>

// boost
#include <boost/format.hpp>
#include <boost/filesystem.hpp>

// header
#include "setting.h"
#include "exception.h"
#include "constant.h"

// using
using namespace std;
using namespace boost;
using namespace boost::filesystem;

void dfs_backupper::setting::open(const wstring& setting_name, SettingType type)
{
	switch(type)
	{
	case SettingType::DIRECTORY:
		FromSettingFilename	= (wformat{L".%1%settings%1%%2%%1%DIR_FROM"} % PATH_BREAK_CHARACTER % setting_name).str();
		ToSettingFilename	= (wformat{L".%1%settings%1%%2%%1%DIR_TO"} % PATH_BREAK_CHARACTER % setting_name).str();
		break;

	case SettingType::FILE:
		FromSettingFilename	= (wformat{L".%1%settings%1%%2%%1%FILE_FROM"} % PATH_BREAK_CHARACTER % setting_name).str();
		ToSettingFilename	= (wformat{L".%1%settings%1%%2%%1%FILE_TO"} % PATH_BREAK_CHARACTER % setting_name).str();
		break;
	}
}

void dfs_backupper::setting::clear()
{
	const auto SettingDirectory = wpath{FromSettingFilename}.parent_path();
	if(!is_directory(SettingDirectory)) // Create setting-directory If It's not exists
	{
		try
		{
			create_directory(SettingDirectory);
		}
		catch(...)
		{
			throw dfs_backupper::exception((wformat{L"failed create a directory \"%1%\""} % SettingDirectory.wstring()).str());
		}
	}

	// Clear from-setting-file
	std::wofstream FromFile{FromSettingFilename};
	if(FromFile.fail())
		throw dfs_backupper::exception((wformat{L"failed clear a file \"%1%\""} % FromSettingFilename).str());

	// Clear to-setting-file
	std::wofstream ToFile{ToSettingFilename};
	if(ToFile.fail())
		throw dfs_backupper::exception((wformat{L"failed clear a file \"%1%\""} % ToSettingFilename).str());

	BackupFilePairs.clear();
}

void dfs_backupper::setting::list() const
{
	for(const auto& BackupFilePair: BackupFilePairs)
		wcout << wformat{L"%1% -> %2%"} % BackupFilePair.first % BackupFilePair.second << endl;
}

void dfs_backupper::setting::add(const wstring& SourceSettingFilename, const wstring& DestSettingFilename)
{
	const auto BackupFilePair = make_pair(SourceSettingFilename, DestSettingFilename);
	const auto BackupFilePairsEnd = end(BackupFilePairs);
	if(find(begin(BackupFilePairs), BackupFilePairsEnd, BackupFilePair) != BackupFilePairsEnd) // exists same setting
		throw dfs_backupper::exception{L"exists same setting"};

	BackupFilePairs.push_back(BackupFilePair);
	write();
}

void dfs_backupper::setting::write() const
{
	// Open from-setting-file
	std::wofstream FromSettingFile;
	FromSettingFile.imbue(locale{""});
	FromSettingFile.open(FromSettingFilename);
	if(FromSettingFile.fail())
		throw dfs_backupper::exception((wformat{L"failed open file \"%1%\""} % FromSettingFilename).str());

	// Open to-setting-file
	std::wofstream ToSettingFile;
	ToSettingFile.imbue(locale{""});
	ToSettingFile.open(ToSettingFilename);
	if(ToSettingFile.fail())
		throw dfs_backupper::exception((wformat{L"failed open file \"%1%\""} % ToSettingFilename).str());

	for(const auto& BackupFilePair: BackupFilePairs)
	{
		FromSettingFile << BackupFilePair.first << endl;	// Write from-setting
		ToSettingFile << BackupFilePair.second << endl;		// Write to-setting
	}
}

void dfs_backupper::setting::read()
{
	// Open from-setting-file
	std::wifstream FromSettingFile;
	FromSettingFile.imbue(locale{""});
	FromSettingFile.open(FromSettingFilename);
	if(FromSettingFile.fail())
		throw dfs_backupper::exception((wformat{L"failed open file \"%1%\""} % FromSettingFilename).str());

	// Open to-setting-file
	std::wifstream ToSettingFile;
	ToSettingFile.imbue(locale{""});
	ToSettingFile.open(ToSettingFilename);
	if(ToSettingFile.fail())
		throw dfs_backupper::exception((wformat{L"failed open file \"%1%\""} % ToSettingFilename).str());

	while(true)
	{
		wstring FromSetting;
		wstring ToSetting;

		if(!getline(FromSettingFile, FromSetting))	// Read a from-setting
			break;

		if(!getline(ToSettingFile, ToSetting))		// Read a to-setting
			break;

		BackupFilePairs.push_back(make_pair(FromSetting, ToSetting));
	}
}

void dfs_backupper::setting::remove(const wstring& from, const wstring& to)
{
	const auto i = find(begin(BackupFilePairs), end(BackupFilePairs), make_pair(from, to));
	if(i == BackupFilePairs.end())	// not found
		throw dfs_backupper::exception{L"not found the setting"};

	// Remove
	if(BackupFilePairs.erase(i) == end(BackupFilePairs)) // failed
		throw dfs_backupper::exception{L"failed remove"};

	write();
}
