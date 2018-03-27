// standard library
#include <array>

// boost
#include <boost/logic/tribool.hpp>

// header
#include "Time.h"

// using
using namespace boost::logic;
using namespace std;

tribool dfs_cls::Time::isSummerTime() const
{
	int flag = data->tm_isdst;
	if(flag > 0)
		return true;
	else if(flag == 0)
		return false;
	else
		return indeterminate;
}

dfs_cls::Time::DayOfWeek dfs_cls::Time::getDayOfWeek() const noexcept
{
	constexpr auto NumberOfDaysInWeek = 7;
	array<DayOfWeek, NumberOfDaysInWeek> a;
	for(auto i = 0; i < NumberOfDaysInWeek; ++i)
		a.at(i) = static_cast<DayOfWeek>(i);

	return a.at(data->tm_wday);
}
