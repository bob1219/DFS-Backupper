// standard library
#include <vector>
#include <string>

// header
#include "function.h"
#include "class.h"

// using
using namespace std;

bool dfs_backupper::CommandProcess(int argc, const vector<wstring>& args)
{
	if(args[1] == L"clear")
	{
		if(argc != 3)
			return false;
		return command::clear(args[2]);
	}
	else if(args[1] == L"list")
	{
		if(argc != 3)
			return false;
		return command::list(args[2]);
	}
	else if(args[1] == L"add")
	{
		if(argc != 6)
			return false;
		return command::add(args[2], args[3], args[4], args[4]);
	}
	else if(args[1] == L"run")
	{
		if(argc != 3)
			return false;
		return command::run(args[2]);
	}
	else throw dfs_backupper::exception(L"unknown command");
}
