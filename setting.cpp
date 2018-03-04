// standard library
#include <string>
#include <iostream>
#include <fstream>
#include <locale>
#include <cstddef>
#include <algorithm>

// boost
#include <boost/format.hpp>
#include <boost/filesystem.hpp>

// header
#include "class.h"
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
		FromSettingFilename	= (wformat(L".%1%settings%1%%2%%1%DIR_FROM") % PATH_BREAK_CHARACTER % setting_name).str();
		ToSettingFilename	= (wformat(L".%1%settings%1%%2%%1%DIR_TO") % PATH_BREAK_CHARACTER % setting_name).str();
		break;

	case SettingType::FILE:
		FromSettingFilename	= (wformat(L".%1%settings%1%%2%%1%FILE_FROM") % PATH_BREAK_CHARACTER % setting_name).str();
		ToSettingFilename	= (wformat(L".%1%settings%1%%2%%1%FILE_TO") % PATH_BREAK_CHARACTER % setting_name).str();
		break;
	}
}

void dfs_backupper::setting::clear()
{
	const wpath FromSettingFile_ParentPath = wpath(FromSettingFilename).parent_path();
	if(!is_directory(FromSettingFile_ParentPath))
	{
		try
		{
			create_directory(FromSettingFile_ParentPath);
		}
		catch(...)
		{
			throw dfs_backupper::exception(
							(wformat(L"failed create a directory \"%1%\"") % FromSettingFile_ParentPath).str()
			);
		}
	}

	std::wofstream FromFile(FromSettingFilename);
	if(FromFile.fail())
		throw dfs_backupper::exception(
						(wformat(L"failed clear a file \"%1%\"") % FromSettingFilename).str()
		);

	const wpath ToSettingFile_ParentPath = wpath(ToSettingFilename).parent_path();
	if(!is_directory(ToSettingFile_ParentPath))
	{
		try
		{
			create_directory(ToSettingFile_ParentPath);
		}
		catch(...)
		{
			throw dfs_backupper::exception(
							(wformat(L"failed create a directory \"%1%\"") % ToSettingFile_ParentPath).str()
			);
		}
	}

	std::wofstream ToFile(ToSettingFilename);
	if(ToFile.fail())
		throw dfs_backupper::exception(
						(wformat(L"failed clear a file \"%1%\"") % ToSettingFilename).str()
		);

	FromFiles.clear();
	ToFiles.clear();
}

void dfs_backupper::setting::list() const
{
	const size_t element_number = FromFiles.size();
	for(unsigned int i = 0; i < element_number; ++i)
		wcout << wformat(L"%1% -> %2%") % FromFiles.at(i) % ToFiles.at(i) << endl;
}

void dfs_backupper::setting::add(const wstring& FromSettingFilename, const wstring& ToSettingFilename)
{
	vector<wstring>::iterator from_it	= find(FromFiles.begin(), FromFiles.end(), FromSettingFilename);
	vector<wstring>::iterator to_it		= find(ToFiles.begin(), ToFiles.end(), ToSettingFilename);
	if(from_it != FromFiles.end() && to_it != ToFiles.end() && (from_it - FromFiles.begin()) == (to_it - ToFiles.begin())) // exists same setting
		throw dfs_backupper::exception(L"exists same setting");

	FromFiles.push_back(FromSettingFilename);
	ToFiles.push_back(ToSettingFilename);

	write();
}

void dfs_backupper::setting::write() const
{
	std::wofstream FromSettingFile;
	FromSettingFile.imbue(locale(""));
	FromSettingFile.open(FromSettingFilename);
	if(FromSettingFile.fail())
		throw dfs_backupper::exception(
						(wformat(L"failed open file \"%1%\"") % FromSettingFilename).str()
		);

	std::wofstream ToSettingFile;
	ToSettingFile.imbue(locale(""));
	ToSettingFile.open(ToSettingFilename);
	if(ToSettingFile.fail())
		throw dfs_backupper::exception(
						(wformat(L"failed open file \"%1%\"") % ToSettingFilename).str()
		);

	for(wstring setting: FromFiles)
		FromSettingFile << setting << L'\n';

	for(wstring setting: ToFiles)
		ToSettingFile << setting << L'\n';
}

void dfs_backupper::setting::read()
{
	std::wifstream FromSettingFile_ifs;
	FromSettingFile_ifs.imbue(locale(""));
	FromSettingFile_ifs.open(FromSettingFilename);
	if(FromSettingFile_ifs.fail())
		throw dfs_backupper::exception(
						(wformat(L"failed open file \"%1%\"") % FromSettingFilename).str()
		);

	wstring FromFile;
	while(getline(FromSettingFile_ifs, FromFile))
		FromFiles.push_back(FromFile);

	std::wifstream ToSettingFile_ifs;
	ToSettingFile_ifs.imbue(locale(""));
	ToSettingFile_ifs.open(ToSettingFilename);
	if(ToSettingFile_ifs.fail())
		throw dfs_backupper::exception(
						(wformat(L"failed open file \"%1%\"") % ToSettingFilename).str()
		);

	wstring ToFile;
	while(getline(ToSettingFile_ifs, ToFile))
		ToFiles.push_back(ToFile);
}

void dfs_backupper::setting::remove(const wstring& from, const wstring& to)
{
	vector<wstring>::iterator from_it	= find(FromFiles.begin(), FromFiles.end(), from);
	vector<wstring>::iterator to_it		= find(ToFiles.begin(), ToFiles.end(), to);
	if(from_it == FromFiles.end() || to_it == ToFiles.end())
		throw dfs_backupper::exception(L"not found the setting");

	bool FromFailed	= (FromFiles.erase(from_it) == FromFiles.end());
	bool ToFailed	= (ToFiles.erase(to_it) == ToFiles.end());
	if(FromFailed || ToFailed)
		throw dfs_backupper::exception(L"failed remove");

	write();
}
