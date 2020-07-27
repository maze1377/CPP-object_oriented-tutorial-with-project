#ifndef WARRIORS_H
#define WARRIORS_H

#include "Agent.h"
#include "Geometry.h"
#include <memory>

/*
A Archer is an Agent that has attack and defense behaviors. It can be commanded
to start attacking another Agent and will continue the attack as long as 
it is alive and the target is alive and in range. If attacked, the Soldier will
start attacking its attacker.
Archer Has less physical strength  but have bigger range for attack
*/

class Archer : public Agent
{
public:
   Archer(const std::string &name, Point location);

   // implements Archer behavior
   void update() override;

   // Make this Soldier start attacking the target Agent.
   // Throws an exception if the target is the same as this Agent,
   // is out of range, or is not alive.
   void start_attacking(std::shared_ptr<Agent> target_ptr) override;

   // Overides Agent take hit to run away
   // to the nearest structure
   void take_hit(int attack_strength, std::shared_ptr<Agent> attacker_ptr) override;

   // Overrides agent stop to print a message
   void stop() override;

   // desribes the current state of the Archer
   void describe() const override;

   // disable get_amount for archer
   double get_amount() override
   {
      return -1.0;
   }

private:
   bool attacking;
   int attack_strength;
   double range;
   std::weak_ptr<Agent> target;
   static const int initial_strength = 1;
};
#endif





