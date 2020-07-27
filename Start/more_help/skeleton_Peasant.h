/* 
A Peasant is an Agent that can move food between Structures. It can be commanded to
start_working, whereupon it moves to the source, picks up food, returns to destination,
deposits the food, returns to source.  If picks up zero food at the source, it waits there
and tries again on the next update. 
If commanded to move_to somewhere, it stops working, and goes there.
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
	// *** define these functions in .cpp; initialize with zero amount being carried
	Peasant(const std::string& name_, Point location_);

	~Peasant();

	// implement Peasant behavior
	void update() override;
	
	// overridden to suspend working behavior
    void move_to(Point dest) override;
	
	// stop moving and working
	void stop() override;

	// starts the working process
	// Throws an exception if the source is the same as the destination.
	void start_working(Structure * source_, Structure * destination_) override;

	// output information about the current state
	void describe() const override;
