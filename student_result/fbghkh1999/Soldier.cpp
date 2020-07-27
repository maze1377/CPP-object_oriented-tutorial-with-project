#include "Soldier.h"
#include "Sim_object.h"
#include "Utility.h"
#include <iostream>

using std::cout;
using std::endl;
using std::shared_ptr;
using std::string;

static int initial_attack_strength_c = 2;
static double initial_attack_range_c = 2.0;

Soldier::Soldier(const string &in_name, Point location) : Agent(in_name, location)
{
   attacking = false;
   attack_strength = initial_attack_strength_c;
   attack_range = initial_attack_range_c;
   cout << "Soldier " << get_name() << " constructed" << endl;
}

Soldier::~Soldier()
{
   cout << "Soldier " << get_name() << " destructed" << endl;
}

void Soldier::update()
{
   Agent::update();

   if (!is_alive())
   {
      return;
   }

   if (!attacking)
   {
      return;
   }

   if (attacking)
   {
      if (target.expired())
      {
         cout << get_name() << ": Target is dead" << endl;
         attacking = false;
         target.reset();
         return;
      }

      if (!target.lock()->is_alive())
      {
         cout << get_name() << ": Target is dead" << endl;
         attacking = false;
         target.reset();
         return;
      }

      if (cartesian_distance(get_location(), target.lock()->get_location()) > attack_range)
      {
         cout << get_name() << ": Target is now out of range" << endl;
         attacking = false;
         return;
      }

      cout << get_name() << ": Clang!" << endl;
      target.lock()->take_hit(attack_strength, shared_from_this());

      if (target.expired())
      {
         cout << get_name() << ": I triumph!" << endl;
         attacking = false;
         target.reset();
      }
   }
}

void Soldier::start_attacking(shared_ptr<Agent> target_ptr)
{
   if (target_ptr == shared_from_this())
   {
      throw Error(get_name() + ": I cannot attack myself!");
   }

   if (!target_ptr->is_alive())
   {
      throw Error(get_name() + ": Target is not alive!");
   }

   if (cartesian_distance(get_location(), target_ptr->get_location()) > attack_range)
   {
      throw Error(get_name() + ": Target is out of range!");
   }

   target = target_ptr;
   attacking = true;
   cout << get_name() << ": I'm attacking!" << endl;
}

void Soldier::take_hit(int attack_strength_, shared_ptr<Agent> attacker_ptr)
{
   lose_health(attack_strength_);

   if (attacking && !is_alive())
   {
      attacking = false;
      target.reset();
   }
   else if (!attacking && is_alive() && attacker_ptr->is_alive())
   {
      attacking = true;
      target = attacker_ptr;
      cout << get_name() << ": I'm attacking!" << endl;
   }
}

void Soldier::stop()
{
   cout << get_name() << ": Don't bother me" << endl;
}

void Soldier::describe() const
{
   cout << "Soldier ";
   Agent::describe();
   if (attacking)
   {
      if (target.expired())
      {
         cout << "   Attacking dead target" << endl;
      }
      else
      {
         cout << "   Attacking " << target.lock()->get_name() << endl;
      }
   }
   else
   {
      cout << "   Not attacking" << endl;
   }
}
