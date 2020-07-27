#include "Peasant.h"
#include "Structure.h"
#include "Utility.h"
#include "Model.h"
#include <iostream>

using std::cout;
using std::endl;
using std::shared_ptr;
using std::string;

static const double initial_food_c = 0.0;
static const double max_food_c = 35.0;

Peasant::Peasant(const std::string &in_name, Point in_location)
    : Agent(in_name, in_location)
{
   food = initial_food_c;
   p_state = NOT_WORKING;
}

// implement Peasant behavior
void Peasant::update()
{
   Agent::update();

   if (!is_alive() || p_state == NOT_WORKING)
   {
   }
   else if (p_state == INBOUND && !is_moving())
   {
      p_state = COLLECTING;
   }
   else if (p_state == COLLECTING)
   {
      double food_to_add = max_food_c - food;
      food_to_add = source->withdraw(food_to_add);
      food += food_to_add;

      if (food_to_add > 0.0)
      {
         cout << get_name() << ": Collected " << food_to_add << endl;
         p_state = OUTBOUND;
         Agent::move_to(destination->get_location());
         Model::get_instance()->notify_amount(get_name(), food);
      }
      else
      {
         cout << get_name() << ": Waiting " << endl;
      }
   }
   else if (p_state == OUTBOUND && !is_moving())
   {
      p_state = DEPOSITING;
   }
   else if (p_state == DEPOSITING)
   {
      destination->deposit(food);
      cout << get_name() << ": Deposited " << food << endl;
      food = 0.0;
      Agent::move_to(source->get_location());
      p_state = INBOUND;
      Model::get_instance()->notify_amount(get_name(), food);
   }
}

// overridden to suspend working behavior
void Peasant::move_to(Point dest)
{
   if (p_state != NOT_WORKING)
   {
      cout << get_name() << ": I'm stopping work" << endl;
   }
   p_state = NOT_WORKING;
   source = nullptr;
   destination = nullptr;
   Agent::move_to(dest);
}

// stop moving and working
void Peasant::stop()
{
   Agent::stop();
   if (p_state != NOT_WORKING)
   {
      cout << get_name() << ": I'm stopping work" << endl;
   }
   p_state = NOT_WORKING;
   source = nullptr;
   destination = nullptr;
}

// starts the working process
// Throws an exception if the source is the same as the destination.
void Peasant::start_working(shared_ptr<Structure> source_, shared_ptr<Structure> destination_)
{
   Agent::stop();
   p_state = NOT_WORKING;
   source = nullptr;
   destination = nullptr;

   if (source_ == destination_)
   {
      throw Error(get_name() + ": I can't move food to and from the same place!");
   }

   source = source_;
   destination = destination_;

   if (food == 0.0)
   {
      if (get_location() == source->get_location())
      {
         p_state = COLLECTING;
      }
      else
      {
         Agent::move_to(source->get_location());
         p_state = INBOUND;
      }
   }
   else
   {
      if (get_location() == destination->get_location())
      {
         p_state = DEPOSITING;
      }
      else
      {
         Agent::move_to(destination->get_location());
         p_state = OUTBOUND;
      }
   }
}

// output information about the current state
void Peasant::describe() const
{
   cout << "Peasant ";
   Agent::describe();
   cout << "   Carrying " << food << endl;

   switch (p_state)
   {
   case NOT_WORKING:
      break;
   case OUTBOUND:
      cout << "   Outbound to destination " << destination->get_name() << endl;
      break;
   case INBOUND:
      cout << "   Inbound to source " << source->get_name() << endl;
      break;
   case COLLECTING:
      cout << "   Collecting at source " << source->get_name() << endl;
      break;
   case DEPOSITING:
      cout << "   Depositing at destination " << destination->get_name() << endl;
      break;
   default:
      cout << "Don't know what I'm doing" << endl;
   }
}
