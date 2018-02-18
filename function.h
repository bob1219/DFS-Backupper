#ifndef FUNCTION_H
#define FUNCTION_H

// standard library
#include <vector>
#include <string>

namespace dfs_backupper
{
	bool CommandProcess(const std::vector<std::wstring>& args);
	void copy_directory(const std::wstring& from, const std::wstring& _to);

	namespace command
	{
		bool clear(const std::wstring& setting_name);
		bool list(const std::wstring& setting_name);
		bool add(const std::wstring& setting_name, const std::wstring& option, const std::wstring& from, const std::wstring& to);
		bool run(const std::wstring& setting_name);
		bool remove(const std::wstring& setting_name, const std::wstring& option, const std::wstring& from, const std::wstring& to);
	}
}

#endif
