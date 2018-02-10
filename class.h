#ifndef _CLASS_H_
#define _CLASS_H_

// standard library
#include <string>
#include <vector>

// header
#include "constant.h"

namespace dfs_backupper
{
	class setting
	{
	public:
		void open(SettingFile FromSettingFile, SettingFile ToSettingFile);
		bool isOpen() { return _isOpen; }
		bool clear();
		void list();
		void add(const std::wstring& from, const std::wstring& to);
		virtual void run() = 0;

	private:
		std::wstring FromSettingFilename;
		std::wstring ToSettingFilename;
		bool _isOpen;
		bool write();

	protected:
		std::vector<std::wstring> FromFiles;
		std::vector<std::wstring> ToFiles;
	};

	class DirSetting : public setting
	{
	public:
		DirSetting(SettingFile FromSettingFile, SettingFile ToSettingFile);
		void run();
	};

	class FileSetting : public setting
	{
	public:
		FileSetting(SettingFile FromSettingFile, SettingFile ToSettingFile);
		void run();
	};

	class exception
	{
	public:
		exception(const std::wstring& _message);
		const std::wstring& getMessage() { return message; }

	private:
		std::wstring message;
	};
}

#endif
