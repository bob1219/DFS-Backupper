#ifndef _CLASS_H_
#define _CLASS_H_

// standard library
#include <string>
#include <vector>

// header
#include "constant.h"

namespace dfs-backupper
{
	class setting
	{
	public:
		setting(SettingFile from, SettingFile to);
		bool isOpen();
		bool clear();
		void list();
		bool add(const std::wstring& from, const std::wstring& to);
		void run();

	private:
		std::vector<std::wstring> from_vector;
		std::vector<std::wstring> to_vector;
		bool _isOpen;
		bool write();
	};

	class exception
	{
	public:
		exception(const std::wstring& message);
		const std::wstring& getMessage();

	private:
		std::wstring message;
	}
}

#endif
