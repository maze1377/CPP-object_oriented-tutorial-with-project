#ifndef STRUCTURE_H
#define STRUCTURE_H

#include "Geometry.h"
#include "Sim_object.h"
#include <string>
/* A Structure is a Sim_object with a location and interface to derived types */

class Structure : public Sim_object
{
public:
   Structure(std::string name_, Point location_);

   Point get_location() const override
   {
      return location;
   }

   // override structure to do nothing
   void update() override {}

   // output information about the current state
   void describe() const override;

   virtual double get_current_food()
   {
      return 0.0;
   }

   virtual double withdraw(double amount_to_get)
   {
      return 0.0;
   }

   virtual void deposit(double amount_to_give) {}

private:
   Point location;
};
#endif
