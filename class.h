#ifndef CLASS_H
#define CLASS_H

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
		void open(const std::wstring& setting_name, SettingType type);
		void read();
		void clear();
		void list() const;
		void add(const std::wstring& from, const std::wstring& to);
		void remove(const std::wstring& from, const std::wstring& to);
		virtual void run() const = 0;

	private:
		std::wstring FromSettingFilename;
		std::wstring ToSettingFilename;
		void write() const;

	protected:
		std::vector<std::wstring> FromFiles;
		std::vector<std::wstring> ToFiles;
	};

	class DirSetting : public setting
	{
	public:
		DirSetting(const std::wstring& setting_name);
		void run() const;
	};

	class FileSetting : public setting
	{
	public:
		FileSetting(const std::wstring& setting_name);
		void run() const;
	};

	class exception
	{
	public:
		exception(const std::wstring& _message);
		std::wstring getMessage() const { return message; }

	private:
		std::wstring message;
	};
}

#endif
