#include "Model.h"
#include "Agent_factory.h"
#include "Structure_factory.h"
#include "Structure.h"
#include "Agent.h"
#include "Utility.h"
#include "Views.h"
#include <algorithm>
#include <set>
#include <math.h>

using std::for_each;
using std::pair;
using std::set;
using std::shared_ptr;
using std::string;

Model *Model::model = nullptr;

Model *Model::get_instance()
{
   if (!model)
   {
      model = new Model();
   }
   return model;
}

class Model_destroyer
{
public:
   ~Model_destroyer()
   {
      delete Model::model;
   }
};

// create an instance of the destroyer class
static Model_destroyer destroyer;

Model::Model()
{
   time = 0;

   add_structure(create_structure("Rivendale", "Farm", Point(10., 10.)));
   add_structure(create_structure("Sunnybrook", "Farm", Point(0., 30.)));
   add_structure(create_structure("Shire", "Town_Hall", Point(20., 20.)));
   add_structure(create_structure("Paduca", "Town_Hall", Point(30., 30.)));

   add_agent(create_agent("Pippin", "Peasant", Point(5., 10.)));
   add_agent(create_agent("Merry", "Peasant", Point(0., 25.)));
   add_agent(create_agent("Zug", "Soldier", Point(20., 30.)));
   add_agent(create_agent("Bug", "Soldier", Point(15., 20.)));
}

// is name already in use for either agent or structure?
bool Model::is_name_in_use(const string &name) const
{
   if (sim_objects.count(name) == 1)
   {
      return true;
   }
   return false;
}

// is there a structure with this name?
bool Model::is_structure_present(const string &name) const
{
   if (structures.count(name) == 1)
   {
      return true;
   }
   return false;
}

// add a new structure; assumes none with the same name
void Model::add_structure(shared_ptr<Structure> sptr)
{
   sim_objects[sptr->get_name()] = sptr;
   structures[sptr->get_name()] = sptr;
   for (auto pair : views)
   {
      pair.second->update_location(sptr->get_name(), sptr->get_location());
      pair.second->update_amount(sptr->get_name(), sptr->get_current_food());
   }
}

// will throw Error("Structure not found!") if no structure of that name
shared_ptr<Structure> Model::get_structure_ptr(const string &name) const
{
   auto it = structures.find(name);

   if (it == structures.end())
   {
      throw Error("Structure not found!");
   }

   return it->second;
}

// is there an agent with this name?
bool Model::is_agent_present(const string &name) const
{
   if (agents.count(name) == 1)
   {
      return true;
   }
   return false;
}

// add a new agent; assumes none with the same name
void Model::add_agent(shared_ptr<Agent> aptr)
{
   sim_objects[aptr->get_name()] = aptr;
   agents[aptr->get_name()] = aptr;
   for (auto pair : views)
   {
      pair.second->update_location(aptr->get_name(), aptr->get_location());
      pair.second->update_health(aptr->get_name(), aptr->get_health());
      if (aptr->get_amount() >= 0.0)
      {
         pair.second->update_amount(aptr->get_name(), aptr->get_amount());
      }
   }
}

// will throw Error("Agent not found!") if no agent of that name
shared_ptr<Agent> Model::get_agent_ptr(const string &name) const
{
   auto it = agents.find(name);

   if (it == agents.end())
   {
      throw Error("Agent not found!");
   }

   return it->second;
}

// removes the agent and then deletes it; no error if not found
void Model::remove_agent(shared_ptr<Agent> aptr)
{
   auto it = agents.find(aptr->get_name());
   auto sim_it = sim_objects.find(aptr->get_name());

   for (auto pair : views)
   {
      pair.second->update_remove(aptr->get_name());
   }

   if (it != agents.end())
   {
      agents.erase(it);
      sim_objects.erase(sim_it);
   }
}

// tell all objects to describe themselves to the console
void Model::describe() const
{
   for_each(sim_objects.begin(), sim_objects.end(),
            [](pair<string, shared_ptr<Sim_object>> p) { p.second->describe(); });
}

// update the objects
void Model::update()
{
   time++;
   for (auto sim_object_pair : sim_objects)
   {
      sim_object_pair.second->update();
   }
}

// Attaching a View causes it to be updated with all current objects'location,
// amounts, and health
void Model::attach(shared_ptr<View> view_pointer)
{
   views[view_pointer->get_name()] = view_pointer;
   for (auto pair : structures)
   {
      view_pointer->update_location(pair.second->get_name(), pair.second->get_location());
      view_pointer->update_amount(pair.second->get_name(), pair.second->get_current_food());
   }

   for (auto pair : agents)
   {
      view_pointer->update_location(pair.second->get_name(), pair.second->get_location());
      if (pair.second->get_amount() >= 0.0)
      {
         view_pointer->update_amount(pair.second->get_name(), pair.second->get_amount());
      }
      view_pointer->update_health(pair.second->get_name(), pair.second->get_health());
   }
}

// Detach the specified View by discarding the pointer - no updates sent to it thereafter.
void Model::detach(shared_ptr<View> view_pointer)
{
   views.erase(view_pointer->get_name());
}

// notifies the each View of the location change
void Model::notify_location(const string &name, Point location)
{
   for (auto pair : views)
   {
      pair.second->update_location(name, location);
   }
}

// notifies each view of the amount change
void Model::notify_amount(const string &name, double amount)
{
   for (auto pair : views)
   {
      pair.second->update_amount(name, amount);
   }
}

// notifies each view of the health change
void Model::notify_health(const string &name, double health)
{
   for (auto pair : views)
   {
      pair.second->update_health(name, health);
   }
}

// finds the closest agent to the specified agent name
shared_ptr<Agent> Model::find_closest_Agent(const string &name)
{
   shared_ptr<Agent> searching_Agent = agents[name];
   auto start = agents.begin();
   shared_ptr<Agent> closest_Agent;

   Point searching_Agent_location = searching_Agent->get_location();

   // initial current_distance
   double current_distance = DBL_MAX;
   double new_distance = -1.0;

   for (; start != agents.end(); ++start)
   {
      if (start->second->get_name() != name)
      {
         new_distance = cartesian_distance(searching_Agent_location,
                                           start->second->get_location());
         if (new_distance < current_distance)
         {
            current_distance = new_distance;
            closest_Agent = start->second;
         }
      }
   }
   return closest_Agent;
}

// finds the closest structure to the specified agent name
std::shared_ptr<Structure> Model::find_closest_Structure(const std::string &name)
{
   shared_ptr<Agent> searching_Agent = agents[name];
   auto start = structures.begin();
   shared_ptr<Structure> closest_Structure;

   Point searching_Agent_location = searching_Agent->get_location();

   // initial current_distance
   double current_distance = DBL_MAX;
   double new_distance = -1.0;

   for (; start != structures.end(); ++start)
   {
      new_distance = cartesian_distance(searching_Agent_location,
                                        start->second->get_location());
      if (new_distance < current_distance)
      {
         current_distance = new_distance;
         closest_Structure = start->second;
      }
   }
   return closest_Structure;
}
