/*
A Farm is a Structure that when updated, increments the amount of food on hand
by the production rate amount.
Food can be withdrawn, but no provision is made for depositing any.
*/

/* *** Comments starting with *** (like this one) in this skeleton file are
instructions for you and should be deleted after you have dealt with them.
You must add code to this file to meet the requirements in the project document,
the comments below, and other relevant course content.
*/

/* 
*** This skeleton file shows the required public interface for the class, which you may not modify. 
If no protected members are shown, there must be none in your version. 
If any protected or private members are shown here, then your class must also have them and use them as intended.

You must delete this comment and all other comments that start with "***".
*/

public:
	Farm (const std::string& name_, Point location_);
	
	~Farm();
		
	// returns the specified amount, or the remaining amount, whichever is less,
	// and deducts that amount from the amount on hand
	double withdraw(double amount_to_get) override;

	//	update adds the production amount to the stored amount
	void update() override;

	// output information about the current state
	void describe() const override;
	
