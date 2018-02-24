// standard library
#include <vector>
#include <string>

// header
#include "function.h"
#include "class.h"

// using
using namespace std;

void dfs_backupper::CommandProcess(const vector<wstring>& args)
{
	if(args.at(1) == L"clear")
	{
		if(args.size() != 3)
			throw dfs_backupper::exception(L"arguments is few or many");
		command::clear(args.at(2));
	}
	else if(args.at(1) == L"list")
	{
		if(args.size() != 3)
			throw dfs_backupper::exception(L"arguments is few or many");
		command::list(args.at(2));
	}
	else if(args.at(1) == L"add")
	{
		if(args.size() != 6)
			throw dfs_backupper::exception(L"arguments is few or many");
		command::add(args.at(2), args.at(3), args.at(4), args.at(5));
	}
	else if(args.at(1) == L"run")
	{
		if(args.size() != 3)
			throw dfs_backupper::exception(L"arguments is few or many");
		command::run(args.at(2));
	}
	else if(args.at(1) == L"remove")
	{
		if(args.size() != 6)
			throw dfs_backupper::exception(L"arguments is few or many");
		command::remove(args.at(2), args.at(3), args.at(4), args.at(5));
	}
	else throw dfs_backupper::exception(L"unknown command");
}
