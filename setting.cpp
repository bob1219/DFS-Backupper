// Copyright 2018 Daiki Yoshida. All rights reserved.
//
// This file is part of DFS-Backupper.
//
// DFS-Backupper is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// DFS-Backupper is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with DFS-Backupper. If not, see <http://www.gnu.org/license/>.

// standard library
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>

// boost
#include <boost/format.hpp>
#include <boost/filesystem.hpp>

// header
#include "setting.h"
#include "exception.h"
#include "constant.h"
#include "LogFile.h"

// using
using namespace std;
using namespace boost;
using namespace boost::filesystem;

void dfs_backupper::setting::open(const wstring& setting_name, SettingType type)
{
	switch(type)
	{
	case SettingType::DIRECTORY:
		SourceSettingFilename	= (wformat{L".%1%settings%1%%2%%1%DIR_SOURCE"} % PATH_BREAK_CHARACTER % setting_name).str();
		DestSettingFilename	= (wformat{L".%1%settings%1%%2%%1%DIR_DEST"} % PATH_BREAK_CHARACTER % setting_name).str();
		break;

	case SettingType::FILE:
		SourceSettingFilename	= (wformat{L".%1%settings%1%%2%%1%FILE_SOURCE"} % PATH_BREAK_CHARACTER % setting_name).str();
		DestSettingFilename	= (wformat{L".%1%settings%1%%2%%1%FILE_DEST"} % PATH_BREAK_CHARACTER % setting_name).str();
		break;
	}
}

void dfs_backupper::setting::base_clear(LogFile& log, SettingType type)
{
	const auto SettingDirectory{wpath{SourceSettingFilename}.parent_path()};
	if(!is_directory(SettingDirectory))
	{
		try
		{
			create_directory(SettingDirectory);
		}
		catch(...)
		{
			wstring SettingDirectoryName{SettingDirectory.wstring()};
			log.write(L"error: failed create setting directory");
			throw dfs_backupper::exception{L"failed create setting directory"};
		}
	}

	std::wofstream SourceSettingFile{SourceSettingFilename};
	if(SourceSettingFile.fail())
	{
		log.write((wformat{L"error: failed clear source-setting-file of %1%"} % ((type == SettingType::DIRECTORY) ? L"directory-setting" : L"file-setting")).str());
		throw dfs_backupper::exception{(wformat{L"failed clear source-setting-file of %1%"} % ((type == SettingType::DIRECTORY) ? L"directory-setting" : L"file-setting")).str()};
	}

	std::wofstream DestSettingFile{DestSettingFilename};
	if(DestSettingFile.fail())
	{
		log.write((wformat{L"error: failed clear destination-setting-file of %1%"} % ((type == SettingType::DIRECTORY) ? L"directory-setting" : L"file-setting")).str());
		throw dfs_backupper::exception{(wformat{L"failed clear destination-setting-file of %1%"} % ((type == SettingType::DIRECTORY) ? L"directory-setting" : L"file-setting")).str()};
	}

	BackupFilePairs.clear();

	log.write((wformat{L"successful clear settings of %1%"} % ((type == SettingType::DIRECTORY) ? L"directory-setting" : L"file-setting")).str());
}

void dfs_backupper::setting::list() const
{
	for(const auto& BackupFilePair: BackupFilePairs)
		wcout << wformat{L"%1% -> %2%"} % BackupFilePair.first % BackupFilePair.second << endl;
}

void dfs_backupper::setting::base_add(const wstring& SourceSettingFilename, const wstring& DestSettingFilename, LogFile& log, SettingType type)
{
	// Check exists same setting
	const auto BackupFilePair{make_pair(SourceSettingFilename, DestSettingFilename)};
	const auto BackupFilePairsEnd{end(BackupFilePairs)};
	if(find(begin(BackupFilePairs), BackupFilePairsEnd, BackupFilePair) != BackupFilePairsEnd)
	{
		log.write(L"error: exists same setting");
		throw dfs_backupper::exception{L"exists same setting"};
	}

	BackupFilePairs.push_back(BackupFilePair);
	write(log, type);

	log.write((wformat{L"successful addition a %1% setting"} % ((type == SettingType::DIRECTORY) ? L"directory" : L"file")).str());
}

