#ifndef AGENT_FACTORY_H
#define AGENT_FACTORY_H

#include <string>

struct Point;
class Agent;

// Create and return the pointer to the specified Agent type. If the type
// is unrecognized, throws Error("Trying to create agent of unknown type!")
// The Agent is allocated with new, so some other component is resposible for deleting it.
Agent * create_agent(const std::string& name, const std::string& type, Point location);

#endif
