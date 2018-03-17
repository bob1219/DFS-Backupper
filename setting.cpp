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
	const auto FromSettingFile_ParentPath = wpath{FromSettingFilename}.parent_path();
	if(!is_directory(FromSettingFile_ParentPath))
	{
		try
		{
			create_directory(FromSettingFile_ParentPath);
		}
		catch(...)
		{
			throw dfs_backupper::exception((wformat{L"failed create a directory \"%1%\""} % FromSettingFile_ParentPath).str());
		}
	}

	std::wofstream FromFile{FromSettingFilename};
	if(FromFile.fail())
		throw dfs_backupper::exception((wformat{L"failed clear a file \"%1%\""} % FromSettingFilename).str());

	const auto ToSettingFile_ParentPath = wpath{ToSettingFilename}.parent_path();
	if(!is_directory(ToSettingFile_ParentPath))
	{
		try
		{
			create_directory(ToSettingFile_ParentPath);
		}
		catch(...)
		{
			throw dfs_backupper::exception((wformat{L"failed create a directory \"%1%\""} % ToSettingFile_ParentPath).str());
		}
	}

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

void dfs_backupper::setting::add(const wstring& FromSettingFilename, const wstring& ToSettingFilename)
{
	const auto BackupFilePair = make_pair(FromSettingFilename, ToSettingFilename);
	if(find(BackupFilePairs.begin(), BackupFilePairs.end(), BackupFilePair) != BackupFilePairs.end()) // exists same setting
		throw dfs_backupper::exception{L"exists same setting"};

	BackupFilePairs.push_back(BackupFilePair);
	write();
}

void dfs_backupper::setting::write() const
{
	std::wofstream FromSettingFile;
	FromSettingFile.imbue(locale{""});
	FromSettingFile.open(FromSettingFilename);
	if(FromSettingFile.fail())
		throw dfs_backupper::exception((wformat{L"failed open file \"%1%\""} % FromSettingFilename).str());

	std::wofstream ToSettingFile;
	ToSettingFile.imbue(locale{""});
	ToSettingFile.open(ToSettingFilename);
	if(ToSettingFile.fail())
		throw dfs_backupper::exception((wformat{L"failed open file \"%1%\""} % ToSettingFilename).str());

	for(const auto& BackupFilePair: BackupFilePairs)
	{
		FromSettingFile << BackupFilePair.first << endl;
		ToSettingFile << BackupFilePair.second << endl;
	}
}

void dfs_backupper::setting::read()
{
	std::wifstream FromSettingFile;
	FromSettingFile.imbue(locale{""});
	FromSettingFile.open(FromSettingFilename);
	if(FromSettingFile.fail())
		throw dfs_backupper::exception((wformat{L"failed open file \"%1%\""} % FromSettingFilename).str());

	std::wifstream ToSettingFile;
	ToSettingFile.imbue(locale{""});
	ToSettingFile.open(ToSettingFilename);
	if(ToSettingFile.fail())
		throw dfs_backupper::exception((wformat{L"failed open file \"%1%\""} % ToSettingFilename).str());

	while(true)
	{
		wstring FromSetting;
		wstring ToSetting;

		if(!getline(FromSettingFile, FromSetting))
			break;

		if(!getline(ToSettingFile, ToSetting))
			break;

		BackupFilePairs.push_back(make_pair(FromSetting, ToSetting));
	}
}

void dfs_backupper::setting::remove(const wstring& from, const wstring& to)
{
	auto i = find(BackupFilePairs.begin(), BackupFilePairs.end(), make_pair(from, to));
	if(i == BackupFilePairs.end())
		throw dfs_backupper::exception{L"not found the setting"};

	if(BackupFilePairs.erase(i) == BackupFilePairs.end())
		throw dfs_backupper::exception{L"failed remove"};

	write();
}
