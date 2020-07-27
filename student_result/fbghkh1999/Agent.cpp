#include "Agent.h"
#include "Utility.h"
#include "Model.h"
#include <iostream>

using std::cout;
using std::endl;
using std::shared_ptr;
using std::string;

static const double initial_speed_c = 5.0;

// create with initial health is 5, speed is 5, state is Alive
Agent::Agent(const std::string &in_name, Point in_location)
    : Moving_object(in_location, initial_speed_c), Sim_object(in_name)
{
   health = initial_health_c;
   alive = true;
}

Agent::~Agent()
{
   cout << "Agent " << get_name() << " destructed" << endl;
}

// tell this Agent to start moving to location destination_
void Agent::move_to(Point destination)
{
   start_moving(destination);
   if (get_current_location() == destination)
   {
      cout << get_name() << ": I'm already there" << endl;
   }
   else
   {
      cout << get_name() << ": I'm on the way" << endl;
   }
}

// tell this Agent to stop its activity
void Agent::stop()
{
   if (is_currently_moving())
   {
      stop_moving();
      cout << get_name() << ": I'm stopped" << endl;
   }
}

// Tell this Agent to accept a hit from an attack of a specified strength
// The attacking Agent identifies itself with its this pointer.
// A derived class can override this function.
// The function lose_health is called to handle the effect of the attack.
void Agent::take_hit(int attack_strength, shared_ptr<Agent> attacker_ptr)
{
   lose_health(attack_strength);
}

// update the moving state and Agent state of this object.
void Agent::update()
{
   if (!alive)
   {
      alive = false;
   }
   else
   {
      if (is_moving())
      {
         if (update_location())
         {
            cout << get_name() << ": I'm there!" << endl;
         }
         else
         {
            cout << get_name() << ": step..." << endl;
         }
         Model::get_instance()->notify_location(get_name(), get_current_location());
      }
   }
}

// output information about the current state
void Agent::describe() const
{
   cout << get_name() << " at " << get_current_location() << endl;
   if (alive)
   {
      cout << "   Health is " << health << endl;
      if (is_moving())
      {
         cout << "   Moving at speed " << get_current_speed()
              << " to " << get_current_destination() << endl;
      }
      else
      {
         cout << "   Stopped" << endl;
      }
   }
}

// Throws exception that an Agent cannot work.
void Agent::start_working(shared_ptr<Structure> s1, shared_ptr<Structure> s2)
{
   throw Error(get_name() + ": Sorry, I can't work!");
}

// Throws exception that an Agent cannot attack.
void Agent::start_attacking(shared_ptr<Agent>)
{
   throw Error(get_name() + ": Sorry, I can't attack!");
}

// protected members
// calculate loss of health due to hit.
// if health decreases to zero or negative, Agent state becomes Dying, and any movement is stopped.
void Agent::lose_health(int attack_strength)
{
   health -= attack_strength;
   if (health <= 0)
   {
      alive = false;
      stop_moving();
      cout << get_name() << ": Arrggh!" << endl;
      Model::get_instance()->remove_agent(shared_from_this());
   }
   else
   {
      cout << get_name() << ": Ouch!" << endl;
      Model::get_instance()->notify_health(get_name(), health);
   }
}
