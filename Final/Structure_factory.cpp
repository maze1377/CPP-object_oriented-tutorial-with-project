#include "Structure_factory.h"
#include "Town_Hall.h"
#include "Farm.h"
#include "Utility.h"

using std::shared_ptr;

// Create and return the pointer to the specified Structure type. If the type
// is unrecognized, throws Error("Trying to create structure of unknown type!")
// The Structure is allocated with new, so some other component is resposible for deleting it.
shared_ptr<Structure> create_structure(const std::string &name, const std::string &type, Point location)
{
   if (type == "Farm")
   {
      return shared_ptr<Structure>(new Farm(name, location));
   }
   else if (type == "Town_Hall")
   {
      return shared_ptr<Structure>(new Town_Hall(name, location));
   }
   throw Error("Trying to create structure of unknown type!");
}