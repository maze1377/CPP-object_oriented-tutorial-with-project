#include "Farm.h"
#include "Model.h"
#include <iostream>

using std::cout;
using std::endl;
using std::string;

static const double initial_food_c = 50.0;
static const double initial_rate_c = 2.0;

Farm::Farm(const std::string &in_name, Point in_location) : Structure(in_name, in_location)
{
   total_food = initial_food_c;
   production_rate = initial_rate_c;
}

// returns the specified amount, or the remaining amount, whichever is less,
// and deducts that amount from the amount on hand
double Farm::withdraw(double amount_to_get)
{
   if (amount_to_get > total_food)
   {
      amount_to_get = total_food;
      total_food = 0.0;
      Model::get_instance()->notify_amount(get_name(), total_food);
      return amount_to_get;
   }
   total_food -= amount_to_get;
   Model::get_instance()->notify_amount(get_name(), total_food);
   return amount_to_get;
}

//	update adds the production amount to the stored amount
void Farm::update()
{
   total_food += production_rate;
   cout << "Farm " << get_name() << " now has " << total_food << endl;
   Model::get_instance()->notify_amount(get_name(), total_food);
}

// output information about the current state
void Farm::describe() const
{
   cout << "Farm ";
   Structure::describe();
   cout << "   Food available: " << total_food << endl;
}
