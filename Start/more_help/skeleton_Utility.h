#ifndef UTILITY_H
#define UTILITY_H

/* *** Comments starting with *** (like this one) in this skeleton file are
instructions for you and should be deleted after you have dealt with them.
You must add code to this file to meet the requirements in the project document,
the comments below, and other relevant course content.
*/

#include <string>
#include <exception>

/* *** do not include any headers that are not needed in order for this header file 
to compile correctly by itself */




/* Utility declarations, functions, and classes used by other modules */

// a simple class for error exceptions that inherits from std::exception
class Error : public std::exception {
public:
	Error(const std::string& in_msg = "") :
		msg(in_msg)
		{}
    const char* what() const noexcept override {return msg.c_str();}
private:
	const std::string msg;
};

/* *** add any additional declarations used by more than one of your modules here. 
Do not include anything used by only one module.
You must delete this comment. */

#endif

