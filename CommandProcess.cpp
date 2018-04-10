// Copyright 2018 Daiki Yoshida. All rights reserved.
//
// This file is part of DFS-Backupper.
//
// DFS-Backupper is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// DFS-Backupper is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with DFS-Backupper. If not, see <http://www.gnu.org/license/>.

// standard library
#include <vector>
#include <string>

// header
#include "function.h"
#include "exception.h"
#include "LogFile.h"

// using
using namespace std;

void dfs_backupper::CommandProcess(const vector<wstring>& args, LogFile& log)
{
	auto arg_error = [](){ throw dfs_backupper::exception{L"few or many arguments"}; };

	if(args.at(1) == L"clear")
	{
		if(args.size() != 3)
			arg_error();
		command::clear(args.at(2), log);
	}
	else if(args.at(1) == L"list")
	{
		if(args.size() != 3)
			arg_error();
		command::list(args.at(2), log);
	}
	else if(args.at(1) == L"add")
	{
		if(args.size() != 6)
			arg_error();
		command::add(args.at(2), args.at(3), args.at(4), args.at(5), log);
	}
	else if(args.at(1) == L"run")
	{
		if(args.size() != 3)
			arg_error();
		command::run(args.at(2), log);
	}
	else if(args.at(1) == L"remove")
	{
		if(args.size() != 6)
			arg_error();
		command::remove(args.at(2), args.at(3), args.at(4), args.at(5), log);
	}
	else throw dfs_backupper::exception{L"unknown command"};
}
