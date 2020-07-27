#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <iosfwd>

/*
This set of simple classes is used to compute positions and directions in the plane, 
in both cartesian and polar coordinates.

These classes are defined with "struct" to make all members public by default.

These classes make no assumptions about units of measurement of distance. Angles
can be specified in radians, but radians can be converted to and from 
trigonometry degrees in which 0 degrees corresponds to (x > 0, y = 0), 
and 90 degrees corresponds to (x = 0, y > 0).

Point is a set of (x, y) coordinates. 

A Cartesian_vector is (delta_x, delta_y) - a displacement in Cartesian coordinates.

A Polar_vector is (r, theta) - a displacement in polar coordinates using radians.

Various overloaded operators support computations of positions and directions.
*/

// angle units conversion functions
double to_radians(double theta_d);
double to_degrees(double theta_r);

// forward class declarations
struct Cartesian_vector;
struct Polar_vector;

/* Point */
// A Point contains an (x, y) pair to represent coordinates
struct Point
{
	double x;
	double y;

	Point(double in_x = 0., double in_y = 0.) : x(in_x), y(in_y)
	{
	}

	// compare two Points
	bool operator==(const Point &rhs) const;
	bool operator!=(const Point &rhs) const;
};

// return the distance between two Points
double cartesian_distance(const Point &p1, const Point &p2);

/* Cartesian_vector */
// A Cartesian_vector contains an x, y displacement
struct Cartesian_vector
{
	double delta_x;
	double delta_y;

	Cartesian_vector(double in_delta_x = 0., double in_delta_y = 0.) : delta_x(in_delta_x), delta_y(in_delta_y)
	{
	}

	// construct a Cartesian_vector from two Points,
	// showing the vector from p1 to p2
	// that is, p1 + cv => p2
	Cartesian_vector(const Point &p1, const Point &p2);

	// construct a Cartesian_vector from a Polar_vector
	Cartesian_vector(const Polar_vector &pv);
};

/* Polar_vector */
// Polar_vector describes a displacement in terms of polar coordinates
// with angle in radians
struct Polar_vector
{
	double r;
	double theta;

	Polar_vector(double in_r = 0., double in_theta = 0.) : r(in_r), theta(in_theta)
	{
	}

	// construct a Polar_vector from two Points,
	// showing the vector from p1 to p2
	// that is, p1 + pv => p2
	Polar_vector(const Point &p1, const Point &p2);

	// construct a Polar_vector from a Cartesian_vector
	Polar_vector(const Cartesian_vector &cv);
};

// *** Overloaded Operators ***

// Subtract two Points to get a Cartesian_vector
// p2's components are subtracted from p1
Cartesian_vector operator-(const Point &p1, const Point &p2);

// Add a Point and a Cartesian_vector to get the displaced Point
Point operator+(const Point &p, const Cartesian_vector &cv);
Point operator+(const Cartesian_vector &cv, const Point &p);

// Add a Point and a Polar_vector to get the displaced Point
Point operator+(const Point &p, const Polar_vector &pv);
Point operator+(const Polar_vector &pv, const Point &p);

// Adding or subtracting two Cartesian_vectors adds or subtracts the components
Cartesian_vector operator+(const Cartesian_vector &cv1, const Cartesian_vector &cv2);
Cartesian_vector operator-(const Cartesian_vector &cv1, const Cartesian_vector &cv2);

// divide a Cartesian_vector by a double: divide each component by the double
Cartesian_vector operator/(const Cartesian_vector &cv, double d);
Cartesian_vector operator/(double d, const Cartesian_vector &cv);

// divide a Polar_vector by a double: divide r component by the double
Polar_vector operator/(const Polar_vector &pv, double d);
Polar_vector operator/(double d, const Polar_vector &pv);

// multiply a Cartesian_vector by a double: divide each component by the double
Cartesian_vector operator*(const Cartesian_vector &cv, double d);
Cartesian_vector operator*(double d, const Cartesian_vector &cv);

// multiply a Polar_vector by a double: divide r component by the double
Polar_vector operator*(const Polar_vector &pv, double d);
Polar_vector operator*(double d, const Polar_vector &pv);

// Output operators
std::ostream &operator<<(std::ostream &os, const Point &p);
std::ostream &operator<<(std::ostream &os, const Cartesian_vector &cv);
std::ostream &operator<<(std::ostream &os, const Polar_vector &pv);

#endif
