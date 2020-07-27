#ifndef TOWN_HALL_H
#define TOWN_HALL_H

#include "Geometry.h"
#include "Structure.h"
#include <string>

/* 
A Town_Hall is a structure that provides for depositing and withdrawing food,
but does no updating.
*/

class Town_Hall : public Structure
{
public:
	Town_Hall(const std::string &in_name, Point in_location);

	// deposit adds in the supplied amount
	void deposit(double deposit_amount) override;

	// returns the specified amount, or the remaining amount, whichever is less,
	// and deducts that amount from the amount on hand
	double withdraw(double amount_to_obtain) override;

	// output information about the current state
	void describe() const override;

	// returns the total_food at the town hall
	double get_current_food() override
	{
		return total_food;
	}

private:
	double total_food;
};

#endif