void dfs_backupper::setting::write(LogFile& log, SettingType type) const
{
	// Open source-setting-file
	std::wofstream SourceSettingFile;
	SourceSettingFile.imbue(locale{""});
	SourceSettingFile.open(SourceSettingFilename);
	if(SourceSettingFile.fail())
	{
		log.write((wformat{L"error: failed open source-setting-file of %1%"} % ((type == SettingType::DIRECTORY) ? L"directory-setting" : L"file-setting")).str());
		throw dfs_backupper::exception{(wformat{L"failed open source-setting-file of %1%"} % ((type == SettingType::DIRECTORY) ? L"directory-setting" : L"file-setting")).str()};
	}

	// Open dest-setting-file
	std::wofstream DestSettingFile;
	DestSettingFile.imbue(locale{""});
	DestSettingFile.open(DestSettingFilename);
	if(DestSettingFile.fail())
	{
		log.write((wformat{L"error: failed open destination-setting-file of %1%"} % ((type == SettingType::DIRECTORY) ? L"directory-setting" : L"file-setting")).str());
		throw dfs_backupper::exception{(wformat{L"failed open destination-setting-file of %1%"} % ((type == SettingType::DIRECTORY) ? L"directory-setting" : L"file-setting")).str()};
	}

	for(const auto& BackupFilePair: BackupFilePairs)
	{
		SourceSettingFile << BackupFilePair.first << endl;	// Write source-settings
		DestSettingFile << BackupFilePair.second << endl;	// Write dest-settings
	}

	log.write((wformat{L"successful wrote %1% settings to setting file"} % ((type == SettingType::DIRECTORY) ? L"directory" : L"file")).str());
}

void dfs_backupper::setting::base_read(LogFile& log, SettingType type)
{
	// Open source-setting-file
	std::wifstream SourceSettingFile;
	SourceSettingFile.imbue(locale{""});
	SourceSettingFile.open(SourceSettingFilename);
	if(SourceSettingFile.fail())
	{
		log.write((wformat{L"error: failed open source-setting-file of %1%"} % ((type == SettingType::DIRECTORY) ? L"directory-setting" : L"file-setting")).str());
		throw dfs_backupper::exception{(wformat{L"failed open source-setting-file of %1%"} % ((type == SettingType::DIRECTORY) ? L"directory-setting" : L"file-setting")).str()};
	}

	// Open dest-setting-file
	std::wifstream DestSettingFile;
	DestSettingFile.imbue(locale{""});
	DestSettingFile.open(DestSettingFilename);
	if(DestSettingFile.fail())
	{
		log.write((wformat{L"error: failed open destination-setting-file of %1%"} % ((type == SettingType::DIRECTORY) ? L"directory-setting" : L"file-setting")).str());
		throw dfs_backupper::exception{(wformat{L"failed open destination-setting-file of %1%"} % ((type == SettingType::DIRECTORY) ? L"directory-setting" : L"file-setting")).str()};
	}

	while(true)
	{
		wstring SourceSetting;
		wstring DestSetting;

		if(!getline(SourceSettingFile, SourceSetting))
			break;

		if(!getline(DestSettingFile, DestSetting))
			break;

		BackupFilePairs.push_back(make_pair(SourceSetting, DestSetting));
	}

	log.write((wformat{L"successful read %1% settings"} % ((type == SettingType::DIRECTORY) ? L"directory" : L"file")).str());
}

void dfs_backupper::setting::base_remove(const wstring& source, const wstring& dest, LogFile& log, SettingType type)
{
	const auto EndOfBackupFilePairs{end(BackupFilePairs)};
	const auto i{find(begin(BackupFilePairs), EndOfBackupFilePairs, make_pair(source, dest))};
	if(i == EndOfBackupFilePairs) // not found
	{
		log.write(L"error: not found the setting");
		throw dfs_backupper::exception{L"not found the setting"};
	}

	// Remove
	if(BackupFilePairs.erase(i) == EndOfBackupFilePairs) // failed
	{
		log.write(L"error: failed remove a setting");
		throw dfs_backupper::exception{L"failed remove a setting"};
	}

	write(log, type);
}
