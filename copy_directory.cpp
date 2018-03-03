// standard library
#include <string>
#include <iostream>
#include <algorithm>

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

void dfs_backupper::copy_directory(const wstring& from, const wstring& _to)
{
	wstring to(_to);
	if(*(to.end() - 1) == PATH_BREAK_CHARACTER)
		to = to.substr(0, to.size() - 1);

	if(is_directory(to))
		remove_all(to);
	boost::filesystem::copy_directory(from, to);

	for_each(directory_iterator(from), directory_iterator(), [&](const wpath& p)
	{
		const wstring filename(p.filename().wstring());
		const wstring ToFile((wformat(L"%1%%2%%3%") % to % PATH_BREAK_CHARACTER % filename).str());

		if(is_regular_file(p))
		{
			try
			{
				copy_file(p, ToFile, copy_option::overwrite_if_exists);
			}
			catch(...)
			{
				wcerr << wformat(L"failed:\t\t%1% -> %2%\n") % p.wstring() % ToFile;
				goto loop_end;
			}
			
			wcout << wformat(L"succeeded:\t%1% -> %2%\n") % p.wstring() % ToFile;
		}
		else dfs_backupper::copy_directory(p.wstring(), ToFile);

	loop_end:;
	});
}
