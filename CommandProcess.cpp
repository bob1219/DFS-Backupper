// standard library
#include <vector>
#include <string>

// header
#include "function.h"
#include "exception.h"

// using
using namespace std;

void dfs_backupper::CommandProcess(const vector<wstring>& args)
{
	auto arg_error = [](){ throw dfs_backupper::exception(L"few or many arguments"); };

	if(args.at(1) == L"clear")
	{
		if(args.size() != 3)
			arg_error();
		command::clear(args.at(2));
	}
	else if(args.at(1) == L"list")
	{
		if(args.size() != 3)
			arg_error();
		command::list(args.at(2));
	}
	else if(args.at(1) == L"add")
	{
		if(args.size() != 6)
			arg_error();
		command::add(args.at(2), args.at(3), args.at(4), args.at(5));
	}
	else if(args.at(1) == L"run")
	{
		if(args.size() != 3)
			arg_error();
		command::run(args.at(2));
	}
	else if(args.at(1) == L"remove")
	{
		if(args.size() != 6)
			arg_error();
		command::remove(args.at(2), args.at(3), args.at(4), args.at(5));
	}
	else throw dfs_backupper::exception(L"unknown command");
}
