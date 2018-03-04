#ifndef FUNCTION_H
#define FUNCTION_H

// standard library
#include <vector>
#include <string>

namespace dfs_backupper
{
	void CommandProcess(const std::vector<std::wstring>& args);
	void copy_directory(const std::wstring& from, const std::wstring& _to);
	void copy_file(const std::wstring& from, const std::wstring& to);

	namespace command
	{
		void clear(const std::wstring& setting_name);
		void list(const std::wstring& setting_name);
		void add(const std::wstring& setting_name, const std::wstring& option, const std::wstring& from, const std::wstring& to);
		void run(const std::wstring& setting_name);
		void remove(const std::wstring& setting_name, const std::wstring& option, const std::wstring& from, const std::wstring& to);
	}
}

#endif
