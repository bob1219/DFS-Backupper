// time.h
// Copyright 2018 Daiki Yoshida. All rights reserved.
// This file is a header file in DFS-Backupper project.
// This file and DFS-Backupper project are licensed by GNU-GPL v3.0.
// You can see document of GNU-GPL v3.0 in "LICENSE" file or GNU official website(https://www.gnu.org/licenses/gpl-3.0.en.html).

#ifndef TIME_H
#define TIME_H

// standard library
#include <ctime>

namespace dfs_backupper
{
	class Time
	{
	private:
		std::time_t	time;
		std::tm*	data;

	public:
		// Constructors
		Time() { update(); }
		Time(std::time_t _time) : time{_time}, data{} {}
		Time(std::tm* _data) : time{}, data{_data} {}
		Time(const Time&) = default;
		Time(Time&&) = default;

		// Operators
		Time& operator=(const Time&) = default;
		Time& operator=(Time&&) = default;

		void update() noexcept { time = std::time(nullptr); data = std::localtime(&time); }
		int year() const noexcept { return data->tm_year + 1900; }
		int month() const noexcept { return data->tm_mon + 1; }
		int day() const noexcept { return data->tm_mday; }
		int hour() const noexcept { return data->tm_hour; }
		int min() const noexcept { return data->tm_min; }
		int sec() const noexcept { return data->tm_sec; }
		std::time_t getTime() const noexcept { return time; }
		std::tm* getData() const noexcept { return data; }
	};

	inline bool operator>(const Time& left, const Time& right) { return difftime(left.getTime(), right.getTime()) > 0; }
	inline bool operator<(const Time& left, const Time& right) { return difftime(left.getTime(), right.getTime()) < 0; }
	inline bool operator==(const Time& left, const Time& right) { return difftime(left.getTime(), right.getTime()) == 0; }
	inline bool operator!=(const Time& left, const Time& right) { return !(left == right); }
	inline bool operator>=(const Time& left, const Time& right) { return !(left < right); }
	inline bool operator<=(const Time& left, const Time& right) { return !(left > right); }
}

#endif
