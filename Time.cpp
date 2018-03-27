// boost
#include <boost/logic/tribool.hpp>

// header
#include "Time.h"

// using
using namespace boost::logic;

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
