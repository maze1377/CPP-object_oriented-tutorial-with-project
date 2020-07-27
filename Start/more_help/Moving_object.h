#ifndef MOVING_OBJECT
#define MOVING_OBJECT
#include "Geometry.h"
/* Moving_object encapsulates the calculations needed to make an object move 
from one point to another, moving a specified distance on each update_location call.
*/

class Moving_object {
public:
	Moving_object() :
		moving(false) {}
	Moving_object(Point location_, double speed_) :
		moving(false), location(location_), speed(speed_) {}

	// readers
	bool is_currently_moving() const
		{return moving;}
	Point get_current_location() const
		{return location;}
	double get_current_speed() const
		{return speed;}
	Point get_current_destination() const
		{return destination;}
	
	// Tell this object to start moving to location destination.
	// If it is already at the destination and moving, it stops;
	// if already there and not moving, it stays stopped.
	// Otherwise, it starts moving, advancing by delta on each update call.
	void start_moving(Point destination_);
	// change the object's speed
	void set_speed(double speed_);
	// tell this object to stop moving
	void stop_moving();
	// update this object's location using current location, speed, and destination
	// returns true if arrived at destination, false if not
	bool update_location();

private:
	bool moving;			// true if this object is moving
	Point location;			// current location
	double speed;			// distance moved per update
	Point destination;		// destination to move to
	Cartesian_vector delta;	// x, y increments per update
	
	// helpers
	void compute_delta();
};

#endif
