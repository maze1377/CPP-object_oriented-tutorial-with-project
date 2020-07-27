/* 
A Town_Hall is a structure that provides for depositing and withdrawing food,
but does no updating.
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
You can add private members of your choice.

You must delete this comment and all other comments that start with "***".
*/

public:
	Town_Hall (const std::string& name_, Point location_);
	
	~Town_Hall();
	
	// deposit adds in the supplied amount
	void deposit(double deposit_amount) override;

	// Return whichever is less, the request or (the amount on hand - 10%) (a "tax"),
	// but amounts less than 1.0 are not supplied - the amount returned is zero.
	// update the amount on hand by subtracting the amount returned.
	double withdraw(double amount_to_obtain) override;

	// output information about the current state
	void describe() const override;
