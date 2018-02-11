// standard library
#include <string>
#include <sstream>
#include <iostream>

// boost
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>

// header
#include "function.h"
#include "constant.h"

// using
using namespace std;
using namespace boost::filesystem;

void dfs_backupper::copy_directory(const wstring& from, const wstring& _to)
{
	wstring to(_to);
	if(to[to.size() - 1] == PATH_BREAK_CHARACTER)
		to = to.substr(0, to.size() - 1);

	if(is_directory(to))
		remove_all(to);
	create_directories(to);

	BOOST_FOREACH(const wpath& p, make_pair(directory_iterator(from), directory_iterator()))
	{
		wstring filename;
		wstring filename_b = p.filename().wstring();
		for(wstring::iterator i = filename_b.begin(); i != filename_b.end(); i++)
			if(*i != L'"')
				filename += *i;

		wostringstream ToFile;
		ToFile	<< to
			<< PATH_BREAK_CHARACTER
			<< filename;

		if(is_regular_file(p))
		{
			try
			{
				copy_file(p, ToFile.str(), copy_option::overwrite_if_exists);
			}
			catch(...)
			{
				wcerr	<< L"failed:\t"
					<< p.wstring()
					<< L" -> "
					<< ToFile
					<< L'\n';
				goto loop_end;
			}
			
			wcout	<< L"succeeded:\t"
				<< p.wstring()
				<< L" -> "
				<< ToFile
				<< L'\n';
		}
		else
			dfs_backupper::copy_directory(p.wstring(), ToFile.str());

	loop_end:
	}
}
