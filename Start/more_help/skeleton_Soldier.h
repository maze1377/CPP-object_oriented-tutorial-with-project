/*
A Soldier is an Agent that has attack and defense behaviors. It can be commanded
to start attacking another Agent and will continue the attack as long as 
it is alive and the target is alive and in range. If attacked, the Soldier will
start attacking its attacker.
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

Private members of your choice can be added.

You must delete this comment and all other comments that start with "***".
*/

public:
	
	// *** define as specified
	Soldier(const std::string& name_, Point location_);
	
	~Soldier();
	
	// update implements Soldier behavior
	void update() override;
	
	// Make this Soldier start attacking the target Agent.
	// Throws an exception if the target is the same as this Agent,
	// is out of range, or is not alive.
	void start_attacking(Agent* target_ptr) override;
	
	// Overrides Agent's take_hit to counterattack when attacked.
	void take_hit(int attack_strength, Agent* attacker_ptr) override;
	
	// Overrides Agent's stop to print a message
	void stop() override;

	// output information about the current state
	void describe() const override;
