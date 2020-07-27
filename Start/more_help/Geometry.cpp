/* 
Geometry.cpp implementation file
See Geometry.h for comments
*/

#include "Geometry.h"

#include <iostream>
#include <cmath>

using namespace std;

// calculate a value for pi
const double pi = 2. * atan2(1., 0.);

// *** Member function definitions ***

// Point members
// compare two positions
bool Point::operator== (const Point& rhs) const
{
	return (x == rhs.x && y == rhs.y);
}
 
bool Point::operator!= (const Point& rhs) const
{
	return (x != rhs.x || y != rhs.y);
}

// return the distance between two Points
double cartesian_distance (const Point& p1, const Point& p2)
{
	double xd = p2.x - p1.x;
	double yd = p2.y - p1.y;
	double d = sqrt(xd * xd + yd * yd);
	return d;
}

// Cartesian_vector members
// construct a Cartesian_vector from two Points,
// showing the vector from p1 to p2 
// that is, p1 + cv => p2
Cartesian_vector::Cartesian_vector(const Point& p1, const Point& p2)
{
	delta_x = p2.x - p1.x;
	delta_y = p2.y - p1.y;
}

// construct a Cartesian_vector from a Polar_vector
Cartesian_vector::Cartesian_vector(const Polar_vector& pv)
{
	delta_x = pv.r * cos(pv.theta);
	delta_y = pv.r * sin(pv.theta);
}

// Polar_vector members
// construct a Polar_vector from a Cartesian_vector
Polar_vector::Polar_vector(const Cartesian_vector& cv)
{
	r = sqrt ((cv.delta_x * cv.delta_x) + (cv.delta_y * cv.delta_y));
	// atan2 will return neg angle for Quadrant III, IV, must translate to I, II
	theta = atan2 (cv.delta_y, cv.delta_x);
	if (theta < 0.)
		theta = 2. * pi + theta; // normalize theta positive
}

// construct a Polar_vector from two Points,
// showing the vector from p1 to p2 
// that is, p1 + pv => p2
Polar_vector::Polar_vector(const Point& p1, const Point& p2)
{
	Polar_vector pv (Cartesian_vector(p1, p2));
	r = pv.r;
	theta = pv.theta;
}




// *** Overloaded Operators ***

// Subtract two Points to get a Cartesian_vector
// p2's components are subtracted from p1
Cartesian_vector operator- (const Point& p1, const Point& p2)
{
	return Cartesian_vector(p1.x - p2.x, p1.y - p2.y);
}

// Add a Point and a Cartesian_vector to get the displaced Point
Point operator+ (const Point& p, const Cartesian_vector& cv)
{
	return Point(p.x + cv.delta_x, p.y + cv.delta_y);
}

Point operator+ (const Cartesian_vector& cv, const Point& p)
{
	return p + cv;
}
	
// Add a Point and a Polar_vector to get the displaced Point
Point operator+ (const Point& p, const Polar_vector& pv)
{
	Cartesian_vector cv (pv);
	return cv + p;
}

Point operator+ (const Polar_vector& pv, const Point& p)
{
	return p + pv;
}

// Adding or subtracting two Cartesian_vectors adds or subtracts the components
Cartesian_vector operator+ (const Cartesian_vector& cv1, const Cartesian_vector& cv2)
{
	return Cartesian_vector(cv1.delta_x + cv2.delta_x, cv1.delta_y + cv2.delta_y);
}

Cartesian_vector operator- (const Cartesian_vector& cv1, const Cartesian_vector& cv2)
{
	return Cartesian_vector(cv1.delta_x - cv2.delta_x, cv1.delta_y - cv2.delta_y);
}

// divide a Cartesian_vector by a double: divide each component by the double
Cartesian_vector operator/ (const Cartesian_vector& cv, double d)
{
	return Cartesian_vector(cv.delta_x / d, cv.delta_y / d);
}

Cartesian_vector operator/ (double d, const Cartesian_vector& cv)
{
	return cv / d;
}

// divide a Polar_vector by a double: divide r component by the double
Polar_vector operator/ (const Polar_vector& pv, double d)
{
	return Polar_vector(pv.r / d, pv.theta);
}

Polar_vector operator/ (double d, const Polar_vector& pv)
{
	return pv / d;
}

// multiply a Cartesian_vector by a double: multiply each component by the double
Cartesian_vector operator* (const Cartesian_vector& cv, double d)
{
	return Cartesian_vector(cv.delta_x * d, cv.delta_y * d);
}

Cartesian_vector operator* (double d, const Cartesian_vector& cv)
{
	return cv * d;
}

// multiply a Polar_vector by a double: multiply r component by the double
Polar_vector operator* (const Polar_vector& pv, double d)
{
	return Polar_vector(pv.r * d, pv.theta);
}

Polar_vector operator* (double d, const Polar_vector& pv)
{
	return pv * d;
}

// Output operators
// output a Point as "(x, y)"
ostream& operator<< (ostream& os, const Point& p)
{
	os << '(' << p.x << ", " << p.y << ')';
	return os;
}
	
// output a Cartesian_vector as "<x, y>"
ostream& operator<< (ostream& os, const Cartesian_vector& cv)
{
	os << '<' << cv.delta_x << ", " << cv.delta_y << '>';
	return os;
}

// output a Polar_vector as "P<r, theta>"
ostream& operator<< (ostream& os, const Polar_vector& pv)
{
	os << "P<" << pv.r << ", " << pv.theta << '>';
	return os;
}

/***** Utility function definitions *****/
// There are 2pi radians in 360 degrees
double to_radians (double theta_d)
{
	return 2. * pi  * (theta_d / 360.);
}

double to_degrees (double theta_r)
{
	double temp = 360. * theta_r / (2. * pi);
	return temp;
}
