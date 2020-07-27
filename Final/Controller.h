#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
#include <map>
#include <memory>
#include <list>

// Controller This class is responsible for controlling
// the Model and View according to interactions with the user.


class Model;
class View;
class Map_View;

class Controller
{
public:
   // run the program by accepting user commands
   void run();

private:
   std::list<std::shared_ptr<View>> views;

   // agent command map typedefs and declaration
   typedef void (Controller::*Agent_cmd_fp_t)(const std::string &);
   typedef std::map<std::string, Agent_cmd_fp_t> Agent_cmd_map_t;
   Agent_cmd_map_t Agent_command_map;

   // whole program command map typdefs and declaration
   typedef void (Controller::*program_cmd_fp_t)();
   typedef std::map<std::string, program_cmd_fp_t> program_cmd_map_t;
   program_cmd_map_t program_command_map;

   // view command map typedefs and declaration
   typedef void (Controller::*view_cmd_fp_t)(const std::string &);
   typedef std::map<std::string, view_cmd_fp_t> view_cmd_map_t;
   view_cmd_map_t view_command_map;

   // consume line helper
   void consume_line();

   // command map loaders
   void load_Agent_commands();
   void load_whole_program_commands();
   void load_View_commands();

   // Agent commands
   void do_move(const std::string &name);
   void do_work(const std::string &name);
   void do_attack(const std::string &name);
   void do_stop(const std::string &name);

   // whole-program commands
   void status();
   void do_show();
   void do_go();
   void build();
   void train();

   // View commands
   void set_default(const std::string &name);
   void set_size(const std::string &name);
   void zoom(const std::string &name);
   void pan(const std::string &name);
   void open(const std::string &name);
   void close(const std::string &name);

   // helper to find the map view
   std::shared_ptr<Map_View> find_map_view();
};
#endif
