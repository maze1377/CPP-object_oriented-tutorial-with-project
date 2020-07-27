/* A Structure is a Sim_object with a location and interface to derived types */

/* *** Comments starting with *** (like this one) in this skeleton file are
instructions for you and should be deleted after you have dealt with them.
You must add code to this file to meet the requirements in the project document,
the comments below, and other relevant course content.
*/

/* 
*** This skeleton file shows the required public interface for the class, which you may not modify. 
If no protected members are shown, there must be none in your version. 
If any protected or private members are shown here, then your class must also have them and use them as intended.
You can add private members of your choice.

You must delete this comment and all other comments that start with "***".
*/

public:
	// *** provide a constructor and destructor
	// *** first constructor parameter should be the name, specified as a string, the second should be a Point for the location.
	
	// *** Make this an abstract class by making the destructor pure virtual
		
	// *** declare and define here appropriately
	Point get_location()

	// *** declare and define the following functions as specified
	void update()

	// output information about the current state
	void describe()

	// ask model to notify views of current state
    void broadcast_current_state()
    
	// fat interface for derived types	
	double withdraw(double amount_to_get);
	void deposit(double amount_to_give);
