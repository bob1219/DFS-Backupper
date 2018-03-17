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
	auto to = _to;
	if(*(to.end() - 1) == PATH_BREAK_CHARACTER)
		to = to.substr(0, to.size() - 1);

	auto from = _from;
	if(*(from.end() - 1) == PATH_BREAK_CHARACTER)
		from = from.substr(0, from.size() - 1);

	if(!is_directory(to))
		create_directories(to);

	unordered_set<wstring> FromDirectoryFiles;
	for_each(directory_iterator{from}, directory_iterator{}, [&](const auto& p){ FromDirectoryFiles.insert(p.filename().wstring()); });
	for_each(directory_iterator{to}, directory_iterator{}, [&](const auto& p)
	{
		if(FromDirectoryFiles.find(p.filename().wstring()) == FromDirectoryFiles.end())
			remove(p);
		else if(is_directory(p))
			dfs_backupper::copy_directory(from + PATH_BREAK_CHARACTER + p.filename().wstring(), p);
		else
			dfs_backupper::copy_file(from + PATH_BREAK_CHARACTER + p.filename().wstring(), p);
	});
}
