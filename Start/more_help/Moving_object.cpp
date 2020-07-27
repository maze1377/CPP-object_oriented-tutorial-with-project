#include "Moving_object.h"
#include <cmath>

using std::fabs;

	
// Tell this object to start moving to location in_destination
// If it is already at the destination and moving, it stops;
// if already there and not moving, it stays stopped.
// Otherwise, it starts moving, advancing by delta on each update call.
void Moving_object::start_moving(Point destination_)
{
	if(location == destination_) {
		if(moving) {
			stop_moving();
			}
		return;
		}
	// time to start moving
	moving = true;
	destination = destination_;
	compute_delta();
}

// change the speed by recomputing the delta if we are moving
void Moving_object::set_speed(double speed_)
{
	speed = speed_;
	// recompute the delta to get to the same destination
	if(moving)
		compute_delta();
}

// call stop to tell this object to stop whatever it is doing
// reset the delta and the destination to make it more obvious that we aren't moving
void Moving_object::stop_moving()
{
	moving = false;
	delta = Cartesian_vector();
	destination = Point();
}

// If the destination is within one delta step away, the object has arrived.
// Set the location to the destination, stop, and return true.
// Otherwise, add the delta to the location, and return false.
bool Moving_object::update_location()
{
	Cartesian_vector diff = destination - location;
	if ((fabs(diff.delta_x) <= fabs(delta.delta_x)) && (fabs(diff.delta_y) <= fabs(delta.delta_y))) {
		location = destination;
		stop_moving();
		return true;
		}
	location = location + delta;
	return false;
}

// use the Geometry operators to compute the delta change in x and y per update
void Moving_object::compute_delta()
{
	delta = (destination - location) * (speed / cartesian_distance(destination, location));
}

	


