#include "Controller.h"
#include "Views.h"
#include "Model.h"
#include "Agent.h"
#include "Structure.h"
#include "Utility.h"
#include "Structure_factory.h"
#include "Agent_factory.h"
#include <map>
#include <iostream>
#include <new>
#include <algorithm>

using std::bad_alloc;
using std::cin;
using std::cout;
using std::dynamic_pointer_cast;
using std::endl;
using std::for_each;
using std::map;
using std::shared_ptr;
using std::string;

static const int map_initial_size = 25;
static const Point initial_origin(-10., -10.);
static const double initial_scale = 2.;
static const int local_view_size = 9;

void Controller::run()
{
   load_Agent_commands();
   load_whole_program_commands();
   load_View_commands();

   while (true)
   {
      cout << "\nTime " << Model::get_instance()->get_time() << ": Enter command: ";
      string input;
      cin >> input;

      if (!input.compare("quit"))
      {
         cout << "Done" << endl;
         return;
      }

      try
      {
         if (Model::get_instance()->is_agent_present(input))
         {
            shared_ptr<Agent> aptr = Model::get_instance()->get_agent_ptr(input);

            string agent_cmd;
            cin >> agent_cmd;
            // handle agent map cmds
            Agent_cmd_fp_t fp = Agent_command_map[agent_cmd];

            if (fp)
            {
               (this->*fp)(input);
            }
            else
            {
               Agent_command_map.erase(agent_cmd);
               throw Error("Unrecognized command!");
            }
         }
         else
         {
            // handle view and rest of program cmds
            program_cmd_fp_t fp = program_command_map[input];
            if (fp)
            {
               (this->*fp)();
            }
            else
            {
               program_command_map.erase(input);

               // if not a program command check if input is a view command
               view_cmd_fp_t view_fp = view_command_map[input];
               string view_name;
               if (input == "open" || input == "close")
               {
                  cin >> view_name;
               }

               if (view_fp)
               {
                  (this->*view_fp)(view_name);
               }
               else
               {
                  view_command_map.erase(input);
                  throw Error("Unrecognized command!");
               }
            }
         }
      }
      catch (Error &error)
      {
         cout << error.msg << endl;
         cin.clear();
         consume_line();
      }
      catch (bad_alloc &b)
      {
         cout << "Bad alloc thrown" << endl;
         exit(1);
      }
      catch (...) // if unknown things happen
      {
         cout << "something strange got thrown" << endl;
      }
   }
}

// loader functions
void Controller::load_Agent_commands()
{
   Agent_command_map["move"] = &Controller::do_move;
   Agent_command_map["work"] = &Controller::do_work;
   Agent_command_map["attack"] = &Controller::do_attack;
   Agent_command_map["stop"] = &Controller::do_stop;
}

void Controller::load_whole_program_commands()
{
   program_command_map["status"] = &Controller::status;
   program_command_map["show"] = &Controller::do_show;
   program_command_map["go"] = &Controller::do_go;
   program_command_map["build"] = &Controller::build;
   program_command_map["train"] = &Controller::train;
}

void Controller::load_View_commands()
{
   view_command_map["default"] = &Controller::set_default;
   view_command_map["size"] = &Controller::set_size;
   view_command_map["zoom"] = &Controller::zoom;
   view_command_map["pan"] = &Controller::pan;
   view_command_map["open"] = &Controller::open;
   view_command_map["close"] = &Controller::close;
}

// Agent commands
void Controller::do_move(const string &name)
{
   shared_ptr<Agent> aptr = Model::get_instance()->get_agent_ptr(name);
   double x, y;

   cin >> x;
   if (!cin.good())
   {
      throw Error("Expected a double!");
   }

   cin >> y;
   if (!cin.good())
   {
      throw Error("Expected a double!");
   }

   Point p(x, y);
   aptr->move_to(p);
}

void Controller::do_work(const string &name)
{
   shared_ptr<Agent> aptr = Model::get_instance()->get_agent_ptr(name);
   string source, dest;
   cin >> source;
   shared_ptr<Structure> sptr = Model::get_instance()->get_structure_ptr(source);
   cin >> dest;
   shared_ptr<Structure> dptr = Model::get_instance()->get_structure_ptr(dest);

   aptr->start_working(sptr, dptr);
}

void Controller::do_attack(const string &name)
{
   string input;
   cin >> input;

   shared_ptr<Agent> attacker = Model::get_instance()->get_agent_ptr(name);
   shared_ptr<Agent> target = Model::get_instance()->get_agent_ptr(input);

   attacker->start_attacking(target);
}

void Controller::do_stop(const string &name)
{
   shared_ptr<Agent> aptr = Model::get_instance()->get_agent_ptr(name);
   aptr->stop();
}

//Whole progam commands
void Controller::status()
{
   Model::get_instance()->describe();
}

void Controller::do_show()
{
   for (auto view : views)
   {
      view->draw();
   }
}

