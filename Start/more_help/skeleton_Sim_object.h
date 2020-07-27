/* The Sim_object class provides the interface for all of simulation objects. 
It also stores the object's name, and has pure virtual accessor functions for 
the object's position and other information. */

/* *** Comments starting with *** (like this one) in this skeleton file are
instructions for you and should be deleted after you have dealt with them.
You must add code to this file to meet the requirements in the project document,
the comments below, and other relevant course content.
*/

/* 
*** This skeleton file shows the required public interface for the class, which you may not modify. 
If no protected members are shown, there must be none in your version. 
If any protected or private members are shown here, then your class must also have them and use them as intended.
No additional private members may be added to this class.

You must delete this comment and all other comments that start with "***".
*/

class Sim_object {
public:
	Sim_object(const std::string& name_);
	// *** supply the appropriate destructor declaration
	
	const std::string& get_name() const
		{return name;}
			
	/*** Interface for derived classes ***/
	// *** declare the following to be pure virtual functions
	Point get_location() const
	void describe() const
	void update()
	// ask model to notify views of current state
    virtual void broadcast_current_state() const

	// Sim_objects must be unique, so disable copy/move construction, assignment
    // of base class, which means that derived class objects can't be copied or moved either.
    Sim_object(const Sim_object&) = delete;
    Sim_object& operator= (const Sim_object&) = delete;
    Sim_object(Sim_object&&) = delete;
    Sim_object& operator= (Sim_object&&) = delete;
	
private:
	std::string name;
};

