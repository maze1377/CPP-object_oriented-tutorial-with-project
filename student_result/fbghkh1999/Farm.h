#ifndef FARM_H
#define FARM_H

#include "Geometry.h"
#include "Structure.h"
#include <string>

/*
A Farm is a Structure that when updated, increments the amount of food on hand
by the production rate amount.
Food can be withdrawn, but no provision is made for depositing any.
*/

class Farm : public Structure
{
public:
	Farm(const std::string &in_name, Point in_location);

	// returns the specified amount, or the remaining amount, whichever is less,
	// and deducts that amount from the amount on hand
	double withdraw(double amount_to_get) override;

	// update adds the production amount to the stored amount
	void update() override;

	// gets the current food at the farm
	double get_current_food() override
	{
		return total_food;
	}

	// output information about the current state
	void describe() const override;

private:
	double total_food;
	double production_rate;
};
#endif
