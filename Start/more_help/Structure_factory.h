#ifndef STRUCTURE_FACTORY_H
#define STRUCTURE_FACTORY_H

#include <string>

struct Point;
class Structure;

// Create and return the pointer to the specified Structure type. If the type
// is unrecognized, throws Error("Trying to create structure of unknown type!")
// The Structure is allocated with new, so some other component is resposible for deleting it.
Structure * create_structure(const std::string& name, const std::string& type, Point location);

#endif
