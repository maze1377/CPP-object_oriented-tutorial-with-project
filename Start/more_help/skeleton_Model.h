/*
Model is part of a simplified Model-View-Controller pattern.
Model keeps track of the Sim_objects in our little world. It is the only
component that knows how many Structures and Agents there are, but it does not
know about any of their derived classes, nor which Agents are of what kind of Agent. 
It has facilities for looking up objects by name, and removing Agents.  When
created, it creates an initial group of Structures and Agents using the Structure_factory
and Agent_factory.
Finally, it keeps the system's time.

Controller tells Model what to do; Model in turn tells the objects what do, and
when asked to do so by an object, tells all the Views whenever anything changes that might be relevant.
Model also provides facilities for looking up objects given their name.

Notice how only the Standard Library headers need to be included - reduced coupling!

/* *** Comments starting with *** (like this one) in this skeleton file are
instructions for you and should be deleted after you have dealt with them.
You must add code to this file to meet the requirements in the project document,
the comments below, and other relevant course content.
*/

/* 
*** This skeleton file shows the required public interface for the class, which you may not modify. 
If no protected members are shown, there must be none in your version. 
If any protected or private members are shown here, then your class must also have them and use them as intended.
You can add other private members of your choice.

You must delete this comment and all other comments that start with "***".
*/

/* 
*** Here provide the appropriate declarations for a global variable named g_Model_ptr of type Model*
 - follow the Header File Guidelines. 
 */
 
class Model {
public:
	// Output a message after doing all initialization and clean-up work
	// create the initial objects
	Model();
	
	// destroy all objects
	~Model();

	// return the current time
	int get_time() const {return time;}

	// is name already in use for either agent or structure?
    // return true if the name matches the name of an existing agent or structure
	bool is_name_in_use(const std::string& name) const;

	// is there a structure with this name?
	bool is_structure_present(const std::string& name) const;
	// add a new structure; assumes none with the same name
	void add_structure(Structure*);
	// will throw Error("Structure not found!") if no structure of that name
	Structure* get_structure_ptr(const std::string& name) const;

	// is there an agent with this name?
	bool is_agent_present(const std::string& name) const;
	// add a new agent; assumes none with the same name
	void add_agent(Agent*);
	// will throw Error("Agent not found!") if no agent of that name
	Agent* get_agent_ptr(const std::string& name) const;
	
	// tell all objects to describe themselves to the console
	void describe() const;
	// increment the time, and tell all objects to update themselves
	void update();	
	
	/* View services */
	// Attaching a View adds it to the container and causes it to be updated
    // with all current objects'location (or other state information.
	void attach(View*);
	// Detach the View by discarding the supplied pointer from the container of Views
    // - no updates sent to it thereafter.
	void detach(View*);
    // notify the views about an object's location
	void notify_location(const std::string& name, Point location) const;
	// notify the views that an object is now gone
	void notify_gone(const std::string& name) const;
	
private:
	// *** declare an int member variable to store the simulated time



	// disallow copy/move construction or assignment
	Model(const Model&) = delete;
	Model& operator= (const Model&)  = delete;
	Model(Model&&) = delete;
	Model& operator= (Model&&) = delete;
};
