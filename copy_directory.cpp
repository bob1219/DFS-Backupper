// standard library
#include <string>
#include <algorithm>
#include <unordered_set>

// boost
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <boost/format.hpp>

// header
#include "function.h"
#include "constant.h"

// using
using namespace std;
using namespace boost::filesystem;
using namespace boost;

void dfs_backupper::copy_directory(const wstring& _from, const wstring& _to)
{
	// Remove last character of to-filename If it's path-break-character
	auto to = _to;
	if(*(to.end() - 1) == PATH_BREAK_CHARACTER)
		to = to.substr(0, to.size() - 1);

	// Remove last character of from-filename If it's path-break-character
	auto from = _from;
	if(*(from.end() - 1) == PATH_BREAK_CHARACTER)
		from = from.substr(0, from.size() - 1);

	// Create to-directory If it's not exists
	if(!is_directory(to))
		create_directories(to);

	// Remove not exists in from-directory files on to-directiry
	unordered_set<wstring> FromDirectoryFiles;
	for_each(directory_iterator{from}, directory_iterator{}, [&](const wpath& p){ FromDirectoryFiles.insert(p.filename().wstring()); });
	for_each(directory_iterator{to}, directory_iterator{}, [&](const wpath& p)
	{
		if(FromDirectoryFiles.find(p.filename().wstring()) == FromDirectoryFiles.end())
			remove(p);
	});

	// Copy other files
	for(const auto& FromDirectoryFile: FromDirectoryFiles)
		dfs_backupper::copy_file(from + PATH_BREAK_CHARACTER + FromDirectoryFile, to + PATH_BREAK_CHARACTER + FromDirectoryFile);
}
