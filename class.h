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
		setting(SettingFile FromSettingFile, SettingFile ToSettingFile);
		bool isOpen() { return _isOpen; }
		bool clear();
		void list();
		void add(const std::wstring& from, const std::wstring& to);
		virtual void run() = 0;

	protected:
		wstring FromSettingFilename;
		wstring ToSettingFilename;
		std::vector<std::wstring> FromFiles;
		std::vector<std::wstring> ToFiles;
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
		const std::wstring& getMessage() { return message; }

	private:
		std::wstring message;
	};
}

#endif
