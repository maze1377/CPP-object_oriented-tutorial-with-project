#ifndef UTILITY_H
#define UTILITY_H

#include <string>

/* Utility functions and classes used by other modules */

// a simple class for error exceptions - msg points to a std::string error message
struct Error
{
	Error(const std::string &in_msg = "") : msg(in_msg)
	{
	}
	const std::string msg;
};

/* *** add any additional declarations used by more than one of your modules here. Do not
include anything used by only one module unless it is truly general purpose. 
You must delete this comment. */

#endif
