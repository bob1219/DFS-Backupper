// standard library
#include <vector>
#include <string>
#include <iostream>

// header
#include "function.h"
#include "class.h"

// using
using namespace std;

bool dfs_backupper::CommandProcess(int argc, const vector<wstring>& args)
{
	if(args[1] == L"clear")
	{
		if(argc != 2)
			return false;
		return command::clear();
	}
	else if(args[1] == L"list")
	{
		if(argc != 2)
			return false;
		return command::list();
	}
	else if(args[1] == L"add")
	{
		if(argc != 5)
			return false;
		return command::add(args[2], args[3], args[4]);
	}
	else if(args[1] == L"run")
	{
		if(argc != 2)
			return false;
		return command::run();
	}
	else throw dfs_backupper::exception(L"unknown command");
}
