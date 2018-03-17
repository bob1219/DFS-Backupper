#ifndef DIR_SETTING_H
#define DIR_SETTING_H

// standard library
#include <string>

// header
#include "constant.h"
#include "setting.h"

namespace dfs_backupper
{
	class DirSetting : public setting
	{
	public:
		DirSetting(const std::wstring& setting_name) { open(setting_name, SettingType::DIRECTORY); }
		DirSetting(const DirSetting&) = default;
		DirSetting(DirSetting&&) = default;

		DirSetting& operator=(const DirSetting&) = default;
		DirSetting& operator=(DirSetting&&) = default;

		void run() const override;
	};
}

#endif
