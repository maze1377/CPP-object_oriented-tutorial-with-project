#include "View.h"
#include "Utility.h"
#include "Sim_object.h"
#include <iostream>
#include <iomanip>
#include <map>
#include <cmath>
#include <sstream>

using std::cout;
using std::endl;
using std::ios;
using std::multimap;
using std::pair;
using std::setw;
using std::string;
using std::stringstream;

static const double initial_scale = 2.0;
static const Point initial_origin(-10., -10.);
static const string initial_state = ". ";
static const int upper_map_bound = 30;
static const int lower_map_bound = 6;

string View::convert_ints_to_key(int row, int col)
{
   stringstream ss;
   ss << row;
   ss << col;
   return ss.str();
}

/* *** Use this function to calculate the subscripts for the cell. */
// Calculate the cell subscripts corresponding to the supplied location parameter,
// using the current size, scale, and origin of the display.
// This function assumes that origin is a  member variable of type Point,
// scale is a double value, and size is an integer for the number of rows/columns
// currently being used for the grid.
// Return true if the location is within the grid, false if not
bool View::get_subscripts(int &ix, int &iy, Point location)
{
   // adjust with origin and scale
   Cartesian_vector subscripts = (location - origin) / scale;
   // truncate coordinates to integer after taking the floor
   // floor function will produce integer smaller than even for negative values,
   // so - 0.05 => -1., which will be outside the array.
   ix = int(floor(subscripts.delta_x));
   iy = int(floor(subscripts.delta_y));
   // if out of range, return false
   if ((ix < 0) || (ix >= size) || (iy < 0) || (iy >= size))
   {
      return false;
   }
   else
      return true;
}

View::View()
{
   size = map_initial_size;
   scale = initial_scale;
   origin = initial_origin;
}

void View::update_location(const string &name, Point location)
{
   objects[name] = location;
}

void View::update_remove(const std::string &name)
{
   objects.erase(name);
}

void View::draw()
{
   int row, col;
   bool delay = true;
   multimap<string, string> out_info;

   // handle out of bounds output
   cout << "Display size: " << size << ", scale: " << scale << ", origin: " << origin << endl;
   for (auto it : objects)
   {
      if (!get_subscripts(col, row, it.second) && delay)
      {
         cout << it.first;
         delay = false;
      }
      else if (!get_subscripts(col, row, it.second))
      {
         cout << ", " << it.first;
      }
      else
      {
         string key = convert_ints_to_key(row, col);
         out_info.insert(pair<string, string>(key, it.first));
      }
   }
   if (!delay)
   {
      cout << " outside the map" << endl;
   }

   cout.precision(0);

   double ylabel;
   ylabel = (size * scale + origin.y) - scale;
   // print the map
   for (int row = size - 1; row >= 0; --row)
   {
      if (row % 3 == 0)
      {
         cout << setw(4) << ylabel << " ";
      }
      else
      {
         cout << "     ";
      }
      for (int col = 0; col < size; ++col)
      {
         int temp_row = row;
         int temp_col = col;
         string key = convert_ints_to_key(temp_row, temp_col);

         if (out_info.count(key) == 0)
         {
            cout << ". ";
         }
         else if (out_info.count(key) > 1)
         {
            cout << "* ";
         }
         else
         {
            auto it = out_info.find(key);
            cout << it->second.substr(0, 2);
         }
      }
      ylabel -= scale;
      cout << endl;
   }

   double xlabel = origin.x;
   for (int i = 0; i < size; ++i)
   {
      if (i % 3 == 0)
      {
         cout << "  " << setw(4) << xlabel;
      }
      xlabel += scale;
   }
   cout << endl;
   cout.precision(2);
}

void View::clear()
{
   objects.clear();
}

void View::set_size(int in_size)
{
   if (in_size > upper_map_bound)
   {
      throw Error("New map size is too big!");
   }

   if (in_size <= lower_map_bound)
   {
      throw Error("New map size is too small!");
   }

   size = in_size;
}

void View::set_scale(double in_scale)
{
   if (in_scale <= 0.0)
   {
      throw Error("New map scale must be positive!");
   }
   scale = in_scale;
}

void View::set_origin(Point in_origin)
{
   origin = in_origin;
}

void View::set_defaults()
{
   size = map_initial_size;
   scale = initial_scale;
   origin = initial_origin;
}
