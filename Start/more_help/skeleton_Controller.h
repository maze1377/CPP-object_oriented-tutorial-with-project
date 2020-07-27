/* Controller
This class is responsible for controlling the Model and View according to interactions
with the user.
*/

/* *** Comments starting with *** (like this one) in this skeleton file are
instructions for you and should be deleted after you have dealt with them.
You must add code to this file to meet the requirements in the project document,
the comments below, and other relevant course content.
*/


/* 
*** This skeleton file shows the required public interface for the class, which you may not modify. 
You can add private members of your choice.

You must delete this comment and all other comments that start with "***".
*/

class Controller {
public:	
	// *** Output a message after doing all initialization and clean-up work
	Controller();
	~Controller();  // delete any View objects that still exist

	// run the program by acccepting user commands
	void run();
