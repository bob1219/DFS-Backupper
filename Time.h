#ifndef TIME_H
#define TIME_H

// standard library
#include <ctime>

namespace dfs_backupper
{
	class Time
	{
	public:
		Time() { update(); }
		Time(const Time&) = default;
		Time(Time&&) = default;
		Time(std::time_t _time) : time{_time} {}

		Time& operator=(const Time&) = default;
		Time& operator=(Time&&) = default;

		std::time_t get() const noexcept { return time; }
		int year() const noexcept { return data->tm_year + 1900; }
		int month() const noexcept { return data->tm_mon + 1; }
		int day() const noexcept { return data->tm_mday; }
		int hour() const noexcept { return data->tm_hour; }
		int min() const noexcept { return data->tm_min; }
		int sec() const noexcept { return data->tm_sec; }
		void update() noexcept { time = std::time(nullptr); data = std::localtime(&time); }

	private:
		std::time_t time;
		tm* data;
	};

	inline bool operator >(const Time& left, const Time& right) noexcept
	{
		return std::difftime(left.get(), right.get()) > 0;
	}

	inline bool operator <(const Time& left, const Time& right) noexcept
	{
		return std::difftime(left.get(), right.get()) < 0;
	}

	inline bool operator ==(const Time& left, const Time& right) noexcept
	{
		return std::difftime(left.get(), right.get()) == 0;
	}

	inline bool operator !=(const Time& left, const Time& right) noexcept
	{
		return !(left == right);
	}

	inline bool operator >=(const Time& left, const Time& right) noexcept
	{
		return (left > right) || (left == right);
	}

	inline bool operator <=(const Time& left, const Time& right) noexcept
	{
		return (left < right) || (left == right);
	}
}

#endif
