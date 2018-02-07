#ifndef _FUNCTION_H_
#define _FUNCTION_H_

// standard library
#include <vector>
#include <string>

namespace dfs-backupper
{
	bool CommandProcess(int argc, const std::vector<std::wstring>& args);

	namespace command
	{
		bool clear();
		bool list();
		bool add(const std::wstring& option, std::wstring& from, std::wstring& to);
		bool run();
	}
}

#endif
