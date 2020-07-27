#include "Town_Hall.h"
#include "Model.h"
#include <iostream>

using std::cout;
using std::endl;

static const double initial_food = 0.0;

Town_Hall::Town_Hall(const std::string &in_name, Point in_location) : Structure(in_name, in_location)
{
   total_food = initial_food;
}

// deposit adds in the supplied amount
void Town_Hall::deposit(double deposit_amount)
{
   total_food += deposit_amount;
   Model::get_instance()->notify_amount(get_name(), total_food);
}

// returns the specified amount, or the remaining amount, whichever is less,
// and deducts that amount from the amount on hand
double Town_Hall::withdraw(double amount_to_obtain)
{
   if (amount_to_obtain > total_food)
   {
      total_food = initial_food;
      total_food = 0.0;
      Model::get_instance()->notify_amount(get_name(), total_food);
      return total_food;
   }
   total_food -= amount_to_obtain;
   Model::get_instance()->notify_amount(get_name(), total_food);
   return amount_to_obtain;
}

// output information about the current state
void Town_Hall::describe() const
{
   cout << "Town_Hall ";
   Structure::describe();
   cout << "   Contains " << total_food << endl;
}