#ifndef EXCEPTION_H
#define EXCEPTION_H

// standard library
#include <string>

namespace dfs_backupper
{
	class exception
	{
	public:
		exception(const std::wstring& _message) : message{_message} {}
		std::wstring getMessage() { return message; }

	private:
		std::wstring message;
	};
}

#endif
