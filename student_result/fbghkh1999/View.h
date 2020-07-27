#ifndef VIEW_H
#define VIEW_H

#include "Geometry.h"
#include <map>
#include <string>

/* *** View class ***
The View class encapsulates the data and functions needed to generate the map
display, and control its properties. It has a "memory" for the names and locations
of the to-be-plotted objects.

Usage: 
1. Call the update_location function with the name and position of each object
to be plotted. If the object is not already in the View's memory, it will be added
along with its location. If it is already present, its location will be set to the 
supplied location. If a single object changes location, its location can be separately
updated with a call to update_location. 
2. Call the update_remove function with the name of any object that should no longer
be plotted. This must be done *after* any call to update_location that 
has the same object name since update_location will add any object name supplied.
3. Call the draw function to print out the map. 
4. As needed, change the origin, scale, or displayed size of the map 
with the appropriate functions. Since the view "remembers" the previously updated
information, the draw function will print out a map showing the previous objects
using the new settings.
*/

/* 
*** This skeleton file shows the required public interface for the class, which you may not modify. 
If no protected members are shown, there must be none in your version. 
If any protected or private members are shown here, then your class must also have them and use them as intended.
You must delete this comment and all other comments that start with "***".
*/

class View
{
public:
	// default constructor sets the default size, scale, and origin
	View();

	// Save the supplied name and location for future use in a draw() call
	// If the name is already present,the new location replaces the previous one.
	void update_location(const std::string &name, Point location);

	// Remove the name and its location; no error if the name is not present.
	void update_remove(const std::string &name);

	// prints out the current map
	void draw();

	// discard the saved information.
	void clear();

	// modify the display parameters
	// if the size is out of bounds will throw Error("New map size is too big!")
	// or Error("New map size is too small!")
	void set_size(int in_size);

	// If scale is not postive, will throw Error("New map scale must be positive!");
	void set_scale(double in_scale);

	// any values are legal for the origin
	void set_origin(Point in_origin);

	// set the parameters to the default values
	void set_defaults();

private:
	int size;
	Point origin;
	double scale;
	std::map<std::string, Point> objects;
	bool get_subscripts(int &ix, int &iy, Point location);
	std::string convert_ints_to_key(int row, int col);
	//*** static integral types can be initialized in the class declaration
	static const int map_view_max_size = 30; // maximum number of rows and columns
	static const int map_initial_size = 25;
};
#endif
