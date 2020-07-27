#ifndef VIEWS_H
#define VIEWS_H

#include "Geometry.h"
#include <string>
#include <map>

class View
{
public:
   // constructor for generic view
   View(const std::string &name_)
   {
      name = name_;
   }

   std::string get_name() const
   {
      return name;
   }

   // display the view
   virtual void draw() = 0;

   // update functions
   virtual void update_amount(const std::string &name, double amount) {}
   virtual void update_health(const std::string &name, double health) {}
   virtual void update_location(const std::string &name, Point location) {}
   virtual void update_remove(const std::string &name) {}

private:
   std::string name;
};

class World_View : public View
{
public:
   World_View(const std::string &name, int size, Point origin, double scale);
   // draw a view of the world
   void draw() override;

   // world view updates
   void update_location(const std::string &name, Point location) override;
   void update_remove(const std::string &name) override;

   // world dimension updates
   virtual void set_origin(Point origin_)
   {
      origin = origin_;
   }
   virtual void set_scale(double scale_);
   virtual void set_size(int size_);
   virtual void set_defaults();

protected:
   // subscript function
   bool get_subscripts(int &ix, int &iy, Point location);

private:
   std::map<std::string, Point> objects;
   int size;
   Point origin;
   double scale;
   static const int map_view_max_size = 30; // maximum number of rows and columns
   static const int map_initial_size = 25;
   static const int map_view_min_size = 6;
};

class Map_View : public World_View
{
public:
   Map_View(const std::string &name, int size, Point origin, double scale);

   // display the map_view
   void draw() override;

   // map view modifiers
   void set_origin(Point origin_) override;
   void set_scale(double scale_) override;
   void set_size(int size_) override;
   void set_defaults() override;

   // map view updates
   void update_location(const std::string &name, Point location) override;
   void update_remove(const std::string &name) override;

private:
   std::map<std::string, Point> sim_objects;
   int size;
   Point origin;
   double scale;
   static const int map_initial_size = 25;
};

class Local_View : public World_View
{
public:
   Local_View(const std::string &name, int size, Point origin, double scale);

   // display the local_view
   void draw() override;

   // local_view manipulators
   // disallow to prevent programming erros
   void set_scale(double) override {}
   void set_size(int) override {}
   void set_defaults() override {}

   // world view updates
   void update_location(const std::string &name, Point location) override;
   void update_remove(const std::string &name) override;

private:
   std::string local_object_name;
   int size;
   double scale;
   bool exists;
};

class Attribute_View : public View
{
public:
   Attribute_View(const std::string &name);

   // draw an attribute view
   void draw() override;

   // attribute view updates
   void update_amount(const std::string &name, double amount) override;
   void update_health(const std::string &name, double health) override;
   void update_remove(const std::string &name) override;

private:
   std::map<std::string, double> attribute_list;
};

class Health_View : public Attribute_View
{
public:
   Health_View(const std::string &name) : Attribute_View(name){};

   // draw a health view
   void draw() override;

   // make update_amount do nothing
   void update_amount(const std::string &name, double amount) override {}
};

class Amount_View : public Attribute_View
{
public:
   Amount_View(const std::string &name) : Attribute_View(name) {}

   // draw an amount view
   void draw() override;

   // make update_health do nothing
   void update_health(const std::string &name, double amount) override {}
};

#endif