void Controller::do_go()
{
   Model::get_instance()->update();
}

void Controller::build()
{
   string name, type;
   double x, y;
   shared_ptr<Structure> sptr;

   cin >> name;

   if (Model::get_instance()->is_name_in_use(name))
   {
      throw Error("Name is already in use!");
   }

   cin >> type;

   cin >> x;
   if (!cin.good())
   {
      throw Error("Expected a double!");
   }

   cin >> y;
   if (!cin.good())
   {
      throw Error("Expected a double!");
   }

   Point p(x, y);
   sptr = create_structure(name, type, p);
   Model::get_instance()->add_structure(sptr);
}

void Controller::train()
{
   string name, type;
   double x, y;
   shared_ptr<Agent> aptr;

   cin >> name;

   if (Model::get_instance()->is_name_in_use(name))
   {
      throw Error("Name is already in use!");
   }

   cin >> type;

   cin >> x;
   if (!cin.good())
   {
      throw Error("Expected a double!");
   }

   cin >> y;
   if (!cin.good())
   {
      throw Error("Expected a double!");
   }

   Point p(x, y);
   aptr = create_agent(name, type, p);
   Model::get_instance()->add_agent(aptr);
}

//view commands
void Controller::set_default(const string &name)
{
   auto map_view_ptr = find_map_view();
   if (!map_view_ptr)
   {
      throw Error("No map view is open!");
   }
   map_view_ptr->set_defaults();
}

void Controller::set_size(const string &name)
{
   auto map_view_ptr = find_map_view();
   if (!map_view_ptr)
   {
      throw Error("No map view is open!");
   }

   int size;
   cin >> size;

   if (!cin.good())
   {
      throw Error("Expected an integer!");
   }
   map_view_ptr->set_size(size);
}

void Controller::zoom(const string &name)
{
   auto map_view_ptr = find_map_view();
   if (!map_view_ptr)
   {
      throw Error("No map view is open!");
   }

   double scale;
   cin >> scale;

   if (!cin.good())
   {
      throw Error("Expected a double!");
   }
   map_view_ptr->set_scale(scale);
}

void Controller::pan(const string &name)
{
   auto map_view_ptr = find_map_view();
   if (!map_view_ptr)
   {
      throw Error("No map view is open!");
   }

   double x;
   cin >> x;

   if (!cin.good())
   {
      throw Error("Expected a double!");
   }

   double y;
   cin >> y;

   if (!cin.good())
   {
      throw Error("Expected a double!");
   }

   Point p(x, y);
   map_view_ptr->set_origin(p);
}

void Controller::open(const string &name)
{
   // check if a view of that name is already opened
   for (auto view : views)
   {
      if (view->get_name() == name)
      {
         throw Error("View of that name already open!");
      }
   }

   if (name == "map")
   {
      shared_ptr<View> view_pointer(new Map_View(name,
                                                 map_initial_size, initial_origin,
                                                 initial_scale));
      Model::get_instance()->attach(view_pointer);
      views.push_back(view_pointer);
   }
   else if (name == "health")
   {
      shared_ptr<View> view_pointer(new Health_View(name));
      Model::get_instance()->attach(view_pointer);
      views.push_back(view_pointer);
   }
   else if (name == "amounts")
   {
      shared_ptr<View> view_pointer(new Amount_View(name));
      Model::get_instance()->attach(view_pointer);
      views.push_back(view_pointer);
   }
   else
   {
      if (Model::get_instance()->is_agent_present(name))
      {
         auto aptr = Model::get_instance()->get_agent_ptr(name);
         shared_ptr<View> view_pointer(new Local_View(name, local_view_size,
                                                      aptr->get_location(), initial_scale));
         Model::get_instance()->attach(view_pointer);
         views.push_back(view_pointer);
      }
      else if (Model::get_instance()->is_structure_present(name))
      {
         auto sptr = Model::get_instance()->get_structure_ptr(name);
         shared_ptr<View> view_pointer(new Local_View(name, local_view_size,
                                                      sptr->get_location(), initial_scale));
         Model::get_instance()->attach(view_pointer);
         views.push_back(view_pointer);
      }
      else
      {
         throw Error("No object of that name!");
      }
   }
}

void Controller::close(const string &name)
{
   auto start = views.begin();

   for (; start != views.end(); ++start)
   {
      if ((*start)->get_name() == name)
      {
         auto view_ptr = *start;
         Model::get_instance()->detach(view_ptr);
         views.erase(start);
         return;
      }
   }
   throw Error("No view of that name is open!");
}

void Controller::consume_line()
{
   while (cin.get() != '\n')
      ;
}

shared_ptr<Map_View> Controller::find_map_view()
{
   shared_ptr<Map_View> empty;
   for (auto view_pointer : views)
   {
      if (view_pointer->get_name() == "map")
      {
         return dynamic_pointer_cast<Map_View>(view_pointer);
      }
   }
   return empty;
}
