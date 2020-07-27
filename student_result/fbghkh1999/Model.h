#ifndef MODEL_H
#define MODEL_H

#include "Geometry.h"
#include <string>
#include <map>
#include <memory>
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
tells View whenever anything changes that might affect the View, and provides
facilities for looking up objects given their name.

Notice how only the Standard Library headers need to be included - reduced coupling!

*/

class Structure;
class Agent;
class View;
class Sim_object;

class Model
{
public:
	// get_intance function
	static Model *get_instance();

	// return the current time
	int get_time() { return time; }

	// is name already in use for either agent or structure?
	bool is_name_in_use(const std::string &name) const;

	// is there a structure with this name?
	bool is_structure_present(const std::string &name) const;
	// add a new structure; assumes none with the same name
	void add_structure(std::shared_ptr<Structure>);
	// will throw Error("Structure not found!") if no structure of that name
	std::shared_ptr<Structure> get_structure_ptr(const std::string &name) const;

	// is there an agent with this name?
	bool is_agent_present(const std::string &name) const;
	// add a new agent; assumes none with the same name
	void add_agent(std::shared_ptr<Agent>);
	// will throw Error("Agent not found!") if no agent of that name
	std::shared_ptr<Agent> get_agent_ptr(const std::string &name) const;
	// removes the agent and then deletes it; no error if not found
	void remove_agent(std::shared_ptr<Agent>);

	// tell all objects to describe themselves to the console
	void describe() const;

	// update the objects and the views
	void update();

	/* View services */
	// Attaching a View causes it to be updated with all current objects'location,
	// amounts, and health
	void attach(std::shared_ptr<View>);
	// Detach the specified View by discarding the pointer - no updates sent to it thereafter.
	void detach(std::shared_ptr<View>);

	// notify functions to allow sim_objects to inform model of their changes
	// so model can inform view
	void notify_health(const std::string &name, double health);
	void notify_amount(const std::string &name, double amount);
	void notify_location(const std::string &name, Point location);

	// finds the closest agent to the specified agent name
	std::shared_ptr<Agent> find_closest_Agent(const std::string &name);
	// finds the closest structure to the specified agent name
	std::shared_ptr<Structure> find_closest_Structure(const std::string &name);

private:
	friend class Model_destroyer;
	static Model *model;
	// create the initial objects
	Model();
	// destroy all objects
	//*** linker error ~Model() maybe visual studio problem?;
	int time;
	std::map<std::string, std::shared_ptr<View>> views;
	std::map<std::string, std::shared_ptr<Sim_object>> sim_objects;
	std::map<std::string, std::shared_ptr<Agent>> agents;
	std::map<std::string, std::shared_ptr<Structure>> structures;
	// no copy or assignment allowed
	//*** make private for now, change to = delete in linux
	Model(const Model &);
	Model &operator=(const Model &);
	Model(const Model &&);
	Model &operator=(const Model &&);
};
#endif
