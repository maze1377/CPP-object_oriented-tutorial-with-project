#include "Structure.h"
#include <iostream>

using std::cout;
using std::endl;

void Structure::describe() const
{
   cout << get_name() << " at " << location << endl;
}

Structure::Structure(std::string name_, Point location_) : Sim_object(name_), location(location_) {}
