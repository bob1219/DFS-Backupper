#ifndef FILE_SETTING_H
#define FILE_SETTING_H

// standard library
#include <string>

// header
#include "constant.h"
#include "setting.h"

namespace dfs_backupper
{
	class FileSetting : public setting
	{
	public:
		FileSetting(const std::wstring& setting_name) { open(setting_name, SettingType::FILE); }
		FileSetting(const FileSetting&) = default;
		FileSetting(FileSetting&&) = default;

		FileSetting& operator=(const FileSetting&) = default;
		FileSetting& operator=(FileSetting&&) = default;

		void run() const override;
	};
}

#endif
