#include "Views.h"
#include "Utility.h"
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;
using std::setw;
using std::string;
using std::vector;

static const Point initial_origin(-10., -10.);
static const double initial_scale = 2.;

//--------------------------------------------------------------------------------
World_View::World_View(const string &name, int size_, Point origin_, double scale_)
    : View(name), size(size_), origin(origin_), scale(scale_) {}

void World_View::draw()
{
   // initialize the map
   string **map = new string *[size];
   for (int i = 0; i < size; ++i)
   {
      map[i] = new string[size];
   }

   for (int i = 0; i < size; ++i)
   {
      for (int j = 0; j < size; ++j)
      {
         map[i][j] = ". ";
      }
   }

   // set the objects that are in range
   for (auto object : objects)
   {
      int x, y;
      if (get_subscripts(x, y, object.second))
      {
         if (map[y][x] == ". ")
         {
            map[y][x] = object.first.substr(0, 2);
         }
         else
         {
            map[y][x] = "* ";
         }
      }
   }

   // print the map
   cout.precision(0);

   double ylabel;
   ylabel = (size * scale + origin.y) - scale;
   for (int i = size - 1; i >= 0; --i)
   {
      if (i % 3 == 0)
      {
         cout << setw(4) << ylabel << " ";
      }
      else
      {
         cout << "     ";
      }
      for (int j = 0; j < size; ++j)
      {
         cout << map[i][j];
      }
      ylabel -= scale;
      cout << endl;
   }

   // handle xlabels
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

   // cleanup map
   for (int i = 0; i < size; ++i)
   {
      delete[] map[i];
   }
   delete[] map;
}

void World_View::update_location(const string &name, Point location)
{
   objects[name] = location;
}

void World_View::update_remove(const string &name)
{
   objects.erase(name);
}

void World_View::set_scale(double scale_)
{
   if (scale_ <= 0.0)
   {
      throw Error("New map scale must be positive!");
   }
   scale = scale_;
}

void World_View::set_size(int size_)
{
   if (size_ > map_view_max_size)
   {
      throw Error("New map size is too big!");
   }

   if (size_ <= map_view_min_size)
   {
      throw Error("New map size is too small!");
   }

   size = size_;
}

void World_View::set_defaults()
{
   origin = initial_origin;
   scale = initial_scale;
   size = map_initial_size;
}

bool World_View::get_subscripts(int &ix, int &iy, Point location)
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

//--------------------------------------------------------------------------------

Map_View::Map_View(const string &name_, int size_, Point origin_, double scale_)
    : World_View(name_, size_, origin_, scale_)
{
   size = size_;
   origin = origin_;
   scale = scale_;
}

void Map_View::draw()
{
   bool delay = true;
   int row, col;

   // handle out of bounds output
   cout << "Display size: " << size << ", scale: " << scale << ", origin: " << origin << endl;
   for (auto object : sim_objects)
   {
      if (!get_subscripts(col, row, object.second) && delay)
      {
         cout << object.first;
         delay = false;
      }
      else if (!get_subscripts(col, row, object.second))
      {
         cout << ", " << object.first;
      }
   }
   if (!delay)
   {
      cout << " outside the map" << endl;
   }

   // then call the world_view draw
   World_View::draw();
}

void Map_View::set_origin(Point origin_)
{
   World_View::set_origin(origin_);
   origin = origin_;
}

void Map_View::set_scale(double scale_)
{
   World_View::set_scale(scale_);
   scale = scale_;
}

void Map_View::set_size(int size_)
{
   World_View::set_size(size_);
   size = size_;
}

void Map_View::set_defaults()
{
   World_View::set_defaults();
   origin = initial_origin;
   scale = initial_scale;
   size = map_initial_size;
}

void Map_View::update_location(const string &name, Point location)
{
   World_View::update_location(name, location);
   sim_objects[name] = location;
}

void Map_View::update_remove(const string &name)
{
   World_View::update_remove(name);
   sim_objects.erase(name);
}

//--------------------------------------------------------------------------------

Local_View::Local_View(const string &name, int size_, Point origin, double scale_)
    : World_View(name, size_, origin, scale_)
{
   local_object_name = name;
   exists = true;
   size = size_;
   scale = scale_;
}

void Local_View::draw()
{
   cout << "Local view for: " << local_object_name << endl;
   World_View::draw();
}

void Local_View::update_location(const string &name, Point location)
{
   World_View::update_location(name, location);

   if ((name == local_object_name) && exists)
   {
      double new_x, new_y;
      new_x = location.x - (size / 2.) * scale;
      new_y = location.y - (size / 2.) * scale;
      set_origin(Point(new_x, new_y));
   }
}

void Local_View::update_remove(const string &name)
{
   World_View::update_remove(name);

   if (name == local_object_name)
   {
      exists = false;
   }
}

//--------------------------------------------------------------------------------
Attribute_View::Attribute_View(const string &name_) : View(name_) {}

void Attribute_View::draw()
{
   cout << "--------------" << endl;
   for (auto attribute_pair : attribute_list)
   {
      cout << attribute_pair.first << ": " << attribute_pair.second << endl;
   }
   cout << "--------------" << endl;
}

void Attribute_View::update_health(const string &name, double health)
{
   attribute_list[name] = health;
}

void Attribute_View::update_amount(const string &name, double amount)
{
   attribute_list[name] = amount;
}

void Attribute_View::update_remove(const string &name)
{
   attribute_list.erase(name);
}

//--------------------------------------------------------------------------------

void Health_View::draw()
{
   cout << "Current "
        << "Health"
        << ":" << endl;
   Attribute_View::draw();
}

//--------------------------------------------------------------------------------

void Amount_View::draw()
{
   cout << "Current "
        << "Amounts"
        << ":" << endl;
   Attribute_View::draw();
}
