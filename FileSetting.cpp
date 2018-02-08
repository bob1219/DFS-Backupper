// standard library
#include <cstddef>

// boost
#include <boost/filesystem.hpp>

// header
#include "class.h"

// using
using namespace std;

void dfs-backupper::FileSetting::run()
{
	size_t element_number = FromFiles.size();
	for(unsigned int i = 0; i < element_number; i++)
		copy_directory(FromFiles[i], ToFiles[i], overwrite_if_exists);
}
