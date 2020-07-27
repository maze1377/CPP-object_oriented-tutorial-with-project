#ifndef AGENT_H
#define AGENT_H

#include "Moving_object.h"
#include "Sim_object.h"
#include <string>
#include <memory>

/* 
Agents are a kind of Sim_object, and privately inherit from Moving_object.
Agents can be commanded to move to a destination. Agents have a health, which
is decreased when they take a hit. If the Agent's health > 0, it is alive.
if its heath <= 0, it starts dying, then on subsequent updates, 
it becomes dead, and finally disappearing.
*/

class Structure;

class Agent : private Moving_object, public Sim_object, public std::enable_shared_from_this<Agent>
{
public:
	// create with initial health is 5, speed is 5, state is Alive
	Agent(const std::string &in_name, Point in_location);

	// destroy object in c++ and return memory to the system
	virtual ~Agent();

	// return true if this agent is Alive or Disappearing
	bool is_alive() const
	{
		return alive;
	}

	// returns the agents current health
	int get_health()
	{
		return health;
	}
	// returns the agents amount
	virtual double get_amount()
	{
		return 0.0;
	}

	// return this Agent's location
	Point get_location() const override
	{
		return get_current_location();
	}

	// return true if this Agent is in motion
	bool is_moving() const
	{
		return is_currently_moving();
	}

	// tell this Agent to start moving to location destination_
	virtual void move_to(Point destination_);

	// tell this Agent to stop its activity
	virtual void stop();

	// Tell this Agent to accept a hit from an attack of a specified strength
	// The attacking Agent identifies itself with its this pointer.
	// A derived class can override this function.
	// The function lose_health is called to handle the effect of the attack.
	virtual void take_hit(int attack_strength, std::shared_ptr<Agent> attacker_ptr);

	// update the moving state and Agent state of this object.
	void update() override;

	// output information about the current state
	virtual void describe() const;

	/* Fat Interface for derived classes */
	// Throws exception that an Agent cannot work.
	virtual void start_working(std::shared_ptr<Structure>, std::shared_ptr<Structure>);

	// Throws exception that an Agent cannot attack.
	virtual void start_attacking(std::shared_ptr<Agent>);

protected:
	// calculate loss of health due to hit.
	// if health decreases to zero or negative, Agent state becomes Dying, and any movement is stopped.
	void lose_health(int attack_strength);

private:
	bool alive;
	int health;
	static const int initial_health_c = 5;
};
#endif
