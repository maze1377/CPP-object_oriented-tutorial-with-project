#ifndef PEASANT_H
#define PEASANT_H

#include "Agent.h"
#include <string>
#include <memory>

/* 
A Peasant is an Agent that can move food between Structures. It can be commanded to
start_working, whereupon it moves to the source, picks up food, returns to destination,
deposits the food, returns to source.  If picks up zero food at the source, it waits there
and tries again on the next update. 
If commanded to move_to somewhere, it stops working, and goes there.
*/

struct Point;
class Structure;

class Peasant : public Agent
{
public:
	Peasant(const std::string &in_name, Point in_location);

	// implement Peasant behavior
	void update() override;

	// overridden to suspend working behavior
	void move_to(Point dest) override;

	//override get_amount
	double get_amount() override
	{
		return food;
	}

	// stop moving and working
	void stop() override;

	// starts the working process
	// Throws an exception if the source is the same as the destination.
	void start_working(std::shared_ptr<Structure> source_, std::shared_ptr<Structure> destination_) override;

	// output information about the current state
	void describe() const override;

private:
	enum Peasant_state_e
	{
		NOT_WORKING,
		INBOUND,
		COLLECTING,
		OUTBOUND,
		DEPOSITING
	};
	Peasant_state_e p_state;
	double food;
	std::shared_ptr<Structure> source;
	std::shared_ptr<Structure> destination;
};

#endif
