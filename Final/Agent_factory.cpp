#include "Agent_factory.h"
#include "Peasant.h"
#include "Soldier.h"
#include "Utility.h"

using std::shared_ptr;
using std::string;

// Create and return the pointer to the specified Agent type. If the type
// is unrecognized, throws Error("Trying to create agent of unknown type!")
// The Agent is allocated with new, so some other component is resposible for deleting it.
shared_ptr<Agent> create_agent(const string &name, const string &type, Point location)
{
   if (type == "Soldier")
   {
      return shared_ptr<Agent>(new Soldier(name, location));
   }
   else if (type == "Peasant")
   {
      return shared_ptr<Agent>(new Peasant(name, location));
   }
   throw Error("Trying to create agent of unknown type!");
}
