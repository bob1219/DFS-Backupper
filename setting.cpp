// standard library
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <locale>
#include <cstddef>

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

void dfs_backupper::setting::open(const wstring& setting_name, SettingFile FromSettingFile, SettingFile ToSettingFile)
{
	// read FromSettingFile setting file
	switch(FromSettingFile)
	{
	case DIR_FROM:
		FromSettingFilename = (wformat(L".%1%settings%1%%2%%1%DIR_FROM") % PATH_BREAK_CHARACTER % setting_name).str();
		break;

	case DIR_TO:
		FromSettingFilename = (wformat(L".%1%settings%1%%2%%1%DIR_TO") % PATH_BREAK_CHARACTER % setting_name).str();
		break;

	case FILE_FROM:
		FromSettingFilename = (wformat(L".%1%settings%1%%2%%1%FILE_FROM") % PATH_BREAK_CHARACTER % setting_name).str();
		break;

	case FILE_TO:
		FromSettingFilename = (wformat(L".%1%settings%1%%2%%1%FILE_TO") % PATH_BREAK_CHARACTER % setting_name).str();
		break;
	}

	// read ToSettingFile_ifs setting file
	switch(ToSettingFile)
	{
	case DIR_FROM:
		ToSettingFilename = (wformat(L".%1%settings%1%%2%%1%DIR_FROM") % PATH_BREAK_CHARACTER % setting_name).str();
		break;

	case DIR_TO:
		ToSettingFilename = (wformat(L".%1%settings%1%%2%%1%DIR_TO") % PATH_BREAK_CHARACTER % setting_name).str();
		break;

	case FILE_FROM:
		ToSettingFilename = (wformat(L".%1%settings%1%%2%%1%FILE_FROM") % PATH_BREAK_CHARACTER % setting_name).str();
		break;

	case FILE_TO:
		ToSettingFilename = (wformat(L".%1%settings%1%%2%%1%FILE_TO") % PATH_BREAK_CHARACTER % setting_name).str();
		break;
	}
}

bool dfs_backupper::setting::clear()
{
	const path FromSettingFile_ParentPath = path(FromSettingFilename).parent_path();
	if(!is_directory(FromSettingFile_ParentPath))
	{
		try
		{
			create_directory(FromSettingFile_ParentPath);
		}
		catch(...)
		{
			return false;
		}
	}

	std::wofstream FromFile(FromSettingFilename);
	if(FromFile.fail())
		return false;

	const path ToSettingFile_ParentPath = path(ToSettingFilename).parent_path();
	if(!is_directory(ToSettingFile_ParentPath))
	{
		try
		{
			create_directory(ToSettingFile_ParentPath);
		}
		catch(...)
		{
			return false;
		}
	}

	std::wofstream ToFile(ToSettingFilename);
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
		wcout << wformat(L"%1% -> %2%\n") % FromFiles[i] % ToFiles[i];
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
	std::wofstream FromSettingFile;
	FromSettingFile.imbue(locale(""));
	FromSettingFile.open(FromSettingFilename);
	if(FromSettingFile.fail())
		return false;

	std::wofstream ToSettingFile;
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
	std::wifstream FromSettingFile_ifs;
	FromSettingFile_ifs.imbue(locale(""));
	FromSettingFile_ifs.open(FromSettingFilename);
	if(FromSettingFile_ifs.fail())
		return false;

	wstring FromFile;
	while(getline(FromSettingFile_ifs, FromFile))
		FromFiles.push_back(FromFile);

	std::wifstream ToSettingFile_ifs;
	ToSettingFile_ifs.imbue(locale(""));
	ToSettingFile_ifs.open(ToSettingFilename);
	if(ToSettingFile_ifs.fail())
		return false;

	wstring ToFile;
	while(getline(ToSettingFile_ifs, ToFile))
		ToFiles.push_back(ToFile);

	return true;
}
