#ifndef _FUNCTION_H_
#define _FUNCTION_H_

// standard library
#include <vector>
#include <string>

namespace dfs_backupper
{
	bool CommandProcess(int argc, const std::vector<std::wstring>& args);
	void copy_directory(const std::wstring& from, const std::wstring& _to);

	namespace command
	{
		bool clear();
		bool list();
		bool add(const std::wstring& option, const std::wstring& from, const std::wstring& to);
		bool run();
	}
}

#endif
