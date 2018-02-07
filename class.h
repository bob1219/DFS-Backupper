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
		setting(SettingFile _from, SettingFile _to);
		bool isOpen() { return _isOpen; }
		bool clear();
		void list();
		void add(const std::wstring& from, const std::wstring& to);
		virtual void run() = 0;

	protected:
		wstring from;
		wstring to;
		std::vector<std::wstring> from_vector;
		std::vector<std::wstring> to_vector;
		bool _isOpen;
		bool write();
	};

	class DirSetting : public setting
	{
	public:
		void run();
	}

	class FileSetting : public setting
	{
	public:
		void run();
	}

	class exception
	{
	public:
		exception(const std::wstring& message);
		const std::wstring& getMessage();

	private:
		std::wstring message;
	};
}

#endif
