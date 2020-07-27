#ifndef SIM_OBJECT_H
#define SIM_OBJECT_H

#include "Geometry.h"
#include <string>
/* The Sim_object class provides the interface for all of simulation objects. 
It also stores the object's name, and has pure virtual describe, update, 
and location accessor functions. */

class Sim_object
{
public:
	Sim_object(const std::string &in_name);

	std::string get_name() const
	{
		return name;
	}

	virtual Point get_location() const = 0;
	virtual void describe() const = 0;
	virtual void update() = 0;

private:
	std::string name;
};
#endif
