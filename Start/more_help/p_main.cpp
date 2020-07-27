/*
Main module. Your project must use this file as-is
*/


#include "Model.h"
#include "Controller.h"

#include <iostream>
#include <exception>

using namespace std;

// The main function creates the Model and Controller objects, 
// then tells the Controller to run. 

int main ()
{	
	// Set output to show two decimal places for floating point numbers
//	cout << fixed << setprecision(2) << endl;
	cout.setf(ios::fixed, ios::floatfield);
	cout.precision(2);

	try {
        // create a Model object
        g_Model_ptr = new Model;
		// create the Controller object and go
		Controller controller;
		controller.run();
		}
	catch(std::exception& error) {
		cout << "Other exception caught: " << error.what() << endl;
		}
	catch(...) {
		cout << "Unknown exception caught!" << endl;
		}
    
    delete g_Model_ptr;
    return 0;
}

