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
	size_t element_number = from_vector.size();
	for(unsigned int i = 0; i < element_number; i++)
		copy_directory(from_vector[i], to_vector[i], overwrite_if_exists);
}
